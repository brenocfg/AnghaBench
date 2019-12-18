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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* init_params ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {int word_size; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int IXGBE_EEPROM_CHECKSUM ; 
 int IXGBE_EEPROM_LAST_WORD ; 
 scalar_t__ IXGBE_EEPROM_SUM ; 
 scalar_t__ IXGBE_ERR_PARAM ; 
 int IXGBE_FW_PTR ; 
 int IXGBE_IXGBE_PCIE_GENERAL_SIZE ; 
 int IXGBE_OPTION_ROM_PTR ; 
 int IXGBE_PCIE_ANALOG_PTR_X550 ; 
#define  IXGBE_PCIE_CONFIG0_PTR 130 
#define  IXGBE_PCIE_CONFIG1_PTR 129 
 int IXGBE_PCIE_CONFIG_SIZE ; 
#define  IXGBE_PCIE_GENERAL_PTR 128 
 int IXGBE_PHY_PTR ; 
 scalar_t__ ixgbe_checksum_ptr_x550 (struct ixgbe_hw*,int,int,int*,int*,int) ; 
 scalar_t__ ixgbe_read_ee_hostif_buffer_X550 (struct ixgbe_hw*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 

s32 ixgbe_calc_checksum_X550(struct ixgbe_hw *hw, u16 *buffer, u32 buffer_size)
{
	u16 eeprom_ptrs[IXGBE_EEPROM_LAST_WORD + 1];
	u16 *local_buffer;
	s32 status;
	u16 checksum = 0;
	u16 pointer, i, size;

	DEBUGFUNC("ixgbe_calc_eeprom_checksum_X550");

	hw->eeprom.ops.init_params(hw);

	if (!buffer) {
		/* Read pointer area */
		status = ixgbe_read_ee_hostif_buffer_X550(hw, 0,
						     IXGBE_EEPROM_LAST_WORD + 1,
						     eeprom_ptrs);
		if (status) {
			DEBUGOUT("Failed to read EEPROM image\n");
			return status;
		}
		local_buffer = eeprom_ptrs;
	} else {
		if (buffer_size < IXGBE_EEPROM_LAST_WORD)
			return IXGBE_ERR_PARAM;
		local_buffer = buffer;
	}

	/*
	 * For X550 hardware include 0x0-0x41 in the checksum, skip the
	 * checksum word itself
	 */
	for (i = 0; i <= IXGBE_EEPROM_LAST_WORD; i++)
		if (i != IXGBE_EEPROM_CHECKSUM)
			checksum += local_buffer[i];

	/*
	 * Include all data from pointers 0x3, 0x6-0xE.  This excludes the
	 * FW, PHY module, and PCIe Expansion/Option ROM pointers.
	 */
	for (i = IXGBE_PCIE_ANALOG_PTR_X550; i < IXGBE_FW_PTR; i++) {
		if (i == IXGBE_PHY_PTR || i == IXGBE_OPTION_ROM_PTR)
			continue;

		pointer = local_buffer[i];

		/* Skip pointer section if the pointer is invalid. */
		if (pointer == 0xFFFF || pointer == 0 ||
		    pointer >= hw->eeprom.word_size)
			continue;

		switch (i) {
		case IXGBE_PCIE_GENERAL_PTR:
			size = IXGBE_IXGBE_PCIE_GENERAL_SIZE;
			break;
		case IXGBE_PCIE_CONFIG0_PTR:
		case IXGBE_PCIE_CONFIG1_PTR:
			size = IXGBE_PCIE_CONFIG_SIZE;
			break;
		default:
			size = 0;
			break;
		}

		status = ixgbe_checksum_ptr_x550(hw, pointer, size, &checksum,
						buffer, buffer_size);
		if (status)
			return status;
	}

	checksum = (u16)IXGBE_EEPROM_SUM - checksum;

	return (s32)checksum;
}