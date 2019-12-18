#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flcerr; int dael; int flcdone; int /*<<< orphan*/  flcinprog; int /*<<< orphan*/  fldesvalid; } ;
union ich8_hws_flash_status {int regval; TYPE_1__ hsf_status; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ E1000_ERR_NVM ; 
 void* E1000_READ_FLASH_REG16 (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_FLASH_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  E1000_WRITE_FLASH_REG16 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ICH_FLASH_HSFSTS ; 
 scalar_t__ ICH_FLASH_READ_COMMAND_TIMEOUT ; 
 scalar_t__ e1000_pch_spt ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 e1000_flash_cycle_init_ich8lan(struct e1000_hw *hw)
{
	union ich8_hws_flash_status hsfsts;
	s32 ret_val = -E1000_ERR_NVM;

	DEBUGFUNC("e1000_flash_cycle_init_ich8lan");

	hsfsts.regval = E1000_READ_FLASH_REG16(hw, ICH_FLASH_HSFSTS);

	/* Check if the flash descriptor is valid */
	if (!hsfsts.hsf_status.fldesvalid) {
		DEBUGOUT("Flash descriptor invalid.  SW Sequencing must be used.\n");
		return -E1000_ERR_NVM;
	}

	/* Clear FCERR and DAEL in hw status by writing 1 */
	hsfsts.hsf_status.flcerr = 1;
	hsfsts.hsf_status.dael = 1;
	if (hw->mac.type >= e1000_pch_spt)
		E1000_WRITE_FLASH_REG(hw, ICH_FLASH_HSFSTS,
				      hsfsts.regval & 0xFFFF);
	else
		E1000_WRITE_FLASH_REG16(hw, ICH_FLASH_HSFSTS, hsfsts.regval);

	/* Either we should have a hardware SPI cycle in progress
	 * bit to check against, in order to start a new cycle or
	 * FDONE bit should be changed in the hardware so that it
	 * is 1 after hardware reset, which can then be used as an
	 * indication whether a cycle is in progress or has been
	 * completed.
	 */

	if (!hsfsts.hsf_status.flcinprog) {
		/* There is no cycle running at present,
		 * so we can start a cycle.
		 * Begin by setting Flash Cycle Done.
		 */
		hsfsts.hsf_status.flcdone = 1;
		if (hw->mac.type >= e1000_pch_spt)
			E1000_WRITE_FLASH_REG(hw, ICH_FLASH_HSFSTS,
					      hsfsts.regval & 0xFFFF);
		else
			E1000_WRITE_FLASH_REG16(hw, ICH_FLASH_HSFSTS,
						hsfsts.regval);
		ret_val = E1000_SUCCESS;
	} else {
		s32 i;

		/* Otherwise poll for sometime so the current
		 * cycle has a chance to end before giving up.
		 */
		for (i = 0; i < ICH_FLASH_READ_COMMAND_TIMEOUT; i++) {
			hsfsts.regval = E1000_READ_FLASH_REG16(hw,
							      ICH_FLASH_HSFSTS);
			if (!hsfsts.hsf_status.flcinprog) {
				ret_val = E1000_SUCCESS;
				break;
			}
			usec_delay(1);
		}
		if (ret_val == E1000_SUCCESS) {
			/* Successful in waiting for previous cycle to timeout,
			 * now set the Flash Cycle Done.
			 */
			hsfsts.hsf_status.flcdone = 1;
			if (hw->mac.type >= e1000_pch_spt)
				E1000_WRITE_FLASH_REG(hw, ICH_FLASH_HSFSTS,
						      hsfsts.regval & 0xFFFF);
			else
				E1000_WRITE_FLASH_REG16(hw, ICH_FLASH_HSFSTS,
							hsfsts.regval);
		} else {
			DEBUGOUT("Flash controller busy, cannot get access\n");
		}
	}

	return ret_val;
}