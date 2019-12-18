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
typedef  int u8 ;
struct ixgbe_hw_stats {int /*<<< orphan*/ * qbrc; int /*<<< orphan*/ * qprc; int /*<<< orphan*/ * qbtc; int /*<<< orphan*/ * qptc; } ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {scalar_t__ out_overflow_discards; scalar_t__ in_overflow_discards; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int IXGBE_DCB_MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  IXGBE_ERR_PARAM ; 
 int /*<<< orphan*/  IXGBE_QBRC (int) ; 
 int /*<<< orphan*/  IXGBE_QBTC (int) ; 
 int /*<<< orphan*/  IXGBE_QPRC (int) ; 
 int /*<<< orphan*/  IXGBE_QPTC (int) ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 TYPE_1__** tc_stats_array ; 
 size_t up ; 

s32 ixgbe_dcb_get_tc_stats_82598(struct ixgbe_hw *hw,
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
		/* Transmitted Bytes */
		stats->qbtc[tc] += IXGBE_READ_REG(hw, IXGBE_QBTC(tc));
		/* Received Packets */
		stats->qprc[tc] += IXGBE_READ_REG(hw, IXGBE_QPRC(tc));
		/* Received Bytes */
		stats->qbrc[tc] += IXGBE_READ_REG(hw, IXGBE_QBRC(tc));

#if 0
		/* Can we get rid of these??  Consequently, getting rid
		 * of the tc_stats structure.
		 */
		tc_stats_array[up]->in_overflow_discards = 0;
		tc_stats_array[up]->out_overflow_discards = 0;
#endif
	}

	return IXGBE_SUCCESS;
}