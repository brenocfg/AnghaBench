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
struct attr_stack {char* origin; size_t originlen; struct attr_stack* prev; } ;

/* Variables and functions */

__attribute__((used)) static void push_stack(struct attr_stack **attr_stack_p,
		       struct attr_stack *elem, char *origin, size_t originlen)
{
	if (elem) {
		elem->origin = origin;
		if (origin)
			elem->originlen = originlen;
		elem->prev = *attr_stack_p;
		*attr_stack_p = elem;
	}
}