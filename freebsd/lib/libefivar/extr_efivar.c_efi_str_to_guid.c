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
 int /*<<< orphan*/  uuid_from_string (char const*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ uuid_s_ok ; 

int
efi_str_to_guid(const char *s, efi_guid_t *guid)
{
	uint32_t status;

	/* knows efi_guid_t is a typedef of uuid_t */
	uuid_from_string(s, guid, &status);

	return (status == uuid_s_ok ? 0 : -1);
}