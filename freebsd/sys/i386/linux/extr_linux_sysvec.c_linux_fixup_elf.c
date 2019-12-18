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
struct image_params {TYPE_1__* args; } ;
typedef  int /*<<< orphan*/  register_t ;
struct TYPE_2__ {scalar_t__ argc; } ;

/* Variables and functions */
 int EFAULT ; 
 int suword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linux_fixup_elf(register_t **stack_base, struct image_params *imgp)
{

	(*stack_base)--;
	if (suword(*stack_base, (register_t)imgp->args->argc) == -1)
		return (EFAULT);
	return (0);
}