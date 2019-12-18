#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int sigl; } ;
typedef  TYPE_1__ FPU_REG ;

/* Variables and functions */
 int /*<<< orphan*/  FPU_settag0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FPU_stack_overflow () ; 
 scalar_t__ STACK_OVERFLOW ; 
 int /*<<< orphan*/  clear_C1 () ; 
 int /*<<< orphan*/  push () ; 
 int /*<<< orphan*/  reg_copy (TYPE_1__ const*,TYPE_1__*) ; 

__attribute__((used)) static void fld_const(FPU_REG const * c, int adj, u_char tag)
{
	FPU_REG *st_new_ptr;

	if (STACK_OVERFLOW) {
		FPU_stack_overflow();
		return;
	}
	push();
	reg_copy(c, st_new_ptr);
	st_new_ptr->sigl += adj;	/* For all our fldxxx constants, we don't need to
					   borrow or carry. */
	FPU_settag0(tag);
	clear_C1();
}