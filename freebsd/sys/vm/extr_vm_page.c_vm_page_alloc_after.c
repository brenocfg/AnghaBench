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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct vm_domainset_iter {int dummy; } ;

/* Variables and functions */
 scalar_t__ vm_domainset_iter_page (struct vm_domainset_iter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vm_domainset_iter_page_init (struct vm_domainset_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/ * vm_page_alloc_domain_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

vm_page_t
vm_page_alloc_after(vm_object_t object, vm_pindex_t pindex,
    int req, vm_page_t mpred)
{
	struct vm_domainset_iter di;
	vm_page_t m;
	int domain;

	vm_domainset_iter_page_init(&di, object, pindex, &domain, &req);
	do {
		m = vm_page_alloc_domain_after(object, pindex, domain, req,
		    mpred);
		if (m != NULL)
			break;
	} while (vm_domainset_iter_page(&di, object, &domain) == 0);

	return (m);
}