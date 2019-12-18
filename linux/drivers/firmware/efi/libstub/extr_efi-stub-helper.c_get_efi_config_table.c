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
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 scalar_t__ efi_is_64bit () ; 
 void* get_efi_config_table32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* get_efi_config_table64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *get_efi_config_table(efi_system_table_t *sys_table, efi_guid_t guid)
{
	if (efi_is_64bit())
		return get_efi_config_table64(sys_table, guid);
	else
		return get_efi_config_table32(sys_table, guid);
}