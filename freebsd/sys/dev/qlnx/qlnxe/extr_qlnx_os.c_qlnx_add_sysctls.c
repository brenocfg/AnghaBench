#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_7__ {int personality; int dbg_level; int dp_level; int dbg_trace_lro_cnt; int dbg_trace_tso_pkt_len; int dp_module; int err_inject; int storm_stats_enable; int storm_stats_index; int grcdump_taken; int idle_chk_taken; int rx_coalesce_usecs; int tx_coalesce_usecs; int rx_pkt_threshold; int rx_jumbo_buf_eq_mtu; int /*<<< orphan*/  err_get_proto_invalid_type; int /*<<< orphan*/  err_fp_null; int /*<<< orphan*/  err_illegal_intr; int /*<<< orphan*/  mfw_ver; int /*<<< orphan*/  stormfw_ver; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_1__ qlnx_host_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_QUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int*,int,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnx_add_fp_stats_sysctls (TYPE_1__*) ; 
 int /*<<< orphan*/  qlnx_add_hw_stats_sysctls (TYPE_1__*) ; 
 int /*<<< orphan*/  qlnx_add_sp_stats_sysctls (TYPE_1__*) ; 
 int /*<<< orphan*/  qlnx_set_rx_coalesce ; 
 int /*<<< orphan*/  qlnx_set_tx_coalesce ; 
 int /*<<< orphan*/  qlnx_trigger_dump_sysctl ; 
 int /*<<< orphan*/  qlnx_ver_str ; 
 scalar_t__ qlnx_vf_device (TYPE_1__*) ; 

