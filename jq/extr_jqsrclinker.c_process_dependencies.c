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
typedef  size_t uint64_t ;
struct lib_loading_state {size_t ct; int /*<<< orphan*/ * defs; int /*<<< orphan*/ * names; } ;
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  jq_state ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 scalar_t__ JV_KIND_STRING ; 
 scalar_t__ JV_KIND_TRUE ; 
 int /*<<< orphan*/  OP_IS_CALL_PSEUDO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_bind_library (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  block_take_imports (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_search (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_lib (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_noop () ; 
 int /*<<< orphan*/  jq_report_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_array_get (int /*<<< orphan*/ ,int) ; 
 int jv_array_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_get_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_object_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,char*) ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 
 scalar_t__ load_library (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,char const*,int /*<<< orphan*/ *,struct lib_loading_state*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  validate_relpath (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_dependencies(jq_state *jq, jv jq_origin, jv lib_origin, block *src_block, struct lib_loading_state *lib_state) {
  jv deps = block_take_imports(src_block);
  block bk = *src_block;
  int nerrors = 0;

  // XXX This is a backward jv_array_foreach because bindings go in reverse
  for (int i = jv_array_length(jv_copy(deps)); i > 0; ) {
    i--;
    jv dep = jv_array_get(jv_copy(deps), i);

    const char *as_str = NULL;
    int is_data = jv_get_kind(jv_object_get(jv_copy(dep), jv_string("is_data"))) == JV_KIND_TRUE;
    int raw = 0;
    jv v = jv_object_get(jv_copy(dep), jv_string("raw"));
    if (jv_get_kind(v) == JV_KIND_TRUE)
      raw = 1;
    int optional = 0;
    if (jv_get_kind(jv_object_get(jv_copy(dep), jv_string("optional"))) == JV_KIND_TRUE)
      optional = 1;
    jv_free(v);
    jv relpath = validate_relpath(jv_object_get(jv_copy(dep), jv_string("relpath")));
    jv as = jv_object_get(jv_copy(dep), jv_string("as"));
    assert(!jv_is_valid(as) || jv_get_kind(as) == JV_KIND_STRING);
    if (jv_get_kind(as) == JV_KIND_STRING)
      as_str = jv_string_value(as);
    jv search = default_search(jq, jv_object_get(dep, jv_string("search")));
    // dep is now freed; do not reuse

    // find_lib does a lot of work that could be cached...
    jv resolved = find_lib(jq, relpath, search, is_data ? ".json" : ".jq", jv_copy(jq_origin), jv_copy(lib_origin));
    // XXX ...move the rest of this into a callback.
    if (!jv_is_valid(resolved)) {
      jv_free(as);
      if (optional) {
        jv_free(resolved);
        continue;
      }
      jv emsg = jv_invalid_get_msg(resolved);
      jq_report_error(jq, jv_string_fmt("jq: error: %s\n",jv_string_value(emsg)));
      jv_free(emsg);
      jv_free(deps);
      jv_free(jq_origin);
      jv_free(lib_origin);
      return 1;
    }

    if (is_data) {
      // Can't reuse data libs because the wrong name is bound
      block dep_def_block;
      nerrors += load_library(jq, resolved, is_data, raw, optional, as_str, &dep_def_block, lib_state);
      if (nerrors == 0) {
        // Bind as both $data::data and $data for backward compatibility vs common sense
        bk = block_bind_library(dep_def_block, bk, OP_IS_CALL_PSEUDO, as_str);
        bk = block_bind_library(dep_def_block, bk, OP_IS_CALL_PSEUDO, NULL);
      }
    } else {
      uint64_t state_idx = 0;
      for (; state_idx < lib_state->ct; ++state_idx) {
        if (strcmp(lib_state->names[state_idx],jv_string_value(resolved)) == 0)
          break;
      }

      if (state_idx < lib_state->ct) { // Found
        jv_free(resolved);
        // Bind the library to the program
        bk = block_bind_library(lib_state->defs[state_idx], bk, OP_IS_CALL_PSEUDO, as_str);
      } else { // Not found.   Add it to the table before binding.
        block dep_def_block = gen_noop();
        nerrors += load_library(jq, resolved, is_data, raw, optional, as_str, &dep_def_block, lib_state);
        // resolved has been freed
        if (nerrors == 0) {
          // Bind the library to the program
          bk = block_bind_library(dep_def_block, bk, OP_IS_CALL_PSEUDO, as_str);
        }
      }
    }

    jv_free(as);
  }
  jv_free(lib_origin);
  jv_free(jq_origin);
  jv_free(deps);
  return nerrors;
}