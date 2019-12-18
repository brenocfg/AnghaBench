#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pmap_t ;
struct TYPE_4__ {scalar_t__ pm_type; int /*<<< orphan*/  pm_pkru; } ;

/* Variables and functions */
 int CPUID_STDEXT2_PKU ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PT_X86 ; 
 int cpu_stdext_feature2 ; 
 int /*<<< orphan*/  rangeset_remove_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pmap_pkru_deassign_all(pmap_t pmap)
{

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	if (pmap->pm_type == PT_X86 &&
	    (cpu_stdext_feature2 & CPUID_STDEXT2_PKU) != 0)
		rangeset_remove_all(&pmap->pm_pkru);
}