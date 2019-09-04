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
struct tsort_store {int dummy; } ;
struct tsort_run {int length; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  merge (void**,struct tsort_run*,int,struct tsort_store*) ; 

__attribute__((used)) static ssize_t collapse(void **dst, struct tsort_run *stack, ssize_t stack_curr, struct tsort_store *store, ssize_t size)
{
	ssize_t A, B, C;

	while (1) {
		/* if the stack only has one thing on it, we are done with the collapse */
		if (stack_curr <= 1)
			break;

		/* if this is the last merge, just do it */
		if ((stack_curr == 2) && (stack[0].length + stack[1].length == size)) {
			merge(dst, stack, stack_curr, store);
			stack[0].length += stack[1].length;
			stack_curr--;
			break;
		}

		/* check if the invariant is off for a stack of 2 elements */
		else if ((stack_curr == 2) && (stack[0].length <= stack[1].length)) {
			merge(dst, stack, stack_curr, store);
			stack[0].length += stack[1].length;
			stack_curr--;
			break;
		}
		else if (stack_curr == 2)
			break;

		A = stack[stack_curr - 3].length;
		B = stack[stack_curr - 2].length;
		C = stack[stack_curr - 1].length;

		/* check first invariant */
		if (A <= B + C) {
			if (A < C) {
				merge(dst, stack, stack_curr - 1, store);
				stack[stack_curr - 3].length += stack[stack_curr - 2].length;
				stack[stack_curr - 2] = stack[stack_curr - 1];
				stack_curr--;
			} else {
				merge(dst, stack, stack_curr, store);
				stack[stack_curr - 2].length += stack[stack_curr - 1].length;
				stack_curr--;
			}
		} else if (B <= C) {
			merge(dst, stack, stack_curr, store);
			stack[stack_curr - 2].length += stack[stack_curr - 1].length;
			stack_curr--;
		} else
			break;
	}

	return stack_curr;
}