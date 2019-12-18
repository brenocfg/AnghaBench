#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct x86_mapping_info {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  efi_system_table_64_t ;
typedef  int /*<<< orphan*/  efi_system_table_32_t ;
struct TYPE_3__ {int efi_systab; scalar_t__ efi_systab_hi; } ;
struct TYPE_4__ {TYPE_1__ efi_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_64BIT ; 
 int /*<<< orphan*/  EFI_BOOT ; 
 TYPE_2__ boot_params ; 
 scalar_t__ efi_enabled (int /*<<< orphan*/ ) ; 
 int kernel_ident_mapping_init (struct x86_mapping_info*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static int
map_efi_systab(struct x86_mapping_info *info, pgd_t *level4p)
{
#ifdef CONFIG_EFI
	unsigned long mstart, mend;

	if (!efi_enabled(EFI_BOOT))
		return 0;

	mstart = (boot_params.efi_info.efi_systab |
			((u64)boot_params.efi_info.efi_systab_hi<<32));

	if (efi_enabled(EFI_64BIT))
		mend = mstart + sizeof(efi_system_table_64_t);
	else
		mend = mstart + sizeof(efi_system_table_32_t);

	if (!mstart)
		return 0;

	return kernel_ident_mapping_init(info, level4p, mstart, mend);
#endif
	return 0;
}