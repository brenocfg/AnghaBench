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
struct TYPE_3__ {int link_speed; scalar_t__ num_tcs; } ;
struct TYPE_4__ {TYPE_1__ dmac_config; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ IXGBE_DCB_MAX_TRAFFIC_CLASS ; 
 scalar_t__ IXGBE_DMACRXT_100M ; 
 scalar_t__ IXGBE_DMACRXT_10G ; 
 scalar_t__ IXGBE_DMACRXT_1G ; 
 int /*<<< orphan*/  IXGBE_DMCTH (scalar_t__) ; 
 scalar_t__ IXGBE_DMCTH_DMACRXT_MASK ; 
#define  IXGBE_LINK_SPEED_100_FULL 130 
#define  IXGBE_LINK_SPEED_10_FULL 129 
#define  IXGBE_LINK_SPEED_1GB_FULL 128 
 int /*<<< orphan*/  IXGBE_MAXFRS ; 
 int IXGBE_MHADD_MFS_SHIFT ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RXPBSIZE (scalar_t__) ; 
 scalar_t__ IXGBE_RXPBSIZE_MASK ; 
 scalar_t__ IXGBE_RXPBSIZE_SHIFT ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

s32 ixgbe_dmac_config_tcs_X550(struct ixgbe_hw *hw)
{
	u32 tc, reg, pb_headroom, rx_pb_size, maxframe_size_kb;

	DEBUGFUNC("ixgbe_dmac_config_tcs_X550");

	/* Configure DMA coalescing enabled */
	switch (hw->mac.dmac_config.link_speed) {
	case IXGBE_LINK_SPEED_10_FULL:
	case IXGBE_LINK_SPEED_100_FULL:
		pb_headroom = IXGBE_DMACRXT_100M;
		break;
	case IXGBE_LINK_SPEED_1GB_FULL:
		pb_headroom = IXGBE_DMACRXT_1G;
		break;
	default:
		pb_headroom = IXGBE_DMACRXT_10G;
		break;
	}

	maxframe_size_kb = ((IXGBE_READ_REG(hw, IXGBE_MAXFRS) >>
			     IXGBE_MHADD_MFS_SHIFT) / 1024);

	/* Set the per Rx packet buffer receive threshold */
	for (tc = 0; tc < IXGBE_DCB_MAX_TRAFFIC_CLASS; tc++) {
		reg = IXGBE_READ_REG(hw, IXGBE_DMCTH(tc));
		reg &= ~IXGBE_DMCTH_DMACRXT_MASK;

		if (tc < hw->mac.dmac_config.num_tcs) {
			/* Get Rx PB size */
			rx_pb_size = IXGBE_READ_REG(hw, IXGBE_RXPBSIZE(tc));
			rx_pb_size = (rx_pb_size & IXGBE_RXPBSIZE_MASK) >>
				IXGBE_RXPBSIZE_SHIFT;

			/* Calculate receive buffer threshold in kilobytes */
			if (rx_pb_size > pb_headroom)
				rx_pb_size = rx_pb_size - pb_headroom;
			else
				rx_pb_size = 0;

			/* Minimum of MFS shall be set for DMCTH */
			reg |= (rx_pb_size > maxframe_size_kb) ?
				rx_pb_size : maxframe_size_kb;
		}
		IXGBE_WRITE_REG(hw, IXGBE_DMCTH(tc), reg);
	}
	return IXGBE_SUCCESS;
}