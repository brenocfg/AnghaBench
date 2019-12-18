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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_EEC_BY_MAC (struct ixgbe_hw*) ; 
 scalar_t__ IXGBE_EEC_CS ; 
 scalar_t__ IXGBE_EEC_GNT ; 
 scalar_t__ IXGBE_EEC_REQ ; 
 scalar_t__ IXGBE_EEC_SK ; 
 scalar_t__ IXGBE_EEPROM_GRANT_ATTEMPTS ; 
 scalar_t__ IXGBE_ERR_EEPROM ; 
 scalar_t__ IXGBE_ERR_SWFW_SYNC ; 
 int /*<<< orphan*/  IXGBE_GSSR_EEP_SM ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 ixgbe_acquire_eeprom(struct ixgbe_hw *hw)
{
	s32 status = IXGBE_SUCCESS;
	u32 eec;
	u32 i;

	DEBUGFUNC("ixgbe_acquire_eeprom");

	if (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM)
	    != IXGBE_SUCCESS)
		status = IXGBE_ERR_SWFW_SYNC;

	if (status == IXGBE_SUCCESS) {
		eec = IXGBE_READ_REG(hw, IXGBE_EEC_BY_MAC(hw));

		/* Request EEPROM Access */
		eec |= IXGBE_EEC_REQ;
		IXGBE_WRITE_REG(hw, IXGBE_EEC_BY_MAC(hw), eec);

		for (i = 0; i < IXGBE_EEPROM_GRANT_ATTEMPTS; i++) {
			eec = IXGBE_READ_REG(hw, IXGBE_EEC_BY_MAC(hw));
			if (eec & IXGBE_EEC_GNT)
				break;
			usec_delay(5);
		}

		/* Release if grant not acquired */
		if (!(eec & IXGBE_EEC_GNT)) {
			eec &= ~IXGBE_EEC_REQ;
			IXGBE_WRITE_REG(hw, IXGBE_EEC_BY_MAC(hw), eec);
			DEBUGOUT("Could not acquire EEPROM grant\n");

			hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);
			status = IXGBE_ERR_EEPROM;
		}

		/* Setup EEPROM for Read/Write */
		if (status == IXGBE_SUCCESS) {
			/* Clear CS and SK */
			eec &= ~(IXGBE_EEC_CS | IXGBE_EEC_SK);
			IXGBE_WRITE_REG(hw, IXGBE_EEC_BY_MAC(hw), eec);
			IXGBE_WRITE_FLUSH(hw);
			usec_delay(1);
		}
	}
	return status;
}