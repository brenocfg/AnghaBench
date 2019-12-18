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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int VPD_FAIL ; 
 int VPD_OK ; 
 int /*<<< orphan*/  isalnum (int) ; 

__attribute__((used)) static int vpd_section_check_key_name(const u8 *key, s32 key_len)
{
	int c;

	while (key_len-- > 0) {
		c = *key++;

		if (!isalnum(c) && c != '_')
			return VPD_FAIL;
	}

	return VPD_OK;
}