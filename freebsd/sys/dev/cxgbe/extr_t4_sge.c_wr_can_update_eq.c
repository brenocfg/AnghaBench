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
struct fw_eth_tx_pkts_wr {int /*<<< orphan*/  op_pkd; } ;

/* Variables and functions */
#define  FW_ETH_TX_PKTS2_WR 132 
#define  FW_ETH_TX_PKTS_WR 131 
#define  FW_ETH_TX_PKT_VM_WR 130 
#define  FW_ETH_TX_PKT_WR 129 
#define  FW_ULPTX_WR 128 
 int G_FW_WR_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
wr_can_update_eq(struct fw_eth_tx_pkts_wr *wr)
{

	switch (G_FW_WR_OP(be32toh(wr->op_pkd))) {
	case FW_ULPTX_WR:
	case FW_ETH_TX_PKT_WR:
	case FW_ETH_TX_PKTS_WR:
	case FW_ETH_TX_PKTS2_WR:
	case FW_ETH_TX_PKT_VM_WR:
		return (1);
	default:
		return (0);
	}
}