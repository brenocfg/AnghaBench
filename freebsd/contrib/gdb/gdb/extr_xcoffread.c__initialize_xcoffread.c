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
typedef  int /*<<< orphan*/  TYPE_TARGET_TYPE ;

/* Variables and functions */
 int HOST_CHAR_BIT ; 
 int TARGET_INT_BIT ; 
 int /*<<< orphan*/  TYPE_CODE_FUNC ; 
 int /*<<< orphan*/  TYPE_CODE_INT ; 
 int /*<<< orphan*/  add_symtab_fns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 int /*<<< orphan*/  func_symbol_type ; 
 void* init_type (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* var_symbol_type ; 
 int /*<<< orphan*/  xcoff_sym_fns ; 

void
_initialize_xcoffread (void)
{
  add_symtab_fns (&xcoff_sym_fns);

  func_symbol_type = init_type (TYPE_CODE_FUNC, 1, 0,
				"<function, no debug info>", NULL);
  TYPE_TARGET_TYPE (func_symbol_type) = builtin_type_int;
  var_symbol_type =
    init_type (TYPE_CODE_INT, TARGET_INT_BIT / HOST_CHAR_BIT, 0,
	       "<variable, no debug info>", NULL);
}