#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t u_int ;
typedef  TYPE_2__* pmap_t ;
struct TYPE_7__ {TYPE_1__* pm_pcids; } ;
struct TYPE_6__ {scalar_t__ pm_pcid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PMAP_PCID_KERN ; 
 scalar_t__ PMAP_PCID_OVERMAX ; 
 TYPE_2__* kernel_pmap ; 
 int /*<<< orphan*/  pmap_pcid_alloc (TYPE_2__*,size_t) ; 

__attribute__((used)) static uint64_t
pmap_pcid_alloc_checked(pmap_t pmap, u_int cpuid)
{
	uint64_t cached;

	cached = pmap_pcid_alloc(pmap, cpuid);
	KASSERT(pmap->pm_pcids[cpuid].pm_pcid < PMAP_PCID_OVERMAX,
	    ("pmap %p cpu %d pcid %#x", pmap, cpuid,
	    pmap->pm_pcids[cpuid].pm_pcid));
	KASSERT(pmap->pm_pcids[cpuid].pm_pcid != PMAP_PCID_KERN ||
	    pmap == kernel_pmap,
	    ("non-kernel pmap pmap %p cpu %d pcid %#x",
	    pmap, cpuid, pmap->pm_pcids[cpuid].pm_pcid));
	return (cached);
}