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

void ixgbe_mdd_event_X550(struct ixgbe_hw *hw, u32 *vf_bitmap)
{
	u32 wqbr;
	u32 i, j, reg, q, shift, vf, idx;

	DEBUGFUNC("ixgbe_mdd_event_X550");

	/* figure out pool size for mapping to vf's */
	reg = IXGBE_READ_REG(hw, IXGBE_MRQC);
	switch (reg & IXGBE_MRQC_MRQE_MASK) {
	case IXGBE_MRQC_VMDQRT8TCEN:
		shift = 3;  /* 16 VFs / pools */
		break;
	case IXGBE_MRQC_VMDQRSS32EN:
	case IXGBE_MRQC_VMDQRT4TCEN:
		shift = 2;  /* 32 VFs / pools */
		break;
	default:
		shift = 1;  /* 64 VFs / pools */
		break;
	}

	/* Read WQBR_TX and WQBR_RX and check for malicious queues */
	for (i = 0; i < 4; i++) {
		wqbr = IXGBE_READ_REG(hw, IXGBE_WQBR_TX(i));
		wqbr |= IXGBE_READ_REG(hw, IXGBE_WQBR_RX(i));

		if (!wqbr)
			continue;

		/* Get malicious queue */
		for (j = 0; j < 32 && wqbr; j++) {

			if (!(wqbr & (1 << j)))
				continue;

			/* Get queue from bitmask */
			q = j + (i * 32);

			/* Map queue to vf */
			vf = (q >> shift);

			/* Set vf bit in vf_bitmap */
			idx = vf / 32;
			vf_bitmap[idx] |= (1 << (vf % 32));
			wqbr &= ~(1 << j);
		}
	}
}