#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ clear_semaphore_once; } ;
struct TYPE_6__ {int smb_counter; } ;
struct TYPE_8__ {TYPE_3__ _82575; TYPE_2__ _82571; } ;
struct TYPE_5__ {int word_size; } ;
struct e1000_hw {TYPE_4__ dev_spec; TYPE_1__ nvm; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int E1000_ERR_NVM ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_SWSM ; 
 int E1000_SWSM_SMBI ; 
 int E1000_SWSM_SWESMBI ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  e1000_put_hw_semaphore (struct e1000_hw*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

s32 e1000_get_hw_semaphore(struct e1000_hw *hw)
{
	u32 swsm;
	s32 fw_timeout = hw->nvm.word_size + 1;
	s32 sw_timeout = hw->nvm.word_size + 1;
	s32 i = 0;
	
	DEBUGFUNC("e1000_get_hw_semaphore");

	/* _82571 */
	/* If we have timedout 3 times on trying to acquire
	 * the inter-port SMBI semaphore, there is old code
	 * operating on the other port, and it is not
	 * releasing SMBI. Modify the number of times that
	 * we try for the semaphore to interwork with this
	 * older code.
	 */
	if (hw->dev_spec._82571.smb_counter > 2)
		sw_timeout = 1;


	/* Get the SW semaphore */
	while (i < sw_timeout) {
		swsm = E1000_READ_REG(hw, E1000_SWSM);
		if (!(swsm & E1000_SWSM_SMBI))
			break;

		usec_delay(50);
		i++;
	}

	if (i == sw_timeout) {
		DEBUGOUT("Driver can't access device - SMBI bit is set.\n");
		hw->dev_spec._82571.smb_counter++;
	}

	/* In rare circumstances, the SW semaphore may already be held
	 * unintentionally. Clear the semaphore once before giving up.
	 */
         if (hw->dev_spec._82575.clear_semaphore_once) {
         	hw->dev_spec._82575.clear_semaphore_once = FALSE;
         	e1000_put_hw_semaphore(hw);
         	for (i = 0; i < fw_timeout; i++) {
         		swsm = E1000_READ_REG(hw, E1000_SWSM);
         		if (!(swsm & E1000_SWSM_SMBI))
         			break;

         		usec_delay(50);
         	}
         }

	/* Get the FW semaphore. */
	for (i = 0; i < fw_timeout; i++) {
		swsm = E1000_READ_REG(hw, E1000_SWSM);
		E1000_WRITE_REG(hw, E1000_SWSM, swsm | E1000_SWSM_SWESMBI);

		/* Semaphore acquired if bit latched */
		if (E1000_READ_REG(hw, E1000_SWSM) & E1000_SWSM_SWESMBI)
			break;

		usec_delay(50);
	}

	if (i == fw_timeout) {
		/* Release semaphores */
		e1000_put_hw_semaphore(hw);
		DEBUGOUT("Driver can't access the NVM\n");
		return -E1000_ERR_NVM;
	}

	return E1000_SUCCESS;
}