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
struct cpuset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuset_getbase (struct cpuset*) ; 
 struct cpuset* cpuset_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cpuset *
cpuset_refbase(struct cpuset *set)
{

	return (cpuset_ref(cpuset_getbase(set)));
}