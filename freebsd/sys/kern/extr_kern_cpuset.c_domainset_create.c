#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct domainset {scalar_t__ ds_policy; int /*<<< orphan*/  ds_mask; int /*<<< orphan*/  ds_prefer; } ;
struct TYPE_2__ {int /*<<< orphan*/  ds_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ DOMAINSET_POLICY_INVALID ; 
 scalar_t__ DOMAINSET_POLICY_MAX ; 
 scalar_t__ DOMAINSET_POLICY_PREFER ; 
 int /*<<< orphan*/  DOMAINSET_SUBSET (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct domainset* _domainset_create (struct domainset*,int /*<<< orphan*/ *) ; 
 TYPE_1__ domainset0 ; 
 int /*<<< orphan*/  domainset_copy (struct domainset const*,struct domainset*) ; 
 int /*<<< orphan*/  domainset_zone ; 
 struct domainset* uma_zalloc (int /*<<< orphan*/ ,int) ; 

struct domainset *
domainset_create(const struct domainset *domain)
{
	struct domainset *ndomain;

	/*
	 * Validate the policy.  It must specify a useable policy number with
	 * only valid domains.  Preferred must include the preferred domain
	 * in the mask.
	 */
	if (domain->ds_policy <= DOMAINSET_POLICY_INVALID ||
	    domain->ds_policy > DOMAINSET_POLICY_MAX)
		return (NULL);
	if (domain->ds_policy == DOMAINSET_POLICY_PREFER &&
	    !DOMAINSET_ISSET(domain->ds_prefer, &domain->ds_mask))
		return (NULL);
	if (!DOMAINSET_SUBSET(&domainset0.ds_mask, &domain->ds_mask))
		return (NULL);
	ndomain = uma_zalloc(domainset_zone, M_WAITOK | M_ZERO);
	domainset_copy(domain, ndomain);
	return _domainset_create(ndomain, NULL);
}