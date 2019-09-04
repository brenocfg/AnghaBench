#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct locfile {int dummy; } ;
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  jq_state ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 scalar_t__ JV_KIND_NULL ; 
 int /*<<< orphan*/  block_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_module_meta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_take_imports (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_lib (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jq_get_jq_origin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jq_get_lib_dirs (int /*<<< orphan*/ *) ; 
 int jq_parse_library (struct locfile*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_load_file (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jv_null () ; 
 int /*<<< orphan*/  jv_object () ; 
 int /*<<< orphan*/  jv_object_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locfile_free (struct locfile*) ; 
 struct locfile* locfile_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_relpath (int /*<<< orphan*/ ) ; 

jv load_module_meta(jq_state *jq, jv mod_relpath) {
  // We can't know the caller's origin; we could though, if it was passed in
  jv lib_path = find_lib(jq, validate_relpath(mod_relpath), jq_get_lib_dirs(jq), ".jq", jq_get_jq_origin(jq), jv_null());
  if (!jv_is_valid(lib_path))
    return lib_path;
  jv meta = jv_null();
  jv data = jv_load_file(jv_string_value(lib_path), 1);
  if (jv_is_valid(data)) {
    block program;
    struct locfile* src = locfile_init(jq, jv_string_value(lib_path), jv_string_value(data), jv_string_length_bytes(jv_copy(data)));
    int nerrors = jq_parse_library(src, &program);
    if (nerrors == 0) {
      meta = block_module_meta(program);
      if (jv_get_kind(meta) == JV_KIND_NULL)
        meta = jv_object();
      meta = jv_object_set(meta, jv_string("deps"), block_take_imports(&program));
    }
    locfile_free(src);
    block_free(program);
  }
  jv_free(lib_path);
  jv_free(data);
  return meta;
}