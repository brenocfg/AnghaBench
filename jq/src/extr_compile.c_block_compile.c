#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symbol_table {int dummy; } ;
struct locfile {int dummy; } ;
struct cfunction {int dummy; } ;
struct bytecode {TYPE_1__* globals; int /*<<< orphan*/  debuginfo; scalar_t__ nclosures; scalar_t__ parent; } ;
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  block ;
struct TYPE_2__ {int ncfunctions; int /*<<< orphan*/  cfunc_names; int /*<<< orphan*/  cfunctions; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bytecode_free (struct bytecode*) ; 
 int compile (struct bytecode*,int /*<<< orphan*/ ,struct locfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int count_cfunctions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_array () ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid () ; 
 void* jv_mem_alloc (int) ; 
 int /*<<< orphan*/  jv_mem_calloc (int,int) ; 
 int /*<<< orphan*/  jv_null () ; 
 int /*<<< orphan*/  jv_object () ; 
 int /*<<< orphan*/  jv_object_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 

int block_compile(block b, struct bytecode** out, struct locfile* lf, jv args) {
  struct bytecode* bc = jv_mem_alloc(sizeof(struct bytecode));
  bc->parent = 0;
  bc->nclosures = 0;
  bc->globals = jv_mem_alloc(sizeof(struct symbol_table));
  int ncfunc = count_cfunctions(b);
  bc->globals->ncfunctions = 0;
  bc->globals->cfunctions = jv_mem_calloc(sizeof(struct cfunction), ncfunc);
  bc->globals->cfunc_names = jv_array();
  bc->debuginfo = jv_object_set(jv_object(), jv_string("name"), jv_null());
  jv env = jv_invalid();
  int nerrors = compile(bc, b, lf, args, &env);
  jv_free(args);
  jv_free(env);
  assert(bc->globals->ncfunctions == ncfunc);
  if (nerrors > 0) {
    bytecode_free(bc);
    *out = 0;
  } else {
    *out = bc;
  }
  return nerrors;
}