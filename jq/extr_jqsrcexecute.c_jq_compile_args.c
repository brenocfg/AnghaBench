#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct locfile {int dummy; } ;
typedef  int /*<<< orphan*/  jv ;
struct TYPE_8__ {int /*<<< orphan*/ * bc; int /*<<< orphan*/  nomem_handler_data; int /*<<< orphan*/  nomem_handler; } ;
typedef  TYPE_1__ jq_state ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 scalar_t__ JV_KIND_ARRAY ; 
 scalar_t__ JV_KIND_OBJECT ; 
 int /*<<< orphan*/  args2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int block_compile (int /*<<< orphan*/ ,int /*<<< orphan*/ **,struct locfile*,int /*<<< orphan*/ ) ; 
 int builtins_bind (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytecode_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jq_report_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jq_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_nomem_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,int,char*) ; 
 int load_program (TYPE_1__*,struct locfile*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locfile_free (struct locfile*) ; 
 struct locfile* locfile_init (TYPE_1__*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * optimize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int jq_compile_args(jq_state *jq, const char* str, jv args) {
  jv_nomem_handler(jq->nomem_handler, jq->nomem_handler_data);
  assert(jv_get_kind(args) == JV_KIND_ARRAY || jv_get_kind(args) == JV_KIND_OBJECT);
  struct locfile* locations;
  locations = locfile_init(jq, "<top-level>", str, strlen(str));
  block program;
  jq_reset(jq);
  if (jq->bc) {
    bytecode_free(jq->bc);
    jq->bc = 0;
  }
  int nerrors = load_program(jq, locations, &program);
  if (nerrors == 0) {
    nerrors = builtins_bind(jq, &program);
    if (nerrors == 0) {
      nerrors = block_compile(program, &jq->bc, locations, args = args2obj(args));
    }
  } else
    jv_free(args);
  if (nerrors)
    jq_report_error(jq, jv_string_fmt("jq: %d compile %s", nerrors, nerrors > 1 ? "errors" : "error"));
  if (jq->bc)
    jq->bc = optimize(jq->bc);
  locfile_free(locations);
  return jq->bc != NULL;
}