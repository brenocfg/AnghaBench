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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct e1000_hw {int dummy; } ;
struct e1000_host_mng_command_header {int /*<<< orphan*/  checksum; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_HOST_IF ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY_DWORD (struct e1000_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_calculate_checksum (int /*<<< orphan*/ *,int) ; 

s32 e1000_mng_write_cmd_header_generic(struct e1000_hw *hw,
				      struct e1000_host_mng_command_header *hdr)
{
	u16 i, length = sizeof(struct e1000_host_mng_command_header);

	DEBUGFUNC("e1000_mng_write_cmd_header_generic");

	/* Write the whole command header structure with new checksum. */

	hdr->checksum = e1000_calculate_checksum((u8 *)hdr, length);

	length >>= 2;
	/* Write the relevant command block into the ram area. */
	for (i = 0; i < length; i++) {
		E1000_WRITE_REG_ARRAY_DWORD(hw, E1000_HOST_IF, i,
					    *((u32 *) hdr + i));
		E1000_WRITE_FLUSH(hw);
	}

	return E1000_SUCCESS;
}