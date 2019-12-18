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
struct value {int dummy; } ;
struct ui_out {int dummy; } ;
struct captured_value_struct_elt_args {char* name; int* static_memfuncp; char* err; struct value** result_ptr; struct value** args; struct value** argp; } ;
typedef  enum gdb_rc { ____Placeholder_gdb_rc } gdb_rc ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int catch_exceptions (struct ui_out*,int /*<<< orphan*/ ,struct captured_value_struct_elt_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_captured_value_struct_elt ; 

enum gdb_rc
gdb_value_struct_elt (struct ui_out *uiout, struct value **result, struct value **argp,
		      struct value **args, char *name, int *static_memfuncp,
		      char *err)
{
  struct captured_value_struct_elt_args cargs;
  cargs.argp = argp;
  cargs.args = args;
  cargs.name = name;
  cargs.static_memfuncp = static_memfuncp;
  cargs.err = err;
  cargs.result_ptr = result;
  return catch_exceptions (uiout, do_captured_value_struct_elt, &cargs,
			   NULL, RETURN_MASK_ALL);
}