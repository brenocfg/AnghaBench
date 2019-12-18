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
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;
typedef  int /*<<< orphan*/  ecma_compiled_code_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ecma_builtin_get_global () ; 
 int /*<<< orphan*/  ecma_get_global_environment () ; 
 int /*<<< orphan*/  ecma_make_object_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_run (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ecma_value_t
vm_run_global (const ecma_compiled_code_t *bytecode_p) /**< pointer to bytecode to run */
{
  ecma_object_t *glob_obj_p = ecma_builtin_get_global ();

  return vm_run (bytecode_p,
                 ecma_make_object_value (glob_obj_p),
                 ecma_get_global_environment (),
                 false,
                 NULL,
                 0);
}