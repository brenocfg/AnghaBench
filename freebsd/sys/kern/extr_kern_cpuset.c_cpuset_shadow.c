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
struct setlist {int dummy; } ;
struct domainset {int dummy; } ;
struct domainlist {int dummy; } ;
struct cpuset {struct domainset* cs_domain; int /*<<< orphan*/  cs_mask; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSET_INVALID ; 
 struct cpuset* LIST_FIRST (struct setlist*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct cpuset*,int /*<<< orphan*/ ) ; 
 int _cpuset_create (struct cpuset*,struct cpuset*,int /*<<< orphan*/  const*,struct domainset*,int /*<<< orphan*/ ) ; 
 struct cpuset* cpuset_getbase (struct cpuset*) ; 
 int cpuset_testshadow (struct cpuset*,int /*<<< orphan*/  const*,struct domainset const*) ; 
 int /*<<< orphan*/  cs_link ; 
 struct domainset* domainset_shadow (struct domainset*,struct domainset const*,struct domainlist*) ; 

__attribute__((used)) static int
cpuset_shadow(struct cpuset *set, struct cpuset **nsetp,
   const cpuset_t *mask, const struct domainset *domain,
   struct setlist *cpusets, struct domainlist *domains)
{
	struct cpuset *parent;
	struct cpuset *nset;
	struct domainset *dset;
	struct domainset *d;
	int error;

	error = cpuset_testshadow(set, mask, domain);
	if (error)
		return (error);

	parent = cpuset_getbase(set);
	dset = parent->cs_domain;
	if (mask == NULL)
		mask = &set->cs_mask;
	if (domain != NULL)
		d = domainset_shadow(dset, domain, domains);
	else
		d = set->cs_domain;
	nset = LIST_FIRST(cpusets);
	error = _cpuset_create(nset, parent, mask, d, CPUSET_INVALID);
	if (error == 0) {
		LIST_REMOVE(nset, cs_link);
		*nsetp = nset;
	}
	return (error);
}