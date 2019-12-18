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
typedef  int u32 ;
struct ixgbe_hw {int dummy; } ;
struct TYPE_2__ {int pg_tcs; } ;
struct ixgbe_dcb_config {scalar_t__ vt_mode; TYPE_1__ num_tcs; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_MRQC ; 
 int IXGBE_MRQC_MRQE_MASK ; 
#define  IXGBE_MRQC_RSSEN 130 
#define  IXGBE_MRQC_RT4TCEN 129 
 int IXGBE_MRQC_RT8TCEN ; 
#define  IXGBE_MRQC_RTRSS4TCEN 128 
 int IXGBE_MRQC_RTRSS8TCEN ; 
 int IXGBE_MRQC_VMDQRT4TCEN ; 
 int /*<<< orphan*/  IXGBE_MTQC ; 
 int IXGBE_MTQC_4TC_4TQ ; 
 int IXGBE_MTQC_8TC_8TQ ; 
 int IXGBE_MTQC_RT_ENA ; 
 int IXGBE_MTQC_VT_ENA ; 
 int /*<<< orphan*/  IXGBE_QDE ; 
 int IXGBE_QDE_IDX_SHIFT ; 
 int IXGBE_QDE_WRITE ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RTTDCS ; 
 int IXGBE_RTTDCS_ARBDIS ; 
 int /*<<< orphan*/  IXGBE_SECTXMINIFG ; 
 int IXGBE_SECTX_DCB ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 

s32 ixgbe_dcb_config_82599(struct ixgbe_hw *hw,
			   struct ixgbe_dcb_config *dcb_config)
{
	u32 reg;
	u32 q;

	/* Disable the Tx desc arbiter so that MTQC can be changed */
	reg = IXGBE_READ_REG(hw, IXGBE_RTTDCS);
	reg |= IXGBE_RTTDCS_ARBDIS;
	IXGBE_WRITE_REG(hw, IXGBE_RTTDCS, reg);

	reg = IXGBE_READ_REG(hw, IXGBE_MRQC);
	if (dcb_config->num_tcs.pg_tcs == 8) {
		/* Enable DCB for Rx with 8 TCs */
		switch (reg & IXGBE_MRQC_MRQE_MASK) {
		case 0:
		case IXGBE_MRQC_RT4TCEN:
			/* RSS disabled cases */
			reg = (reg & ~IXGBE_MRQC_MRQE_MASK) |
			      IXGBE_MRQC_RT8TCEN;
			break;
		case IXGBE_MRQC_RSSEN:
		case IXGBE_MRQC_RTRSS4TCEN:
			/* RSS enabled cases */
			reg = (reg & ~IXGBE_MRQC_MRQE_MASK) |
			      IXGBE_MRQC_RTRSS8TCEN;
			break;
		default:
			/*
			 * Unsupported value, assume stale data,
			 * overwrite no RSS
			 */
			ASSERT(0);
			reg = (reg & ~IXGBE_MRQC_MRQE_MASK) |
			      IXGBE_MRQC_RT8TCEN;
		}
	}
	if (dcb_config->num_tcs.pg_tcs == 4) {
		/* We support both VT-on and VT-off with 4 TCs. */
		if (dcb_config->vt_mode)
			reg = (reg & ~IXGBE_MRQC_MRQE_MASK) |
			      IXGBE_MRQC_VMDQRT4TCEN;
		else
			reg = (reg & ~IXGBE_MRQC_MRQE_MASK) |
			      IXGBE_MRQC_RTRSS4TCEN;
	}
	IXGBE_WRITE_REG(hw, IXGBE_MRQC, reg);

	/* Enable DCB for Tx with 8 TCs */
	if (dcb_config->num_tcs.pg_tcs == 8)
		reg = IXGBE_MTQC_RT_ENA | IXGBE_MTQC_8TC_8TQ;
	else {
		/* We support both VT-on and VT-off with 4 TCs. */
		reg = IXGBE_MTQC_RT_ENA | IXGBE_MTQC_4TC_4TQ;
		if (dcb_config->vt_mode)
			reg |= IXGBE_MTQC_VT_ENA;
	}
	IXGBE_WRITE_REG(hw, IXGBE_MTQC, reg);

	/* Disable drop for all queues */
	for (q = 0; q < 128; q++)
		IXGBE_WRITE_REG(hw, IXGBE_QDE,
				(IXGBE_QDE_WRITE | (q << IXGBE_QDE_IDX_SHIFT)));

	/* Enable the Tx desc arbiter */
	reg = IXGBE_READ_REG(hw, IXGBE_RTTDCS);
	reg &= ~IXGBE_RTTDCS_ARBDIS;
	IXGBE_WRITE_REG(hw, IXGBE_RTTDCS, reg);

	/* Enable Security TX Buffer IFG for DCB */
	reg = IXGBE_READ_REG(hw, IXGBE_SECTXMINIFG);
	reg |= IXGBE_SECTX_DCB;
	IXGBE_WRITE_REG(hw, IXGBE_SECTXMINIFG, reg);

	return IXGBE_SUCCESS;
}