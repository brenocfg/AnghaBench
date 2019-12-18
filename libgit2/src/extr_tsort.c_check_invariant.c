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
struct tsort_run {int length; } ;
typedef  int ssize_t ;

/* Variables and functions */

__attribute__((used)) static int check_invariant(struct tsort_run *stack, ssize_t stack_curr)
{
	if (stack_curr < 2)
		return 1;

	else if (stack_curr == 2) {
		const ssize_t A = stack[stack_curr - 2].length;
		const ssize_t B = stack[stack_curr - 1].length;
		return (A > B);
	} else {
		const ssize_t A = stack[stack_curr - 3].length;
		const ssize_t B = stack[stack_curr - 2].length;
		const ssize_t C = stack[stack_curr - 1].length;
		return !((A <= B + C) || (B <= C));
	}
}