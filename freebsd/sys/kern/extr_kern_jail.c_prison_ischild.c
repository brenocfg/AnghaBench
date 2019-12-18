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
struct prison {struct prison* pr_parent; } ;

/* Variables and functions */

int
prison_ischild(struct prison *pr1, struct prison *pr2)
{

	for (pr2 = pr2->pr_parent; pr2 != NULL; pr2 = pr2->pr_parent)
		if (pr1 == pr2)
			return (1);
	return (0);
}