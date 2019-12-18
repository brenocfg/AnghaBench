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
struct TYPE_2__ {int argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  suword (int /*<<< orphan*/ *,intptr_t) ; 

__attribute__((used)) static int
linux_fixup(register_t **stack_base, struct image_params *imgp)
{
	register_t *argv, *envp;

	argv = *stack_base;
	envp = *stack_base + (imgp->args->argc + 1);
	(*stack_base)--;
	suword(*stack_base, (intptr_t)(void *)envp);
	(*stack_base)--;
	suword(*stack_base, (intptr_t)(void *)argv);
	(*stack_base)--;
	suword(*stack_base, imgp->args->argc);
	return (0);
}