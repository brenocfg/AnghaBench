#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {scalar_t__ fw_vendor; scalar_t__ runtime; scalar_t__ config_table; } ;
struct TYPE_7__ {struct attribute attr; } ;
struct TYPE_6__ {struct attribute attr; } ;
struct TYPE_5__ {struct attribute attr; } ;

/* Variables and functions */
 scalar_t__ EFI_INVALID_TABLE_ADDR ; 
 int /*<<< orphan*/  EFI_PARAVIRT ; 
 TYPE_4__ efi ; 
 TYPE_3__ efi_attr_config_table ; 
 TYPE_2__ efi_attr_fw_vendor ; 
 TYPE_1__ efi_attr_runtime ; 
 scalar_t__ efi_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static umode_t efi_attr_is_visible(struct kobject *kobj,
				   struct attribute *attr, int n)
{
	if (attr == &efi_attr_fw_vendor.attr) {
		if (efi_enabled(EFI_PARAVIRT) ||
				efi.fw_vendor == EFI_INVALID_TABLE_ADDR)
			return 0;
	} else if (attr == &efi_attr_runtime.attr) {
		if (efi.runtime == EFI_INVALID_TABLE_ADDR)
			return 0;
	} else if (attr == &efi_attr_config_table.attr) {
		if (efi.config_table == EFI_INVALID_TABLE_ADDR)
			return 0;
	}

	return attr->mode;
}