#define DUCKDB_EXTENSION_MAIN

#include "arrow_extension.hpp"
#include "arrow_stream_buffer.hpp"
#include "arrow_scan_ipc.hpp"
#include "arrow_to_ipc.hpp"

#include "duckdb.hpp"
#ifndef DUCKDB_AMALGAMATION
#include "duckdb/common/arrow/result_arrow_wrapper.hpp"
#include "duckdb/common/arrow/arrow_appender.hpp"
#include "duckdb/common/arrow/arrow_converter.hpp"
#include "duckdb/parser/parsed_data/create_table_function_info.hpp"
#include "duckdb/function/table/arrow.hpp"
#endif

namespace duckdb {

static void LoadInternal(ExtensionLoader &loader) {
  loader.RegisterFunction(ToArrowIPCFunction::GetFunction());
  loader.RegisterFunction(ArrowIPCTableFunction::GetFunction());
}

void ArrowExtension::Load(ExtensionLoader &loader) { LoadInternal(loader); }
std::string ArrowExtension::Name() { return "arrow"; }

} // namespace duckdb

extern "C" {

DUCKDB_EXTENSION_API void arrow_duckdb_cpp_init(duckdb::ExtensionLoader &loader) {
  LoadInternal(loader);
}

DUCKDB_EXTENSION_API const char *arrow_version() {
  return duckdb::DuckDB::LibraryVersion();
}
}

#ifndef DUCKDB_EXTENSION_MAIN
#error DUCKDB_EXTENSION_MAIN not defined
#endif
