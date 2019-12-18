#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pmap_t ;
struct TYPE_8__ {int /*<<< orphan*/ * rs_data_ctx; } ;
struct TYPE_7__ {scalar_t__ pm_type; TYPE_2__ pm_pkru; } ;

/* Variables and functions */
 int CPUID_STDEXT2_PKU ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PT_X86 ; 
 int cpu_stdext_feature2 ; 
 int rangeset_copy (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static int
pmap_pkru_copy(pmap_t dst_pmap, pmap_t src_pmap)
{

	PMAP_LOCK_ASSERT(dst_pmap, MA_OWNED);
	PMAP_LOCK_ASSERT(src_pmap, MA_OWNED);
	MPASS(dst_pmap->pm_type == PT_X86);
	MPASS(src_pmap->pm_type == PT_X86);
	MPASS((cpu_stdext_feature2 & CPUID_STDEXT2_PKU) != 0);
	if (src_pmap->pm_pkru.rs_data_ctx == NULL)
		return (0);
	return (rangeset_copy(&dst_pmap->pm_pkru, &src_pmap->pm_pkru));
}