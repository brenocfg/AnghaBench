#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flcdone; scalar_t__ flcerr; } ;
union ich8_hws_flash_status {TYPE_3__ hsf_status; void* regval; } ;
struct TYPE_5__ {int fldbcount; int /*<<< orphan*/  flcycle; } ;
union ich8_hws_flash_ctrl {void* regval; TYPE_2__ hsf_ctrl; } ;
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int flash_base_addr; } ;
struct e1000_hw {TYPE_1__ nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ E1000_ERR_NVM ; 
 int E1000_READ_FLASH_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 void* E1000_READ_FLASH_REG16 (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_FLASH_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  E1000_WRITE_FLASH_REG16 (struct e1000_hw*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ICH_CYCLE_READ ; 
 scalar_t__ ICH_FLASH_CYCLE_REPEAT_COUNT ; 
 int /*<<< orphan*/  ICH_FLASH_FADDR ; 
 int /*<<< orphan*/  ICH_FLASH_FDATA0 ; 
 int /*<<< orphan*/  ICH_FLASH_HSFCTL ; 
 int /*<<< orphan*/  ICH_FLASH_HSFSTS ; 
 int ICH_FLASH_LINEAR_ADDR_MASK ; 
 int /*<<< orphan*/  ICH_FLASH_READ_COMMAND_TIMEOUT ; 
 scalar_t__ e1000_flash_cycle_ich8lan (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_flash_cycle_init_ich8lan (struct e1000_hw*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 e1000_read_flash_data_ich8lan(struct e1000_hw *hw, u32 offset,
					 u8 size, u16 *data)
{
	union ich8_hws_flash_status hsfsts;
	union ich8_hws_flash_ctrl hsflctl;
	u32 flash_linear_addr;
	u32 flash_data = 0;
	s32 ret_val = -E1000_ERR_NVM;
	u8 count = 0;

	DEBUGFUNC("e1000_read_flash_data_ich8lan");

	if (size < 1 || size > 2 || offset > ICH_FLASH_LINEAR_ADDR_MASK)
		return -E1000_ERR_NVM;
	flash_linear_addr = ((ICH_FLASH_LINEAR_ADDR_MASK & offset) +
			     hw->nvm.flash_base_addr);

	do {
		usec_delay(1);
		/* Steps */
		ret_val = e1000_flash_cycle_init_ich8lan(hw);
		if (ret_val != E1000_SUCCESS)
			break;
		hsflctl.regval = E1000_READ_FLASH_REG16(hw, ICH_FLASH_HSFCTL);

		/* 0b/1b corresponds to 1 or 2 byte size, respectively. */
		hsflctl.hsf_ctrl.fldbcount = size - 1;
		hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_READ;
		E1000_WRITE_FLASH_REG16(hw, ICH_FLASH_HSFCTL, hsflctl.regval);
		E1000_WRITE_FLASH_REG(hw, ICH_FLASH_FADDR, flash_linear_addr);

		ret_val = e1000_flash_cycle_ich8lan(hw,
						ICH_FLASH_READ_COMMAND_TIMEOUT);

		/* Check if FCERR is set to 1, if set to 1, clear it
		 * and try the whole sequence a few more times, else
		 * read in (shift in) the Flash Data0, the order is
		 * least significant byte first msb to lsb
		 */
		if (ret_val == E1000_SUCCESS) {
			flash_data = E1000_READ_FLASH_REG(hw, ICH_FLASH_FDATA0);
			if (size == 1)
				*data = (u8)(flash_data & 0x000000FF);
			else if (size == 2)
				*data = (u16)(flash_data & 0x0000FFFF);
			break;
		} else {
			/* If we've gotten here, then things are probably
			 * completely hosed, but if the error condition is
			 * detected, it won't hurt to give it another try...
			 * ICH_FLASH_CYCLE_REPEAT_COUNT times.
			 */
			hsfsts.regval = E1000_READ_FLASH_REG16(hw,
							      ICH_FLASH_HSFSTS);
			if (hsfsts.hsf_status.flcerr) {
				/* Repeat for some time before giving up. */
				continue;
			} else if (!hsfsts.hsf_status.flcdone) {
				DEBUGOUT("Timeout error - flash cycle did not complete.\n");
				break;
			}
		}
	} while (count++ < ICH_FLASH_CYCLE_REPEAT_COUNT);

	return ret_val;
}