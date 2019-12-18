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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 scalar_t__ uuid_s_ok ; 
 int /*<<< orphan*/  uuid_to_string (int /*<<< orphan*/  const*,char**,scalar_t__*) ; 

int
efi_guid_to_str(const efi_guid_t *guid, char **sp)
{
	uint32_t status;

	/* knows efi_guid_t is a typedef of uuid_t */
	uuid_to_string(guid, sp, &status);

	return (status == uuid_s_ok ? 0 : -1);
}