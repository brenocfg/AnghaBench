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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_5__ {scalar_t__ target; scalar_t__ state; int rcv_from_other_engine; } ;
struct dbg_tools_data {size_t chip_id; size_t platform_id; TYPE_2__ bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
struct TYPE_6__ {TYPE_1__* per_platform; } ;
struct TYPE_4__ {scalar_t__ num_ports; } ;

/* Variables and functions */
 int CHUNK_SIZE_IN_BYTES ; 
 int DBG_BUS_OTHER_ENGINE_MODE_CROSS_ENGINE_RX ; 
 int DBG_BUS_OTHER_ENGINE_MODE_CROSS_ENGINE_TX ; 
 scalar_t__ DBG_BUS_STATE_READY ; 
 scalar_t__ DBG_BUS_TARGET_ID_INT_BUF ; 
 int DBG_BUS_TARGET_ID_NIG ; 
 int /*<<< orphan*/  DBG_REG_DEBUG_TARGET ; 
 int /*<<< orphan*/  DBG_REG_ETHERNET_HDR_4 ; 
 int /*<<< orphan*/  DBG_REG_ETHERNET_HDR_5 ; 
 int /*<<< orphan*/  DBG_REG_ETHERNET_HDR_6 ; 
 int /*<<< orphan*/  DBG_REG_ETHERNET_HDR_7 ; 
 int /*<<< orphan*/  DBG_REG_ETHERNET_HDR_WIDTH ; 
 int /*<<< orphan*/  DBG_REG_NIG_DATA_LIMIT_SIZE ; 
 int /*<<< orphan*/  DBG_REG_OTHER_ENGINE_MODE_BB_K2 ; 
 int /*<<< orphan*/  DBG_REG_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  DBG_REG_TARGET_PACKET_SIZE ; 
 int DBG_STATUS_DBG_BLOCK_NOT_RESET ; 
 int DBG_STATUS_INVALID_ARGS ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_OUTPUT_ALREADY_SET ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__,int,int,int,int,int) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 scalar_t__ ETH_TYPE ; 
 int NIG_PKT_SIZE_IN_CHUNKS ; 
 int /*<<< orphan*/  NIG_REG_DEBUG_PORT ; 
 int SRC_MAC_ADDR_HI32 ; 
 scalar_t__ SRC_MAC_ADDR_LO16 ; 
 int TARGET_EN_MASK_NIG ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* s_chip_defs ; 

enum dbg_status ecore_dbg_bus_set_nw_output(struct ecore_hwfn *p_hwfn,
											struct ecore_ptt *p_ptt,
											u8 port_id,
											u32 dest_addr_lo32,
											u16 dest_addr_hi16,
											u16 data_limit_size_kb,
											bool send_to_other_engine,
											bool rcv_from_other_engine)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_bus_set_nw_output: port_id = %d, dest_addr_lo32 = 0x%x, dest_addr_hi16 = 0x%x, data_limit_size_kb = %d, send_to_other_engine = %d, rcv_from_other_engine = %d\n", port_id, dest_addr_lo32, dest_addr_hi16, data_limit_size_kb, send_to_other_engine, rcv_from_other_engine);

	if (dev_data->bus.target != DBG_BUS_TARGET_ID_INT_BUF)
		return DBG_STATUS_OUTPUT_ALREADY_SET;
	if (dev_data->bus.state != DBG_BUS_STATE_READY)
		return DBG_STATUS_DBG_BLOCK_NOT_RESET;
	if (port_id >= s_chip_defs[dev_data->chip_id].per_platform[dev_data->platform_id].num_ports || (send_to_other_engine && rcv_from_other_engine))
		return DBG_STATUS_INVALID_ARGS;

	dev_data->bus.target = DBG_BUS_TARGET_ID_NIG;
	dev_data->bus.rcv_from_other_engine = rcv_from_other_engine;

	ecore_wr(p_hwfn, p_ptt, DBG_REG_OUTPUT_ENABLE, TARGET_EN_MASK_NIG);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_DEBUG_TARGET, DBG_BUS_TARGET_ID_NIG);

	if (send_to_other_engine)
		ecore_wr(p_hwfn, p_ptt, DBG_REG_OTHER_ENGINE_MODE_BB_K2, DBG_BUS_OTHER_ENGINE_MODE_CROSS_ENGINE_TX);
	else
		ecore_wr(p_hwfn, p_ptt, NIG_REG_DEBUG_PORT, port_id);

	if (rcv_from_other_engine) {
		ecore_wr(p_hwfn, p_ptt, DBG_REG_OTHER_ENGINE_MODE_BB_K2, DBG_BUS_OTHER_ENGINE_MODE_CROSS_ENGINE_RX);
	}
	else {

		/* Configure ethernet header of 14 bytes */
		ecore_wr(p_hwfn, p_ptt, DBG_REG_ETHERNET_HDR_WIDTH, 0);
		ecore_wr(p_hwfn, p_ptt, DBG_REG_ETHERNET_HDR_7, dest_addr_lo32);
		ecore_wr(p_hwfn, p_ptt, DBG_REG_ETHERNET_HDR_6, (u32)SRC_MAC_ADDR_LO16 | ((u32)dest_addr_hi16 << 16));
		ecore_wr(p_hwfn, p_ptt, DBG_REG_ETHERNET_HDR_5, SRC_MAC_ADDR_HI32);
		ecore_wr(p_hwfn, p_ptt, DBG_REG_ETHERNET_HDR_4, (u32)ETH_TYPE << 16);
		ecore_wr(p_hwfn, p_ptt, DBG_REG_TARGET_PACKET_SIZE, NIG_PKT_SIZE_IN_CHUNKS);
		if (data_limit_size_kb)
			ecore_wr(p_hwfn, p_ptt, DBG_REG_NIG_DATA_LIMIT_SIZE, (data_limit_size_kb * 1024) / CHUNK_SIZE_IN_BYTES);
	}

	return DBG_STATUS_OK;
}