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
struct domainset {int dummy; } ;
struct cpuset {struct domainset* cs_domain; int /*<<< orphan*/  cs_mask; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 struct cpuset* cpuset_getbase (struct cpuset*) ; 
 int cpuset_testshadow (struct cpuset*,int /*<<< orphan*/ *,struct domainset*) ; 

__attribute__((used)) static int
cpuset_setproc_test_maskthread(struct cpuset *tdset, cpuset_t *mask,
    struct domainset *domain)
{
	struct cpuset *parent;

	parent = cpuset_getbase(tdset);
	if (mask == NULL)
		mask = &tdset->cs_mask;
	if (domain == NULL)
		domain = tdset->cs_domain;
	return cpuset_testshadow(parent, mask, domain);
}