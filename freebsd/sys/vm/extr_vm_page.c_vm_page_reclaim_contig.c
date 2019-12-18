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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  u_long ;
struct vm_domainset_iter {int dummy; } ;

/* Variables and functions */
 scalar_t__ vm_domainset_iter_page (struct vm_domainset_iter*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  vm_domainset_iter_page_init (struct vm_domainset_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*) ; 
 int vm_page_reclaim_contig_domain (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
vm_page_reclaim_contig(int req, u_long npages, vm_paddr_t low, vm_paddr_t high,
    u_long alignment, vm_paddr_t boundary)
{
	struct vm_domainset_iter di;
	int domain;
	bool ret;

	vm_domainset_iter_page_init(&di, NULL, 0, &domain, &req);
	do {
		ret = vm_page_reclaim_contig_domain(domain, req, npages, low,
		    high, alignment, boundary);
		if (ret)
			break;
	} while (vm_domainset_iter_page(&di, NULL, &domain) == 0);

	return (ret);
}