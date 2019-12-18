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
struct agent {scalar_t__ type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agent_cmp_func(const void *a1, const void *a2)
{
   	struct agent const *ap1 = *((struct agent const **)a1);
	struct agent const *ap2 = *((struct agent const **)a2);
	int res;

	res = strcmp(ap1->name, ap2->name);
	if (res == 0) {
		if (ap1->type == ap2->type)
			res = 0;
		else if (ap1->type < ap2->type)
			res = -1;
		else
			res = 1;
	}

	return (res);
}