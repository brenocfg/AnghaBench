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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int IXGBE_MAX_PACKET_BUFFERS ; 
 int /*<<< orphan*/  IXGBE_RXPBSIZE (int) ; 
 int /*<<< orphan*/  IXGBE_RXPBSIZE_48KB ; 
 int /*<<< orphan*/  IXGBE_RXPBSIZE_64KB ; 
 int /*<<< orphan*/  IXGBE_RXPBSIZE_80KB ; 
 int /*<<< orphan*/  IXGBE_TXPBSIZE (int) ; 
 int /*<<< orphan*/  IXGBE_TXPBSIZE_40KB ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PBA_STRATEGY_EQUAL 129 
#define  PBA_STRATEGY_WEIGHTED 128 
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_set_rxpba_82598(struct ixgbe_hw *hw, int num_pb,
				  u32 headroom, int strategy)
{
	u32 rxpktsize = IXGBE_RXPBSIZE_64KB;
	u8 i = 0;
	UNREFERENCED_1PARAMETER(headroom);

	if (!num_pb)
		return;

	/* Setup Rx packet buffer sizes */
	switch (strategy) {
	case PBA_STRATEGY_WEIGHTED:
		/* Setup the first four at 80KB */
		rxpktsize = IXGBE_RXPBSIZE_80KB;
		for (; i < 4; i++)
			IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(i), rxpktsize);
		/* Setup the last four at 48KB...don't re-init i */
		rxpktsize = IXGBE_RXPBSIZE_48KB;
		/* Fall Through */
	case PBA_STRATEGY_EQUAL:
	default:
		/* Divide the remaining Rx packet buffer evenly among the TCs */
		for (; i < IXGBE_MAX_PACKET_BUFFERS; i++)
			IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(i), rxpktsize);
		break;
	}

	/* Setup Tx packet buffer sizes */
	for (i = 0; i < IXGBE_MAX_PACKET_BUFFERS; i++)
		IXGBE_WRITE_REG(hw, IXGBE_TXPBSIZE(i), IXGBE_TXPBSIZE_40KB);
}