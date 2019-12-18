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
 int /*<<< orphan*/  CPU_SUBSET (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int EINVAL ; 
 struct cpuset* cpuset_getbase (struct cpuset*) ; 
 int /*<<< orphan*/  domainset_valid (struct domainset*,struct domainset const*) ; 

__attribute__((used)) static int
cpuset_testshadow(struct cpuset *set, const cpuset_t *mask,
    const struct domainset *domain)
{
	struct cpuset *parent;
	struct domainset *dset;

	parent = cpuset_getbase(set);
	/*
	 * If we are restricting a cpu mask it must be a subset of the
	 * parent or invalid CPUs have been specified.
	 */
	if (mask != NULL && !CPU_SUBSET(&parent->cs_mask, mask))
		return (EINVAL);

	/*
	 * If we are restricting a domain mask it must be a subset of the
	 * parent or invalid domains have been specified.
	 */
	dset = parent->cs_domain;
	if (domain != NULL && !domainset_valid(dset, domain))
		return (EINVAL);

	return (0);
}