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
struct ixgbevf_hw_stats {int /*<<< orphan*/  vfmprc; int /*<<< orphan*/  vfgotc; int /*<<< orphan*/  vfgorc; int /*<<< orphan*/  vfgptc; int /*<<< orphan*/  vfgprc; int /*<<< orphan*/  last_vfmprc; int /*<<< orphan*/  last_vfgotc; int /*<<< orphan*/  last_vfgorc; int /*<<< orphan*/  last_vfgptc; int /*<<< orphan*/  last_vfgprc; } ;
struct ixgbe_hw {int dummy; } ;
struct TYPE_2__ {struct ixgbevf_hw_stats vf; } ;
struct adapter {TYPE_1__ stats; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_SET_IBYTES (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SET_IMCASTS (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SET_IPACKETS (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SET_OBYTES (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SET_OPACKETS (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VFGORC_LSB ; 
 int /*<<< orphan*/  IXGBE_VFGORC_MSB ; 
 int /*<<< orphan*/  IXGBE_VFGOTC_LSB ; 
 int /*<<< orphan*/  IXGBE_VFGOTC_MSB ; 
 int /*<<< orphan*/  IXGBE_VFGPRC ; 
 int /*<<< orphan*/  IXGBE_VFGPTC ; 
 int /*<<< orphan*/  IXGBE_VFMPRC ; 
 int /*<<< orphan*/  UPDATE_STAT_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_STAT_36 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ixv_update_stats(struct adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct ixgbevf_hw_stats *stats = &adapter->stats.vf;

	UPDATE_STAT_32(IXGBE_VFGPRC, adapter->stats.vf.last_vfgprc,
	    adapter->stats.vf.vfgprc);
	UPDATE_STAT_32(IXGBE_VFGPTC, adapter->stats.vf.last_vfgptc,
	    adapter->stats.vf.vfgptc);
	UPDATE_STAT_36(IXGBE_VFGORC_LSB, IXGBE_VFGORC_MSB,
	    adapter->stats.vf.last_vfgorc, adapter->stats.vf.vfgorc);
	UPDATE_STAT_36(IXGBE_VFGOTC_LSB, IXGBE_VFGOTC_MSB,
	    adapter->stats.vf.last_vfgotc, adapter->stats.vf.vfgotc);
	UPDATE_STAT_32(IXGBE_VFMPRC, adapter->stats.vf.last_vfmprc,
	    adapter->stats.vf.vfmprc);

	/* Fill out the OS statistics structure */
	IXGBE_SET_IPACKETS(adapter, stats->vfgprc);
	IXGBE_SET_OPACKETS(adapter, stats->vfgptc);
	IXGBE_SET_IBYTES(adapter, stats->vfgorc);
	IXGBE_SET_OBYTES(adapter, stats->vfgotc);
	IXGBE_SET_IMCASTS(adapter, stats->vfmprc);
}