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
typedef  int u64 ;
struct ixgbe_hw_stats {int* qbtc; int* qbrc; int /*<<< orphan*/ * qprdc; int /*<<< orphan*/ * qprc; int /*<<< orphan*/ * qptc; } ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int IXGBE_DCB_MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  IXGBE_ERR_PARAM ; 
 int /*<<< orphan*/  IXGBE_QBRC_H (int) ; 
 int /*<<< orphan*/  IXGBE_QBRC_L (int) ; 
 int /*<<< orphan*/  IXGBE_QBTC_H (int) ; 
 int /*<<< orphan*/  IXGBE_QBTC_L (int) ; 
 int /*<<< orphan*/  IXGBE_QPRC (int) ; 
 int /*<<< orphan*/  IXGBE_QPRDC (int) ; 
 int /*<<< orphan*/  IXGBE_QPTC (int) ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 

s32 ixgbe_dcb_get_tc_stats_82599(struct ixgbe_hw *hw,
				 struct ixgbe_hw_stats *stats,
				 u8 tc_count)
{
	int tc;

	DEBUGFUNC("dcb_get_tc_stats");

	if (tc_count > IXGBE_DCB_MAX_TRAFFIC_CLASS)
		return IXGBE_ERR_PARAM;

	/* Statistics pertaining to each traffic class */
	for (tc = 0; tc < tc_count; tc++) {
		/* Transmitted Packets */
		stats->qptc[tc] += IXGBE_READ_REG(hw, IXGBE_QPTC(tc));
		/* Transmitted Bytes (read low first to prevent missed carry) */
		stats->qbtc[tc] += IXGBE_READ_REG(hw, IXGBE_QBTC_L(tc));
		stats->qbtc[tc] +=
			(((u64)(IXGBE_READ_REG(hw, IXGBE_QBTC_H(tc)))) << 32);
		/* Received Packets */
		stats->qprc[tc] += IXGBE_READ_REG(hw, IXGBE_QPRC(tc));
		/* Received Bytes (read low first to prevent missed carry) */
		stats->qbrc[tc] += IXGBE_READ_REG(hw, IXGBE_QBRC_L(tc));
		stats->qbrc[tc] +=
			(((u64)(IXGBE_READ_REG(hw, IXGBE_QBRC_H(tc)))) << 32);

		/* Received Dropped Packet */
		stats->qprdc[tc] += IXGBE_READ_REG(hw, IXGBE_QPRDC(tc));
	}

	return IXGBE_SUCCESS;
}