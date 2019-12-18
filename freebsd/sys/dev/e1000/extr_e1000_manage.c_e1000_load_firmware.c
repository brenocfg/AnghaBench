#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_ERR_CONFIG ; 
 int /*<<< orphan*/  E1000_ERR_HOST_INTERFACE_COMMAND ; 
 int /*<<< orphan*/  E1000_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_FWSM_FW_VALID ; 
 scalar_t__ E1000_FWSM_HI_EN_ONLY_MODE ; 
 int E1000_FWSM_MODE_MASK ; 
 scalar_t__ E1000_FWSM_MODE_SHIFT ; 
 int /*<<< orphan*/  E1000_HIBBA ; 
 int /*<<< orphan*/  E1000_HICR ; 
 int E1000_HICR_C ; 
 int E1000_HICR_EN ; 
 int E1000_HICR_FW_RESET ; 
 int E1000_HICR_FW_RESET_ENABLE ; 
 int E1000_HICR_MEMORY_BASE_EN ; 
 int E1000_HI_COMMAND_TIMEOUT ; 
 int E1000_HI_FW_BASE_ADDRESS ; 
 int E1000_HI_FW_BLOCK_DWORD_LENGTH ; 
 int E1000_HI_FW_MAX_LENGTH ; 
 int /*<<< orphan*/  E1000_HOST_IF ; 
 int E1000_ICR_MNG ; 
 int /*<<< orphan*/  E1000_ICR_V2 ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY_DWORD (struct e1000_hw*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ e1000_i210 ; 
 int /*<<< orphan*/  msec_delay (int) ; 

s32 e1000_load_firmware(struct e1000_hw *hw, u8 *buffer, u32 length)
{
	u32 hicr, hibba, fwsm, icr, i;

	DEBUGFUNC("e1000_load_firmware");

	if (hw->mac.type < e1000_i210) {
		DEBUGOUT("Hardware doesn't support loading FW by the driver\n");
		return -E1000_ERR_CONFIG;
	}

	/* Check that the host interface is enabled. */
	hicr = E1000_READ_REG(hw, E1000_HICR);
	if (!(hicr & E1000_HICR_EN)) {
		DEBUGOUT("E1000_HOST_EN bit disabled.\n");
		return -E1000_ERR_CONFIG;
	}
	if (!(hicr & E1000_HICR_MEMORY_BASE_EN)) {
		DEBUGOUT("E1000_HICR_MEMORY_BASE_EN bit disabled.\n");
		return -E1000_ERR_CONFIG;
	}

	if (length == 0 || length & 0x3 || length > E1000_HI_FW_MAX_LENGTH) {
		DEBUGOUT("Buffer length failure.\n");
		return -E1000_ERR_INVALID_ARGUMENT;
	}

	/* Clear notification from ROM-FW by reading ICR register */
	icr = E1000_READ_REG(hw, E1000_ICR_V2);

	/* Reset ROM-FW */
	hicr = E1000_READ_REG(hw, E1000_HICR);
	hicr |= E1000_HICR_FW_RESET_ENABLE;
	E1000_WRITE_REG(hw, E1000_HICR, hicr);
	hicr |= E1000_HICR_FW_RESET;
	E1000_WRITE_REG(hw, E1000_HICR, hicr);
	E1000_WRITE_FLUSH(hw);

	/* Wait till MAC notifies about its readiness after ROM-FW reset */
	for (i = 0; i < (E1000_HI_COMMAND_TIMEOUT * 2); i++) {
		icr = E1000_READ_REG(hw, E1000_ICR_V2);
		if (icr & E1000_ICR_MNG)
			break;
		msec_delay(1);
	}

	/* Check for timeout */
	if (i == E1000_HI_COMMAND_TIMEOUT) {
		DEBUGOUT("FW reset failed.\n");
		return -E1000_ERR_HOST_INTERFACE_COMMAND;
	}

	/* Wait till MAC is ready to accept new FW code */
	for (i = 0; i < E1000_HI_COMMAND_TIMEOUT; i++) {
		fwsm = E1000_READ_REG(hw, E1000_FWSM);
		if ((fwsm & E1000_FWSM_FW_VALID) &&
		    ((fwsm & E1000_FWSM_MODE_MASK) >> E1000_FWSM_MODE_SHIFT ==
		    E1000_FWSM_HI_EN_ONLY_MODE))
			break;
		msec_delay(1);
	}

	/* Check for timeout */
	if (i == E1000_HI_COMMAND_TIMEOUT) {
		DEBUGOUT("FW reset failed.\n");
		return -E1000_ERR_HOST_INTERFACE_COMMAND;
	}

	/* Calculate length in DWORDs */
	length >>= 2;

	/* The device driver writes the relevant FW code block
	 * into the ram area in DWORDs via 1kB ram addressing window.
	 */
	for (i = 0; i < length; i++) {
		if (!(i % E1000_HI_FW_BLOCK_DWORD_LENGTH)) {
			/* Point to correct 1kB ram window */
			hibba = E1000_HI_FW_BASE_ADDRESS +
				((E1000_HI_FW_BLOCK_DWORD_LENGTH << 2) *
				(i / E1000_HI_FW_BLOCK_DWORD_LENGTH));

			E1000_WRITE_REG(hw, E1000_HIBBA, hibba);
		}

		E1000_WRITE_REG_ARRAY_DWORD(hw, E1000_HOST_IF,
					    i % E1000_HI_FW_BLOCK_DWORD_LENGTH,
					    *((u32 *)buffer + i));
	}

	/* Setting this bit tells the ARC that a new FW is ready to execute. */
	hicr = E1000_READ_REG(hw, E1000_HICR);
	E1000_WRITE_REG(hw, E1000_HICR, hicr | E1000_HICR_C);

	for (i = 0; i < E1000_HI_COMMAND_TIMEOUT; i++) {
		hicr = E1000_READ_REG(hw, E1000_HICR);
		if (!(hicr & E1000_HICR_C))
			break;
		msec_delay(1);
	}

	/* Check for successful FW start. */
	if (i == E1000_HI_COMMAND_TIMEOUT) {
		DEBUGOUT("New FW did not start within timeout period.\n");
		return -E1000_ERR_HOST_INTERFACE_COMMAND;
	}

	return E1000_SUCCESS;
}