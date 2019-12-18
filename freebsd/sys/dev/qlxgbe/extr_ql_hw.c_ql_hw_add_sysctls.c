#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_rds_rings; int num_sds_rings; int num_tx_rings; int max_tx_segs; int sds_cidx_thres; int rds_pidx_thres; int rcv_intr_coalesce; int xmt_intr_coalesce; int enable_9kb; int enable_hw_lro; int sp_log_index; int sp_log_stop; int sp_log_stop_events; int mdump_active; int mdump_done; int mdump_capture_mask; int user_pri_nic; int user_pri_iscsi; } ;
struct TYPE_7__ {int txr_idx; int err_inject; TYPE_1__ hw; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_2__ qla_host_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,int,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_sysctl_get_cam_search_mode ; 
 int /*<<< orphan*/  qla_sysctl_port_cfg ; 
 int /*<<< orphan*/  qla_sysctl_set_cam_search_mode ; 
 int /*<<< orphan*/  qla_sysctl_stop_pegs ; 
 int /*<<< orphan*/  qlnx_add_drvr_stats_sysctls (TYPE_2__*) ; 
 int /*<<< orphan*/  qlnx_add_hw_stats_sysctls (TYPE_2__*) ; 

void
ql_hw_add_sysctls(qla_host_t *ha)
{
        device_t	dev;

        dev = ha->pci_dev;

	SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
		SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
		OID_AUTO, "num_rds_rings", CTLFLAG_RD, &ha->hw.num_rds_rings,
		ha->hw.num_rds_rings, "Number of Rcv Descriptor Rings");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "num_sds_rings", CTLFLAG_RD, &ha->hw.num_sds_rings,
		ha->hw.num_sds_rings, "Number of Status Descriptor Rings");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "num_tx_rings", CTLFLAG_RD, &ha->hw.num_tx_rings,
		ha->hw.num_tx_rings, "Number of Transmit Rings");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "tx_ring_index", CTLFLAG_RW, &ha->txr_idx,
		ha->txr_idx, "Tx Ring Used");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "max_tx_segs", CTLFLAG_RD, &ha->hw.max_tx_segs,
		ha->hw.max_tx_segs, "Max # of Segments in a non-TSO pkt");

	ha->hw.sds_cidx_thres = 32;
        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "sds_cidx_thres", CTLFLAG_RW, &ha->hw.sds_cidx_thres,
		ha->hw.sds_cidx_thres,
		"Number of SDS entries to process before updating"
		" SDS Ring Consumer Index");

	ha->hw.rds_pidx_thres = 32;
        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "rds_pidx_thres", CTLFLAG_RW, &ha->hw.rds_pidx_thres,
		ha->hw.rds_pidx_thres,
		"Number of Rcv Rings Entries to post before updating"
		" RDS Ring Producer Index");

        ha->hw.rcv_intr_coalesce = (3 << 16) | 256;
        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "rcv_intr_coalesce", CTLFLAG_RW,
                &ha->hw.rcv_intr_coalesce,
                ha->hw.rcv_intr_coalesce,
                "Rcv Intr Coalescing Parameters\n"
                "\tbits 15:0 max packets\n"
                "\tbits 31:16 max micro-seconds to wait\n"
                "\tplease run\n"
                "\tifconfig <if> down && ifconfig <if> up\n"
                "\tto take effect \n");

        ha->hw.xmt_intr_coalesce = (64 << 16) | 64;
        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "xmt_intr_coalesce", CTLFLAG_RW,
                &ha->hw.xmt_intr_coalesce,
                ha->hw.xmt_intr_coalesce,
                "Xmt Intr Coalescing Parameters\n"
                "\tbits 15:0 max packets\n"
                "\tbits 31:16 max micro-seconds to wait\n"
                "\tplease run\n"
                "\tifconfig <if> down && ifconfig <if> up\n"
                "\tto take effect \n");

        SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "port_cfg", CTLTYPE_INT | CTLFLAG_RW,
                (void *)ha, 0,
                qla_sysctl_port_cfg, "I",
                        "Set Port Configuration if values below "
                        "otherwise Get Port Configuration\n"
                        "\tBits 0-3 ; 1 = DCBX Enable; 0 = DCBX Disable\n"
                        "\tBits 4-7 : 0 = no pause; 1 = std ; 2 = ppm \n"
                        "\tBits 8-11: std pause cfg; 0 = xmt and rcv;"
                        " 1 = xmt only; 2 = rcv only;\n"
                );

	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
		SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
		OID_AUTO, "set_cam_search_mode", CTLTYPE_INT | CTLFLAG_RW,
		(void *)ha, 0,
		qla_sysctl_set_cam_search_mode, "I",
			"Set CAM Search Mode"
			"\t 1 = search mode internal\n"
			"\t 2 = search mode auto\n");

	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
		SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
		OID_AUTO, "get_cam_search_mode", CTLTYPE_INT | CTLFLAG_RW,
		(void *)ha, 0,
		qla_sysctl_get_cam_search_mode, "I",
			"Get CAM Search Mode"
			"\t 1 = search mode internal\n"
			"\t 2 = search mode auto\n");

        ha->hw.enable_9kb = 1;

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "enable_9kb", CTLFLAG_RW, &ha->hw.enable_9kb,
                ha->hw.enable_9kb, "Enable 9Kbyte Buffers when MTU = 9000");

        ha->hw.enable_hw_lro = 1;

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "enable_hw_lro", CTLFLAG_RW, &ha->hw.enable_hw_lro,
                ha->hw.enable_hw_lro, "Enable Hardware LRO; Default is true \n"
		"\t 1 : Hardware LRO if LRO is enabled\n"
		"\t 0 : Software LRO if LRO is enabled\n"
		"\t Any change requires ifconfig down/up to take effect\n"
		"\t Note that LRO may be turned off/on via ifconfig\n");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "sp_log_index", CTLFLAG_RW, &ha->hw.sp_log_index,
                ha->hw.sp_log_index, "sp_log_index");

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "sp_log_stop", CTLFLAG_RW, &ha->hw.sp_log_stop,
                ha->hw.sp_log_stop, "sp_log_stop");

        ha->hw.sp_log_stop_events = 0;

        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "sp_log_stop_events", CTLFLAG_RW,
		&ha->hw.sp_log_stop_events,
                ha->hw.sp_log_stop_events, "Slow path event log is stopped"
		" when OR of the following events occur \n"
		"\t 0x01 : Heart beat Failure\n"
		"\t 0x02 : Temperature Failure\n"
		"\t 0x04 : HW Initialization Failure\n"
		"\t 0x08 : Interface Initialization Failure\n"
		"\t 0x10 : Error Recovery Failure\n");

	ha->hw.mdump_active = 0;
        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "minidump_active", CTLFLAG_RW, &ha->hw.mdump_active,
		ha->hw.mdump_active,
		"Minidump retrieval is Active");

	ha->hw.mdump_done = 0;
        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "mdump_done", CTLFLAG_RW,
		&ha->hw.mdump_done, ha->hw.mdump_done,
		"Minidump has been done and available for retrieval");

	ha->hw.mdump_capture_mask = 0xF;
        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "minidump_capture_mask", CTLFLAG_RW,
		&ha->hw.mdump_capture_mask, ha->hw.mdump_capture_mask,
		"Minidump capture mask");
