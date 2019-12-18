#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int val; int mask; } ;
struct TYPE_5__ {int min; int max; } ;
union dbg_bus_storm_eid_params {TYPE_3__ mask; TYPE_2__ range; } ;
typedef  int u32 ;
struct storm_mode_defs {int id_in_hw; scalar_t__ is_fast_dbg; } ;
struct storm_defs {int sem_fast_mem_addr; int sem_frame_mode_addr; int sem_slow_enable_addr; int sem_slow_mode_addr; int sem_slow_mode1_conf_addr; } ;
struct ecore_ptt {int dummy; } ;
struct TYPE_4__ {struct dbg_bus_storm_data* storms; } ;
struct dbg_tools_data {TYPE_1__ bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct dbg_bus_storm_data {size_t mode; int cid; scalar_t__ eid_range_not_mask; union dbg_bus_storm_eid_params eid_filter_params; scalar_t__ eid_filter_en; scalar_t__ cid_filter_en; } ;
typedef  enum dbg_storms { ____Placeholder_dbg_storms } dbg_storms ;

/* Variables and functions */
 int DBG_BUS_SEMI_FRAME_MODE_0SLOW_4FAST ; 
 int DBG_BUS_SEMI_FRAME_MODE_4SLOW_0FAST ; 
 int SEM_FAST_MODE23_SRC_ENABLE_VAL ; 
 int SEM_FAST_MODE4_SRC_ENABLE_VAL ; 
 int SEM_FAST_MODE6_SRC_ENABLE_VAL ; 
 int SEM_FAST_REG_DBG_MODE23_SRC_DISABLE ; 
 int SEM_FAST_REG_DBG_MODE4_SRC_DISABLE ; 
 int SEM_FAST_REG_DBG_MODE6_SRC_DISABLE ; 
 int SEM_FAST_REG_DEBUG_ACTIVE ; 
 int SEM_FAST_REG_DEBUG_MODE ; 
 int SEM_FAST_REG_EVENT_ID_MASK ; 
 int SEM_FAST_REG_EVENT_ID_RANGE_END ; 
 int SEM_FAST_REG_EVENT_ID_RANGE_STRT ; 
 int SEM_FAST_REG_FILTER_CID ; 
 int SEM_FAST_REG_FILTER_EVENT_ID ; 
 int SEM_FAST_REG_RECORD_FILTER_ENABLE ; 
 int SEM_FILTER_CID_EN_MASK ; 
 int SEM_FILTER_EID_MASK_EN_MASK ; 
 int SEM_FILTER_EID_RANGE_EN_MASK ; 
 int SEM_SLOW_MODE1_DATA_ENABLE ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int,int) ; 
 struct storm_defs* s_storm_defs ; 
 struct storm_mode_defs* s_storm_mode_defs ; 

__attribute__((used)) static void ecore_bus_enable_storm(struct ecore_hwfn *p_hwfn,
								   struct ecore_ptt *p_ptt,
								   enum dbg_storms storm_id)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 base_addr, sem_filter_params = 0;
	struct dbg_bus_storm_data *storm_bus;
	struct storm_mode_defs *storm_mode;
	struct storm_defs *storm;

	storm = &s_storm_defs[storm_id];
	storm_bus = &dev_data->bus.storms[storm_id];
	storm_mode = &s_storm_mode_defs[storm_bus->mode];
	base_addr = storm->sem_fast_mem_addr;

	/* Config SEM */
	if (storm_mode->is_fast_dbg) {

		/* Enable fast debug */
		ecore_wr(p_hwfn, p_ptt, storm->sem_frame_mode_addr, DBG_BUS_SEMI_FRAME_MODE_0SLOW_4FAST);
		ecore_wr(p_hwfn, p_ptt, base_addr + SEM_FAST_REG_DEBUG_MODE, storm_mode->id_in_hw);
		ecore_wr(p_hwfn, p_ptt, base_addr + SEM_FAST_REG_DEBUG_ACTIVE, 1);

		/* Enable messages. Must be done after enabling
		 * SEM_FAST_REG_DEBUG_ACTIVE, otherwise messages will
		 * be dropped after the SEMI sync fifo is filled.
		 */
		ecore_wr(p_hwfn, p_ptt, base_addr + SEM_FAST_REG_DBG_MODE23_SRC_DISABLE, SEM_FAST_MODE23_SRC_ENABLE_VAL);
		ecore_wr(p_hwfn, p_ptt, base_addr + SEM_FAST_REG_DBG_MODE4_SRC_DISABLE, SEM_FAST_MODE4_SRC_ENABLE_VAL);
		ecore_wr(p_hwfn, p_ptt, base_addr + SEM_FAST_REG_DBG_MODE6_SRC_DISABLE, SEM_FAST_MODE6_SRC_ENABLE_VAL);
	}
	else {

		/* Enable slow debug */
		ecore_wr(p_hwfn, p_ptt, storm->sem_frame_mode_addr, DBG_BUS_SEMI_FRAME_MODE_4SLOW_0FAST);
		ecore_wr(p_hwfn, p_ptt, storm->sem_slow_enable_addr, 1);
		ecore_wr(p_hwfn, p_ptt, storm->sem_slow_mode_addr, storm_mode->id_in_hw);
		ecore_wr(p_hwfn, p_ptt, storm->sem_slow_mode1_conf_addr, SEM_SLOW_MODE1_DATA_ENABLE);
	}

	/* Config SEM cid filter */
	if (storm_bus->cid_filter_en) {
		ecore_wr(p_hwfn, p_ptt, base_addr + SEM_FAST_REG_FILTER_CID, storm_bus->cid);
		sem_filter_params |= SEM_FILTER_CID_EN_MASK;
	}

	/* Config SEM eid filter */
	if (storm_bus->eid_filter_en) {
		const union dbg_bus_storm_eid_params *eid_filter = &storm_bus->eid_filter_params;

		if (storm_bus->eid_range_not_mask) {
			ecore_wr(p_hwfn, p_ptt, base_addr + SEM_FAST_REG_EVENT_ID_RANGE_STRT, eid_filter->range.min);
			ecore_wr(p_hwfn, p_ptt, base_addr + SEM_FAST_REG_EVENT_ID_RANGE_END, eid_filter->range.max);
			sem_filter_params |= SEM_FILTER_EID_RANGE_EN_MASK;
		}
		else {
			ecore_wr(p_hwfn, p_ptt, base_addr + SEM_FAST_REG_FILTER_EVENT_ID, eid_filter->mask.val);
			ecore_wr(p_hwfn, p_ptt, base_addr + SEM_FAST_REG_EVENT_ID_MASK, ~eid_filter->mask.mask);
			sem_filter_params |= SEM_FILTER_EID_MASK_EN_MASK;
		}
	}

	/* Config accumulaed SEM filter parameters (if any) */
	if (sem_filter_params)
		ecore_wr(p_hwfn, p_ptt, base_addr + SEM_FAST_REG_RECORD_FILTER_ENABLE, sem_filter_params);
}