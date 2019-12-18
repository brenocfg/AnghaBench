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
typedef  scalar_t__ kvm_pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  E820_TYPE_RAM ; 
 scalar_t__ PageReserved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e820__mapped_raw_any (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_pfn (scalar_t__) ; 
 int /*<<< orphan*/  pat_enabled () ; 
 scalar_t__ pat_pfn_immune_to_uc_mtrr (scalar_t__) ; 
 scalar_t__ pfn_to_hpa (scalar_t__) ; 
 int /*<<< orphan*/  pfn_to_page (scalar_t__) ; 
 scalar_t__ pfn_valid (scalar_t__) ; 

__attribute__((used)) static bool kvm_is_mmio_pfn(kvm_pfn_t pfn)
{
	if (pfn_valid(pfn))
		return !is_zero_pfn(pfn) && PageReserved(pfn_to_page(pfn)) &&
			/*
			 * Some reserved pages, such as those from NVDIMM
			 * DAX devices, are not for MMIO, and can be mapped
			 * with cached memory type for better performance.
			 * However, the above check misconceives those pages
			 * as MMIO, and results in KVM mapping them with UC
			 * memory type, which would hurt the performance.
			 * Therefore, we check the host memory type in addition
			 * and only treat UC/UC-/WC pages as MMIO.
			 */
			(!pat_enabled() || pat_pfn_immune_to_uc_mtrr(pfn));

	return !e820__mapped_raw_any(pfn_to_hpa(pfn),
				     pfn_to_hpa(pfn + 1) - 1,
				     E820_TYPE_RAM);
}