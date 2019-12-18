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
struct cpuset {scalar_t__ cs_id; struct cpuset* cs_parent; } ;

/* Variables and functions */
 scalar_t__ CPUSET_INVALID ; 

__attribute__((used)) static struct cpuset *
cpuset_getbase(struct cpuset *set)
{

	if (set->cs_id == CPUSET_INVALID)
		set = set->cs_parent;
	return (set);
}