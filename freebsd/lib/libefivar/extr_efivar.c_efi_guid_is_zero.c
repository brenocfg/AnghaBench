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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 int uuid_is_nil (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int
efi_guid_is_zero(const efi_guid_t *guid)
{
	uint32_t status;

	return uuid_is_nil(guid, &status);
}