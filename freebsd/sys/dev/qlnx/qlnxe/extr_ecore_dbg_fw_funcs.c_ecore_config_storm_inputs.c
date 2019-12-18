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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct storm_defs {int /*<<< orphan*/  sem_sync_dbg_empty_addr; } ;
struct ecore_ptt {int dummy; } ;
struct dbg_bus_data {scalar_t__ target; struct dbg_bus_storm_data* storms; scalar_t__ one_shot_en; } ;
struct dbg_tools_data {struct dbg_bus_data bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct dbg_bus_storm_data {size_t hw_id; scalar_t__ enabled; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 scalar_t__ DBG_BUS_TARGET_ID_INT_BUF ; 
 scalar_t__ DBG_REG_CALENDAR_SLOT0 ; 
 scalar_t__ DBG_REG_NO_GRANT_ON_FULL ; 
 scalar_t__ DBG_REG_STORM_ID_NUM ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_SEMI_FIFO_NOT_EMPTY ; 
 scalar_t__ DWORDS_TO_BYTES (size_t) ; 
 size_t HW_ID_BITS ; 
 size_t MAX_DBG_STORMS ; 
 size_t NUM_CALENDAR_SLOTS ; 
 int /*<<< orphan*/  ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,size_t) ; 
 struct storm_defs* s_storm_defs ; 

__attribute__((used)) static enum dbg_status ecore_config_storm_inputs(struct ecore_hwfn *p_hwfn,
										  struct ecore_ptt *p_ptt)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct dbg_bus_data *bus = &dev_data->bus;
	u8 storm_id, i, next_storm_id = 0;
	u32 storm_id_mask = 0;

	/* Check if SEMI sync FIFO is empty */
	for (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) {
		struct dbg_bus_storm_data *storm_bus = &bus->storms[storm_id];
		struct storm_defs *storm = &s_storm_defs[storm_id];

		if (storm_bus->enabled && !ecore_rd(p_hwfn, p_ptt, storm->sem_sync_dbg_empty_addr))
			return DBG_STATUS_SEMI_FIFO_NOT_EMPTY;
	}

	for (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) {
		struct dbg_bus_storm_data *storm_bus = &bus->storms[storm_id];

		if (storm_bus->enabled)
			storm_id_mask |= (storm_bus->hw_id << (storm_id * HW_ID_BITS));
	}

	ecore_wr(p_hwfn, p_ptt, DBG_REG_STORM_ID_NUM, storm_id_mask);

	/* Disable storm stall if recording to internal buffer in one-shot */
	ecore_wr(p_hwfn, p_ptt, DBG_REG_NO_GRANT_ON_FULL, (dev_data->bus.target == DBG_BUS_TARGET_ID_INT_BUF && bus->one_shot_en) ? 0 : 1);

	/* Configure calendar */
	for (i = 0; i < NUM_CALENDAR_SLOTS; i++, next_storm_id = (next_storm_id + 1) % MAX_DBG_STORMS) {

		/* Find next enabled Storm */
		for (; !dev_data->bus.storms[next_storm_id].enabled; next_storm_id = (next_storm_id + 1) % MAX_DBG_STORMS);

		/* Configure calendar slot */
		ecore_wr(p_hwfn, p_ptt, DBG_REG_CALENDAR_SLOT0 + DWORDS_TO_BYTES(i), next_storm_id);
	}

	return DBG_STATUS_OK;
}