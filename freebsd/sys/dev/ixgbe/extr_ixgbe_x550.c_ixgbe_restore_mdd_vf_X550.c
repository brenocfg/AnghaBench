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
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_MRQC ; 
 int IXGBE_MRQC_MRQE_MASK ; 
#define  IXGBE_MRQC_VMDQRSS32EN 130 
#define  IXGBE_MRQC_VMDQRT4TCEN 129 
#define  IXGBE_MRQC_VMDQRT8TCEN 128 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WQBR_RX (int) ; 
 int /*<<< orphan*/  IXGBE_WQBR_TX (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 

void ixgbe_restore_mdd_vf_X550(struct ixgbe_hw *hw, u32 vf)
{
	u32 idx, reg, num_qs, start_q, bitmask;

	DEBUGFUNC("ixgbe_restore_mdd_vf_X550");

	/* Map VF to queues */
	reg = IXGBE_READ_REG(hw, IXGBE_MRQC);
	switch (reg & IXGBE_MRQC_MRQE_MASK) {
	case IXGBE_MRQC_VMDQRT8TCEN:
		num_qs = 8;  /* 16 VFs / pools */
		bitmask = 0x000000FF;
		break;
	case IXGBE_MRQC_VMDQRSS32EN:
	case IXGBE_MRQC_VMDQRT4TCEN:
		num_qs = 4;  /* 32 VFs / pools */
		bitmask = 0x0000000F;
		break;
	default:            /* 64 VFs / pools */
		num_qs = 2;
		bitmask = 0x00000003;
		break;
	}
	start_q = vf * num_qs;

	/* Release vf's queues by clearing WQBR_TX and WQBR_RX (RW1C) */
	idx = start_q / 32;
	reg = 0;
	reg |= (bitmask << (start_q % 32));
	IXGBE_WRITE_REG(hw, IXGBE_WQBR_TX(idx), reg);
	IXGBE_WRITE_REG(hw, IXGBE_WQBR_RX(idx), reg);
}