__attribute__((used)) static void
qlnx_add_sysctls(qlnx_host_t *ha)
{
        device_t		dev = ha->pci_dev;
	struct sysctl_ctx_list	*ctx;
	struct sysctl_oid_list	*children;

	ctx = device_get_sysctl_ctx(dev);
	children = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));

	qlnx_add_fp_stats_sysctls(ha);
	qlnx_add_sp_stats_sysctls(ha);

	if (qlnx_vf_device(ha) != 0)
		qlnx_add_hw_stats_sysctls(ha);

	SYSCTL_ADD_STRING(ctx, children, OID_AUTO, "Driver_Version",
		CTLFLAG_RD, qlnx_ver_str, 0,
		"Driver Version");

	SYSCTL_ADD_STRING(ctx, children, OID_AUTO, "STORMFW_Version",
		CTLFLAG_RD, ha->stormfw_ver, 0,
		"STORM Firmware Version");

	SYSCTL_ADD_STRING(ctx, children, OID_AUTO, "MFW_Version",
		CTLFLAG_RD, ha->mfw_ver, 0,
		"Management Firmware Version");

        SYSCTL_ADD_UINT(ctx, children,
                OID_AUTO, "personality", CTLFLAG_RD,
                &ha->personality, ha->personality,
		"\tpersonality = 0 => Ethernet Only\n"
		"\tpersonality = 3 => Ethernet and RoCE\n"
		"\tpersonality = 4 => Ethernet and iWARP\n"
		"\tpersonality = 6 => Default in Shared Memory\n");

        ha->dbg_level = 0;
        SYSCTL_ADD_UINT(ctx, children,
                OID_AUTO, "debug", CTLFLAG_RW,
                &ha->dbg_level, ha->dbg_level, "Debug Level");

        ha->dp_level = 0x01;
        SYSCTL_ADD_UINT(ctx, children,
                OID_AUTO, "dp_level", CTLFLAG_RW,
                &ha->dp_level, ha->dp_level, "DP Level");

        ha->dbg_trace_lro_cnt = 0;
        SYSCTL_ADD_UINT(ctx, children,
                OID_AUTO, "dbg_trace_lro_cnt", CTLFLAG_RW,
                &ha->dbg_trace_lro_cnt, ha->dbg_trace_lro_cnt,
		"Trace LRO Counts");

        ha->dbg_trace_tso_pkt_len = 0;
        SYSCTL_ADD_UINT(ctx, children,
                OID_AUTO, "dbg_trace_tso_pkt_len", CTLFLAG_RW,
                &ha->dbg_trace_tso_pkt_len, ha->dbg_trace_tso_pkt_len,
		"Trace TSO packet lengths");

        ha->dp_module = 0;
        SYSCTL_ADD_UINT(ctx, children,
                OID_AUTO, "dp_module", CTLFLAG_RW,
                &ha->dp_module, ha->dp_module, "DP Module");

        ha->err_inject = 0;

        SYSCTL_ADD_UINT(ctx, children,
                OID_AUTO, "err_inject", CTLFLAG_RW,
                &ha->err_inject, ha->err_inject, "Error Inject");

	ha->storm_stats_enable = 0;

	SYSCTL_ADD_UINT(ctx, children,
		OID_AUTO, "storm_stats_enable", CTLFLAG_RW,
		&ha->storm_stats_enable, ha->storm_stats_enable,
		"Enable Storm Statistics Gathering");

	ha->storm_stats_index = 0;

	SYSCTL_ADD_UINT(ctx, children,
		OID_AUTO, "storm_stats_index", CTLFLAG_RD,
		&ha->storm_stats_index, ha->storm_stats_index,
		"Enable Storm Statistics Gathering Current Index");

	ha->grcdump_taken = 0;
	SYSCTL_ADD_UINT(ctx, children,
		OID_AUTO, "grcdump_taken", CTLFLAG_RD,
		&ha->grcdump_taken, ha->grcdump_taken,
		"grcdump_taken");

	ha->idle_chk_taken = 0;
	SYSCTL_ADD_UINT(ctx, children,
		OID_AUTO, "idle_chk_taken", CTLFLAG_RD,
		&ha->idle_chk_taken, ha->idle_chk_taken,
		"idle_chk_taken");

	SYSCTL_ADD_UINT(ctx, children,
		OID_AUTO, "rx_coalesce_usecs", CTLFLAG_RD,
		&ha->rx_coalesce_usecs, ha->rx_coalesce_usecs,
		"rx_coalesce_usecs");

	SYSCTL_ADD_UINT(ctx, children,
		OID_AUTO, "tx_coalesce_usecs", CTLFLAG_RD,
		&ha->tx_coalesce_usecs, ha->tx_coalesce_usecs,
		"tx_coalesce_usecs");

	SYSCTL_ADD_PROC(ctx, children,
		OID_AUTO, "trigger_dump", (CTLTYPE_INT | CTLFLAG_RW),
		(void *)ha, 0,
		qlnx_trigger_dump_sysctl, "I", "trigger_dump");

	SYSCTL_ADD_PROC(ctx, children,
		OID_AUTO, "set_rx_coalesce_usecs",
		(CTLTYPE_INT | CTLFLAG_RW),
		(void *)ha, 0,
		qlnx_set_rx_coalesce, "I",
		"rx interrupt coalesce period microseconds");

	SYSCTL_ADD_PROC(ctx, children,
		OID_AUTO, "set_tx_coalesce_usecs",
		(CTLTYPE_INT | CTLFLAG_RW),
		(void *)ha, 0,
		qlnx_set_tx_coalesce, "I",
		"tx interrupt coalesce period microseconds");

	ha->rx_pkt_threshold = 128;
        SYSCTL_ADD_UINT(ctx, children,
                OID_AUTO, "rx_pkt_threshold", CTLFLAG_RW,
                &ha->rx_pkt_threshold, ha->rx_pkt_threshold,
		"No. of Rx Pkts to process at a time");

	ha->rx_jumbo_buf_eq_mtu = 0;
        SYSCTL_ADD_UINT(ctx, children,
                OID_AUTO, "rx_jumbo_buf_eq_mtu", CTLFLAG_RW,
                &ha->rx_jumbo_buf_eq_mtu, ha->rx_jumbo_buf_eq_mtu,
		"== 0 => Rx Jumbo buffers are capped to 4Kbytes\n"
		"otherwise Rx Jumbo buffers are set to >= MTU size\n");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "err_illegal_intr", CTLFLAG_RD,
		&ha->err_illegal_intr, "err_illegal_intr");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "err_fp_null", CTLFLAG_RD,
		&ha->err_fp_null, "err_fp_null");

	SYSCTL_ADD_QUAD(ctx, children,
                OID_AUTO, "err_get_proto_invalid_type", CTLFLAG_RD,
		&ha->err_get_proto_invalid_type, "err_get_proto_invalid_type");
	return;
}