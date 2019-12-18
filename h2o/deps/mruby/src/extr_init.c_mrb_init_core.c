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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  DONE ; 
 int /*<<< orphan*/  mrb_init_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_comparable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_enumerable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_exception (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_gc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_hash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_kernel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_mrblib (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_numeric (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_proc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_range (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_symbol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_symtbl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_version (int /*<<< orphan*/ *) ; 

void
mrb_init_core(mrb_state *mrb)
{
  mrb_init_symtbl(mrb); DONE;

  mrb_init_class(mrb); DONE;
  mrb_init_object(mrb); DONE;
  mrb_init_kernel(mrb); DONE;
  mrb_init_comparable(mrb); DONE;
  mrb_init_enumerable(mrb); DONE;

  mrb_init_symbol(mrb); DONE;
  mrb_init_string(mrb); DONE;
  mrb_init_exception(mrb); DONE;
  mrb_init_proc(mrb); DONE;
  mrb_init_array(mrb); DONE;
  mrb_init_hash(mrb); DONE;
  mrb_init_numeric(mrb); DONE;
  mrb_init_range(mrb); DONE;
  mrb_init_gc(mrb); DONE;
  mrb_init_version(mrb); DONE;
  mrb_init_mrblib(mrb); DONE;
}