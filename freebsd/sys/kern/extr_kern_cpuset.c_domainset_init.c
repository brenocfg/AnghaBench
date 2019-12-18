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
struct domainset {int ds_prefer; void* ds_policy; int /*<<< orphan*/  ds_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* DOMAINSET_POLICY_PREFER ; 
 void* DOMAINSET_POLICY_ROUNDROBIN ; 
 int /*<<< orphan*/  DOMAINSET_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DOMAINSET_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _domainset_create (struct domainset*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  all_domains ; 
 struct domainset* domainset_fixed ; 
 struct domainset* domainset_prefer ; 
 struct domainset domainset_roundrobin ; 
 int vm_ndomains ; 

void
domainset_init(void)
{
	struct domainset *dset;
	int i;

	dset = &domainset_roundrobin;
	DOMAINSET_COPY(&all_domains, &dset->ds_mask);
	dset->ds_policy = DOMAINSET_POLICY_ROUNDROBIN;
	dset->ds_prefer = -1;
	_domainset_create(dset, NULL);

	for (i = 0; i < vm_ndomains; i++) {
		dset = &domainset_fixed[i];
		DOMAINSET_ZERO(&dset->ds_mask);
		DOMAINSET_SET(i, &dset->ds_mask);
		dset->ds_policy = DOMAINSET_POLICY_ROUNDROBIN;
		_domainset_create(dset, NULL);

		dset = &domainset_prefer[i];
		DOMAINSET_COPY(&all_domains, &dset->ds_mask);
		dset->ds_policy = DOMAINSET_POLICY_PREFER;
		dset->ds_prefer = i;
		_domainset_create(dset, NULL);
	}
}