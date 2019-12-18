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
struct domainset {int* ds_order; scalar_t__ ds_policy; int ds_prefer; int /*<<< orphan*/  ds_mask; int /*<<< orphan*/  ds_cnt; } ;
typedef  int /*<<< orphan*/  domainset_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_COUNT (int /*<<< orphan*/ *) ; 
 int DOMAINSET_FLS (int /*<<< orphan*/ *) ; 
 scalar_t__ DOMAINSET_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DOMAINSET_NAND (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DOMAINSET_POLICY_PREFER ; 
 scalar_t__ DOMAINSET_POLICY_ROUNDROBIN ; 
 int /*<<< orphan*/  DOMAINSET_SET (int,int /*<<< orphan*/ *) ; 
 scalar_t__ DOMAINSET_SUBSET (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DOMAINSET_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ VM_DOMAIN_EMPTY (int) ; 
 int vm_ndomains ; 

__attribute__((used)) static bool
domainset_empty_vm(struct domainset *domain)
{
	domainset_t empty;
	int i, j;

	DOMAINSET_ZERO(&empty);
	for (i = 0; i < vm_ndomains; i++)
		if (VM_DOMAIN_EMPTY(i))
			DOMAINSET_SET(i, &empty);
	if (DOMAINSET_SUBSET(&empty, &domain->ds_mask))
		return (true);

	/* Remove empty domains from the set and recompute. */
	DOMAINSET_NAND(&domain->ds_mask, &empty);
	domain->ds_cnt = DOMAINSET_COUNT(&domain->ds_mask);
	for (i = j = 0; i < DOMAINSET_FLS(&domain->ds_mask); i++)
		if (DOMAINSET_ISSET(i, &domain->ds_mask))
			domain->ds_order[j++] = i;

	/* Convert a PREFER policy referencing an empty domain to RR. */
	if (domain->ds_policy == DOMAINSET_POLICY_PREFER &&
	    DOMAINSET_ISSET(domain->ds_prefer, &empty)) {
		domain->ds_policy = DOMAINSET_POLICY_ROUNDROBIN;
		domain->ds_prefer = -1;
	}

	return (false);
}