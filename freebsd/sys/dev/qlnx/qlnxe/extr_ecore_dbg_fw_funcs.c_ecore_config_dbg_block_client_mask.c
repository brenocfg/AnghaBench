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
typedef  size_t u8 ;
typedef  int u32 ;
struct storm_defs {int* dbg_client_id; } ;
struct ecore_ptt {int dummy; } ;
struct dbg_bus_data {scalar_t__ timestamp_input_en; scalar_t__ grc_input_en; struct dbg_bus_block_data* blocks; scalar_t__ num_enabled_blocks; TYPE_1__* storms; scalar_t__ num_enabled_storms; } ;
struct dbg_tools_data {size_t chip_id; struct dbg_bus_data bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct dbg_bus_block_data {int /*<<< orphan*/  data; } ;
struct block_defs {int* dbg_client_id; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 int BLOCK_DBG ; 
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_ENABLE_MASK ; 
 int DBG_BUS_CLIENT_CPU ; 
 int DBG_BUS_CLIENT_TIMESTAMP ; 
 scalar_t__ GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_BLOCK_ID ; 
 size_t MAX_DBG_STORMS ; 
 int /*<<< orphan*/  ecore_bus_enable_clients (struct ecore_hwfn*,struct ecore_ptt*,int) ; 
 struct block_defs** s_block_defs ; 
 struct storm_defs* s_storm_defs ; 

__attribute__((used)) static void ecore_config_dbg_block_client_mask(struct ecore_hwfn *p_hwfn,
										struct ecore_ptt *p_ptt)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct dbg_bus_data *bus = &dev_data->bus;
	u32 block_id, client_mask = 0;
	u8 storm_id;

	/* Update client mask for Storm inputs */
	if (bus->num_enabled_storms)
		for (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) {
			struct storm_defs *storm = &s_storm_defs[storm_id];

			if (bus->storms[storm_id].enabled)
				client_mask |= (1 << storm->dbg_client_id[dev_data->chip_id]);
		}

	/* Update client mask for block inputs */
	if (bus->num_enabled_blocks) {
		for (block_id = 0; block_id < MAX_BLOCK_ID; block_id++) {
			struct dbg_bus_block_data *block_bus = &bus->blocks[block_id];
			struct block_defs *block = s_block_defs[block_id];

			if (GET_FIELD(block_bus->data, DBG_BUS_BLOCK_DATA_ENABLE_MASK) && block_id != BLOCK_DBG)
				client_mask |= (1 << block->dbg_client_id[dev_data->chip_id]);
		}
	}

	/* Update client mask for GRC input */
	if (bus->grc_input_en)
		client_mask |= (1 << DBG_BUS_CLIENT_CPU);

	/* Update client mask for timestamp input */
	if (bus->timestamp_input_en)
		client_mask |= (1 << DBG_BUS_CLIENT_TIMESTAMP);

	ecore_bus_enable_clients(p_hwfn, p_ptt, client_mask);
}