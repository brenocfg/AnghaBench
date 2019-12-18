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
struct obj_order {scalar_t__ order; int orig_order; } ;

/* Variables and functions */

__attribute__((used)) static int compare_objs_order(const void *a_, const void *b_)
{
	struct obj_order const *a, *b;
	a = (struct obj_order const *)a_;
	b = (struct obj_order const *)b_;
	if (a->order != b->order)
		return a->order - b->order;
	return a->orig_order - b->orig_order;
}