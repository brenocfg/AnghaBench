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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  efi_char16_t ;

/* Variables and functions */

__attribute__((used)) static bool
validate_uint16(efi_char16_t *var_name, int match, u8 *buffer,
		unsigned long len)
{
	/* A single 16-bit integer */
	if (len != 2)
		return false;

	return true;
}