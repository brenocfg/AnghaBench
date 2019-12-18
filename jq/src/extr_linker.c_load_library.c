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
struct lib_loading_state {int ct; void** defs; void** names; } ;
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  jq_state ;
typedef  void* block ;

/* Variables and functions */
 int /*<<< orphan*/  OP_IS_CALL_PSEUDO ; 
 void* block_bind_self (void*,int /*<<< orphan*/ ) ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* gen_const_global (int /*<<< orphan*/ ,char const*) ; 
 void* gen_noop () ; 
 int /*<<< orphan*/  jq_get_jq_origin (int /*<<< orphan*/ *) ; 
 scalar_t__ jq_parse_library (struct locfile*,void**) ; 
 int /*<<< orphan*/  jq_report_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_get_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_invalid_has_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_load_file (int /*<<< orphan*/ ,int) ; 
 void* jv_mem_realloc (void**,int) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locfile_free (struct locfile*) ; 
 struct locfile* locfile_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ process_dependencies (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,struct lib_loading_state*) ; 
 void* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_library(jq_state *jq, jv lib_path, int is_data, int raw, int optional, const char *as, block *out_block, struct lib_loading_state *lib_state) {
  int nerrors = 0;
  struct locfile* src = NULL;
  block program;
  jv data;
  if (is_data && !raw)
    data = jv_load_file(jv_string_value(lib_path), 0);
  else
    data = jv_load_file(jv_string_value(lib_path), 1);
  int state_idx;
  if (!jv_is_valid(data)) {
    program = gen_noop();
    if (!optional) {
      if (jv_invalid_has_msg(jv_copy(data)))
        data = jv_invalid_get_msg(data);
      else
        data = jv_string("unknown error");
      jq_report_error(jq, jv_string_fmt("jq: error loading data file %s: %s\n", jv_string_value(lib_path), jv_string_value(data)));
      nerrors++;
    }
    goto out;
  } else if (is_data) {
    // import "foo" as $bar;
    program = gen_const_global(jv_copy(data), as);
  } else {
    // import "foo" as bar;
    src = locfile_init(jq, jv_string_value(lib_path), jv_string_value(data), jv_string_length_bytes(jv_copy(data)));
    nerrors += jq_parse_library(src, &program);
    locfile_free(src);
    if (nerrors == 0) {
      char *lib_origin = strdup(jv_string_value(lib_path));
      nerrors += process_dependencies(jq, jq_get_jq_origin(jq),
                                      jv_string(dirname(lib_origin)),
                                      &program, lib_state);
      free(lib_origin);
      program = block_bind_self(program, OP_IS_CALL_PSEUDO);
    }
  }
  state_idx = lib_state->ct++;
  lib_state->names = jv_mem_realloc(lib_state->names, lib_state->ct * sizeof(const char *));
  lib_state->defs = jv_mem_realloc(lib_state->defs, lib_state->ct * sizeof(block));
  lib_state->names[state_idx] = strdup(jv_string_value(lib_path));
  lib_state->defs[state_idx] = program;
out:
  *out_block = program;
  jv_free(lib_path);
  jv_free(data);
  return nerrors;
}