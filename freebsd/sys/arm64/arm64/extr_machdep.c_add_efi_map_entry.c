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
struct efi_md {int md_type; int md_pages; int /*<<< orphan*/  md_phys; } ;

/* Variables and functions */
#define  EFI_MD_TYPE_BS_CODE 133 
#define  EFI_MD_TYPE_BS_DATA 132 
#define  EFI_MD_TYPE_CODE 131 
#define  EFI_MD_TYPE_DATA 130 
#define  EFI_MD_TYPE_FREE 129 
#define  EFI_MD_TYPE_RT_DATA 128 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  arm_physmem_hardware_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
add_efi_map_entry(struct efi_md *p)
{

	switch (p->md_type) {
	case EFI_MD_TYPE_RT_DATA:
		/*
		 * Runtime data will be excluded after the DMAP
		 * region is created to stop it from being added
		 * to phys_avail.
		 */
	case EFI_MD_TYPE_CODE:
	case EFI_MD_TYPE_DATA:
	case EFI_MD_TYPE_BS_CODE:
	case EFI_MD_TYPE_BS_DATA:
	case EFI_MD_TYPE_FREE:
		/*
		 * We're allowed to use any entry with these types.
		 */
		arm_physmem_hardware_region(p->md_phys,
		    p->md_pages * PAGE_SIZE);
		break;
	}
}