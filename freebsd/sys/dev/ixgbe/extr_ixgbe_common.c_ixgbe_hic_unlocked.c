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
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int /*<<< orphan*/  ERROR_REPORT1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IXGBE_CPU_TO_LE32 (int) ; 
 int /*<<< orphan*/  IXGBE_ERROR_CAUTION ; 
 int /*<<< orphan*/  IXGBE_ERR_HOST_INTERFACE_COMMAND ; 
 int /*<<< orphan*/  IXGBE_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  IXGBE_FLEX_MNG ; 
 int /*<<< orphan*/  IXGBE_FWSTS ; 
 int IXGBE_FWSTS_FWRI ; 
 int /*<<< orphan*/  IXGBE_HICR ; 
 int IXGBE_HICR_C ; 
 int IXGBE_HICR_EN ; 
 int IXGBE_HICR_SV ; 
 int IXGBE_HI_MAX_BLOCK_BYTE_LENGTH ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG_ARRAY (struct ixgbe_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

s32 ixgbe_hic_unlocked(struct ixgbe_hw *hw, u32 *buffer, u32 length,
		       u32 timeout)
{
	u32 hicr, i, fwsts;
	u16 dword_len;

	DEBUGFUNC("ixgbe_hic_unlocked");

	if (!length || length > IXGBE_HI_MAX_BLOCK_BYTE_LENGTH) {
		DEBUGOUT1("Buffer length failure buffersize=%d.\n", length);
		return IXGBE_ERR_HOST_INTERFACE_COMMAND;
	}

	/* Set bit 9 of FWSTS clearing FW reset indication */
	fwsts = IXGBE_READ_REG(hw, IXGBE_FWSTS);
	IXGBE_WRITE_REG(hw, IXGBE_FWSTS, fwsts | IXGBE_FWSTS_FWRI);

	/* Check that the host interface is enabled. */
	hicr = IXGBE_READ_REG(hw, IXGBE_HICR);
	if (!(hicr & IXGBE_HICR_EN)) {
		DEBUGOUT("IXGBE_HOST_EN bit disabled.\n");
		return IXGBE_ERR_HOST_INTERFACE_COMMAND;
	}

	/* Calculate length in DWORDs. We must be DWORD aligned */
	if (length % sizeof(u32)) {
		DEBUGOUT("Buffer length failure, not aligned to dword");
		return IXGBE_ERR_INVALID_ARGUMENT;
	}

	dword_len = length >> 2;

	/* The device driver writes the relevant command block
	 * into the ram area.
	 */
	for (i = 0; i < dword_len; i++)
		IXGBE_WRITE_REG_ARRAY(hw, IXGBE_FLEX_MNG,
				      i, IXGBE_CPU_TO_LE32(buffer[i]));

	/* Setting this bit tells the ARC that a new command is pending. */
	IXGBE_WRITE_REG(hw, IXGBE_HICR, hicr | IXGBE_HICR_C);

	for (i = 0; i < timeout; i++) {
		hicr = IXGBE_READ_REG(hw, IXGBE_HICR);
		if (!(hicr & IXGBE_HICR_C))
			break;
		msec_delay(1);
	}

	/* Check command completion */
	if ((timeout && i == timeout) ||
	    !(IXGBE_READ_REG(hw, IXGBE_HICR) & IXGBE_HICR_SV)) {
		ERROR_REPORT1(IXGBE_ERROR_CAUTION,
			     "Command has failed with no status valid.\n");
		return IXGBE_ERR_HOST_INTERFACE_COMMAND;
	}

	return IXGBE_SUCCESS;
}