#ifdef QL_DBG

	ha->err_inject = 0;
        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "err_inject",
                CTLFLAG_RW, &ha->err_inject, ha->err_inject,
                "Error to be injected\n"
                "\t\t\t 0: No Errors\n"
                "\t\t\t 1: rcv: rxb struct invalid\n"
                "\t\t\t 2: rcv: mp == NULL\n"
                "\t\t\t 3: lro: rxb struct invalid\n"
                "\t\t\t 4: lro: mp == NULL\n"
                "\t\t\t 5: rcv: num handles invalid\n"
                "\t\t\t 6: reg: indirect reg rd_wr failure\n"
                "\t\t\t 7: ocm: offchip memory rd_wr failure\n"
                "\t\t\t 8: mbx: mailbox command failure\n"
                "\t\t\t 9: heartbeat failure\n"
                "\t\t\t A: temperature failure\n"
		"\t\t\t 11: m_getcl or m_getjcl failure\n"
		"\t\t\t 13: Invalid Descriptor Count in SGL Receive\n"
		"\t\t\t 14: Invalid Descriptor Count in LRO Receive\n"
		"\t\t\t 15: peer port error recovery failure\n"
		"\t\t\t 16: tx_buf[next_prod_index].mbuf != NULL\n" );

	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "peg_stop", CTLTYPE_INT | CTLFLAG_RW,
                (void *)ha, 0,
                qla_sysctl_stop_pegs, "I", "Peg Stop");

#endif /* #ifdef QL_DBG */

        ha->hw.user_pri_nic = 0;
        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "user_pri_nic", CTLFLAG_RW, &ha->hw.user_pri_nic,
                ha->hw.user_pri_nic,
                "VLAN Tag User Priority for Normal Ethernet Packets");

        ha->hw.user_pri_iscsi = 4;
        SYSCTL_ADD_UINT(device_get_sysctl_ctx(dev),
                SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
                OID_AUTO, "user_pri_iscsi", CTLFLAG_RW, &ha->hw.user_pri_iscsi,
                ha->hw.user_pri_iscsi,
                "VLAN Tag User Priority for iSCSI Packets");

	qlnx_add_hw_stats_sysctls(ha);
	qlnx_add_drvr_stats_sysctls(ha);

	return;
}