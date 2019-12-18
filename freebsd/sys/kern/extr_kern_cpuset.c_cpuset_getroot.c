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
struct cpuset {int cs_flags; struct cpuset* cs_parent; } ;

/* Variables and functions */
 int CPU_SET_ROOT ; 

__attribute__((used)) static struct cpuset *
cpuset_getroot(struct cpuset *set)
{

	while ((set->cs_flags & CPU_SET_ROOT) == 0 && set->cs_parent != NULL)
		set = set->cs_parent;
	return (set);
}