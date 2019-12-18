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
typedef  int /*<<< orphan*/  tcbptr ;
struct image_params {int dummy; } ;
typedef  scalar_t__ register_t ;

/* Variables and functions */
 int cloudabi64_fixup (scalar_t__**,struct image_params*) ; 
 int copyout (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static int
cloudabi64_fixup_tcb(register_t **stack_base, struct image_params *imgp)
{
	int error;
	register_t tcbptr;

	/* Place auxiliary vector and TCB on the stack. */
	error = cloudabi64_fixup(stack_base, imgp);
	if (error != 0)
		return (error);
	
	/*
	 * On x86-64, the TCB is referred to by %fs:0. Take some space
	 * from the top of the stack to store a single element array,
	 * containing a pointer to the TCB. %fs base will point to this.
	 */
	tcbptr = (register_t)*stack_base;
	return (copyout(&tcbptr, --*stack_base, sizeof(tcbptr)));
}