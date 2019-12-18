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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct dbg_bus_data {scalar_t__ state; scalar_t__ target; struct dbg_bus_storm_data* storms; TYPE_2__* blocks; scalar_t__ trigger_en; scalar_t__ filter_en; scalar_t__ num_enabled_storms; scalar_t__ num_enabled_blocks; TYPE_1__ pci_buf; } ;
struct dbg_tools_data {struct dbg_bus_data bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct dbg_bus_storm_data {int enabled; scalar_t__ cid_filter_en; scalar_t__ eid_filter_en; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 size_t BLOCK_PCIE ; 
 scalar_t__ CHUNK_SIZE_IN_DWORDS ; 
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_ENABLE_MASK ; 
 scalar_t__ DBG_BUS_STATE_IDLE ; 
 scalar_t__ DBG_BUS_STATE_RECORDING ; 
 scalar_t__ DBG_BUS_STATE_STOPPED ; 
 scalar_t__ DBG_BUS_TARGET_ID_NIG ; 
 scalar_t__ DBG_BUS_TARGET_ID_PCI ; 
 int DBG_STATUS_DUMP_BUF_TOO_SMALL ; 
 int DBG_STATUS_DUMP_NOT_CHUNK_ALIGNED ; 
 int DBG_STATUS_NO_DATA_RECORDED ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_PCI_BUF_NOT_ALLOCATED ; 
 int DBG_STATUS_RECORDING_NOT_STARTED ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 scalar_t__ MAX_BLOCK_ID ; 
 size_t MAX_DBG_STORMS ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_bus_dump_data (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__*,int) ; 
 scalar_t__ ecore_bus_dump_hdr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__*,int) ; 
 int /*<<< orphan*/  ecore_bus_free_pci_buf (struct ecore_hwfn*) ; 
 int ecore_dbg_bus_get_dump_buf_size (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__*) ; 
 int ecore_dbg_bus_stop (struct ecore_hwfn*,struct ecore_ptt*) ; 
 scalar_t__ ecore_dump_last_section (scalar_t__*,scalar_t__,int) ; 

enum dbg_status ecore_dbg_bus_dump(struct ecore_hwfn *p_hwfn,
								   struct ecore_ptt *p_ptt,
								   u32 *dump_buf,
								   u32 buf_size_in_dwords,
								   u32 *num_dumped_dwords)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 min_buf_size_in_dwords, block_id, offset = 0;
	struct dbg_bus_data *bus = &dev_data->bus;
	enum dbg_status status;
	u8 storm_id;

	*num_dumped_dwords = 0;

	status = ecore_dbg_bus_get_dump_buf_size(p_hwfn, p_ptt, &min_buf_size_in_dwords);
	if (status != DBG_STATUS_OK)
		return status;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_bus_dump: dump_buf = 0x%p, buf_size_in_dwords = %d\n", dump_buf, buf_size_in_dwords);

	if (bus->state != DBG_BUS_STATE_RECORDING && bus->state != DBG_BUS_STATE_STOPPED)
		return DBG_STATUS_RECORDING_NOT_STARTED;

	if (bus->state == DBG_BUS_STATE_RECORDING) {
		enum dbg_status stop_state = ecore_dbg_bus_stop(p_hwfn, p_ptt);
		if (stop_state != DBG_STATUS_OK)
			return stop_state;
	}

	if (buf_size_in_dwords < min_buf_size_in_dwords)
		return DBG_STATUS_DUMP_BUF_TOO_SMALL;

	if (bus->target == DBG_BUS_TARGET_ID_PCI && !bus->pci_buf.size)
		return DBG_STATUS_PCI_BUF_NOT_ALLOCATED;

	/* Dump header */
	offset += ecore_bus_dump_hdr(p_hwfn, p_ptt, dump_buf + offset, true);

	/* Dump recorded data */
	if (bus->target != DBG_BUS_TARGET_ID_NIG) {
		u32 recorded_dwords = ecore_bus_dump_data(p_hwfn, p_ptt, dump_buf + offset, true);

		if (!recorded_dwords)
			return DBG_STATUS_NO_DATA_RECORDED;
		if (recorded_dwords % CHUNK_SIZE_IN_DWORDS)
			return DBG_STATUS_DUMP_NOT_CHUNK_ALIGNED;
		offset += recorded_dwords;
	}

	/* Dump last section */
	offset += ecore_dump_last_section(dump_buf, offset, true);

	/* If recorded to PCI buffer - free the buffer */
	ecore_bus_free_pci_buf(p_hwfn);

	/* Clear debug bus parameters */
	bus->state = DBG_BUS_STATE_IDLE;
	bus->num_enabled_blocks = 0;
	bus->num_enabled_storms = 0;
	bus->filter_en = bus->trigger_en = 0;

	for (block_id = 0; block_id < MAX_BLOCK_ID; block_id++)
		SET_FIELD(bus->blocks[BLOCK_PCIE].data, DBG_BUS_BLOCK_DATA_ENABLE_MASK, 0);

	for (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) {
		struct dbg_bus_storm_data *storm_bus = &bus->storms[storm_id];

		storm_bus->enabled = false;
		storm_bus->eid_filter_en = storm_bus->cid_filter_en = 0;
	}

	*num_dumped_dwords = offset;

	return DBG_STATUS_OK;
}