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
typedef  int u32 ;
typedef  int u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT2 (char*,int,int) ; 
 scalar_t__ E1000_ERR_NVM ; 
 scalar_t__ E1000_SUCCESS ; 
 scalar_t__ e1000_write_flash_data32_ich8lan (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 e1000_retry_write_flash_dword_ich8lan(struct e1000_hw *hw,
						 u32 offset, u32 dword)
{
	s32 ret_val;
	u16 program_retries;

	DEBUGFUNC("e1000_retry_write_flash_dword_ich8lan");

	/* Must convert word offset into bytes. */
	offset <<= 1;

	ret_val = e1000_write_flash_data32_ich8lan(hw, offset, dword);

	if (!ret_val)
		return ret_val;
	for (program_retries = 0; program_retries < 100; program_retries++) {
		DEBUGOUT2("Retrying Byte %8.8X at offset %u\n", dword, offset);
		usec_delay(100);
		ret_val = e1000_write_flash_data32_ich8lan(hw, offset, dword);
		if (ret_val == E1000_SUCCESS)
			break;
	}
	if (program_retries == 100)
		return -E1000_ERR_NVM;

	return E1000_SUCCESS;
}