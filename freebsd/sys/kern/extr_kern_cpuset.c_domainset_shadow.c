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
struct domainset {int /*<<< orphan*/  ds_mask; } ;
struct domainlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_AND (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct domainset* LIST_FIRST (struct domainlist*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct domainset*,int /*<<< orphan*/ ) ; 
 struct domainset* _domainset_create (struct domainset*,struct domainlist*) ; 
 int /*<<< orphan*/  domainset_copy (struct domainset const*,struct domainset*) ; 
 int /*<<< orphan*/  ds_link ; 

__attribute__((used)) static struct domainset *
domainset_shadow(const struct domainset *pdomain,
    const struct domainset *domain, struct domainlist *freelist)
{
	struct domainset *ndomain;

	ndomain = LIST_FIRST(freelist);
	LIST_REMOVE(ndomain, ds_link);

	/*
	 * Initialize the key from the request.
	 */
	domainset_copy(domain, ndomain);

	/*
	 * Restrict the key by the parent.
	 */
	DOMAINSET_AND(&ndomain->ds_mask, &pdomain->ds_mask);

	return _domainset_create(ndomain, freelist);
}