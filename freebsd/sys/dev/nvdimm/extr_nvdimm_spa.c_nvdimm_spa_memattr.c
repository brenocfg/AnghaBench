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
typedef  int /*<<< orphan*/  vm_memattr_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int EFI_MD_ATTR_UC ; 
 int EFI_MD_ATTR_WB ; 
 int EFI_MD_ATTR_WC ; 
 int EFI_MD_ATTR_WP ; 
 int EFI_MD_ATTR_WT ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_BACK ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_PROTECTED ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_THROUGH ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static vm_memattr_t
nvdimm_spa_memattr(uint64_t efi_mem_flags)
{
	vm_memattr_t mode;

	if ((efi_mem_flags & EFI_MD_ATTR_WB) != 0)
		mode = VM_MEMATTR_WRITE_BACK;
	else if ((efi_mem_flags & EFI_MD_ATTR_WT) != 0)
		mode = VM_MEMATTR_WRITE_THROUGH;
	else if ((efi_mem_flags & EFI_MD_ATTR_WC) != 0)
		mode = VM_MEMATTR_WRITE_COMBINING;
	else if ((efi_mem_flags & EFI_MD_ATTR_WP) != 0)
		mode = VM_MEMATTR_WRITE_PROTECTED;
	else if ((efi_mem_flags & EFI_MD_ATTR_UC) != 0)
		mode = VM_MEMATTR_UNCACHEABLE;
	else {
		if (bootverbose)
			printf("SPA mapping attr %#lx unsupported\n",
			    efi_mem_flags);
		mode = VM_MEMATTR_UNCACHEABLE;
	}
	return (mode);
}