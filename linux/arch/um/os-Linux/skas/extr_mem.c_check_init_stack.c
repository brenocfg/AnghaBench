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
struct mm_id {scalar_t__ stack; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long *check_init_stack(struct mm_id * mm_idp,
					      unsigned long *stack)
{
	if (stack == NULL) {
		stack = (unsigned long *) mm_idp->stack + 2;
		*stack = 0;
	}
	return stack;
}