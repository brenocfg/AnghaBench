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
struct cpuset {int /*<<< orphan*/  cs_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct cpuset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_rel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_zone ; 
 int /*<<< orphan*/  cs_link ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct cpuset*) ; 

__attribute__((used)) static void
cpuset_rel_complete(struct cpuset *set)
{
	LIST_REMOVE(set, cs_link);
	cpuset_rel(set->cs_parent);
	uma_zfree(cpuset_zone, set);
}