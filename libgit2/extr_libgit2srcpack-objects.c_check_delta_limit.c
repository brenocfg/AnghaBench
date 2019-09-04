#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* delta_sibling; struct TYPE_3__* delta_child; } ;
typedef  TYPE_1__ git_pobject ;

/* Variables and functions */

__attribute__((used)) static size_t check_delta_limit(git_pobject *me, size_t n)
{
	git_pobject *child = me->delta_child;
	size_t m = n;

	while (child) {
		size_t c = check_delta_limit(child, n + 1);
		if (m < c)
			m = c;
		child = child->delta_sibling;
	}
	return m;
}