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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 int EFI_VARIABLE_APPEND_WRITE ; 
 int efi_set_variable (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,size_t,int) ; 

int
efi_append_variable(efi_guid_t guid, const char *name,
    uint8_t *data, size_t data_size, uint32_t attributes)
{

	return efi_set_variable(guid, name, data, data_size,
	    attributes | EFI_VARIABLE_APPEND_WRITE);
}