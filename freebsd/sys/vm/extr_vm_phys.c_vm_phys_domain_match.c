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
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  domainset_t ;
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 scalar_t__ DOMAINSET_EMPTY (int /*<<< orphan*/ *) ; 
 int DOMAINSET_FFS (int /*<<< orphan*/ *) ; 
 scalar_t__ DOMAINSET_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DOMAINSET_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DOMAINSET_ZERO (int /*<<< orphan*/ *) ; 
 TYPE_1__* mem_affinity ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vm_ndomains ; 

int
vm_phys_domain_match(int prefer, vm_paddr_t low, vm_paddr_t high)
{
#ifdef NUMA
	domainset_t mask;
	int i;

	if (vm_ndomains == 1 || mem_affinity == NULL)
		return (0);

	DOMAINSET_ZERO(&mask);
	/*
	 * Check for any memory that overlaps low, high.
	 */
	for (i = 0; mem_affinity[i].end != 0; i++)
		if (mem_affinity[i].start <= high &&
		    mem_affinity[i].end >= low)
			DOMAINSET_SET(mem_affinity[i].domain, &mask);
	if (prefer != -1 && DOMAINSET_ISSET(prefer, &mask))
		return (prefer);
	if (DOMAINSET_EMPTY(&mask))
		panic("vm_phys_domain_match:  Impossible constraint");
	return (DOMAINSET_FFS(&mask) - 1);
#else
	return (0);
#endif
}