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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct i40e_hw {int /*<<< orphan*/  debug_mask; int /*<<< orphan*/  device_id; } ;
struct ixl_pf {scalar_t__ has_i2c; int /*<<< orphan*/  dbg_mask; struct i40e_hw hw; int /*<<< orphan*/  dynamic_tx_itr; int /*<<< orphan*/  dynamic_rx_itr; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLFLAG_SKIP ; 
 int CTLFLAG_WR ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_STRING ; 
 int CTLTYPE_ULONG ; 
 char* IXL_SYSCTL_HELP_FC ; 
 char* IXL_SYSCTL_HELP_FW_LLDP ; 
 char* IXL_SYSCTL_HELP_LINK_STATUS ; 
 char* IXL_SYSCTL_HELP_READ_I2C ; 
 char* IXL_SYSCTL_HELP_SET_ADVERTISE ; 
 char* IXL_SYSCTL_HELP_SUPPORTED_SPEED ; 
 char* IXL_SYSCTL_HELP_WRITE_I2C ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct ixl_pf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_is_25G_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_sysctl_current_speed ; 
 int /*<<< orphan*/  ixl_sysctl_do_core_reset ; 
 int /*<<< orphan*/  ixl_sysctl_do_emp_reset ; 
 int /*<<< orphan*/  ixl_sysctl_do_global_reset ; 
 int /*<<< orphan*/  ixl_sysctl_do_pf_reset ; 
 int /*<<< orphan*/  ixl_sysctl_dump_debug_data ; 
 int /*<<< orphan*/  ixl_sysctl_fec_auto_enable ; 
 int /*<<< orphan*/  ixl_sysctl_fec_fc_ability ; 
 int /*<<< orphan*/  ixl_sysctl_fec_fc_request ; 
 int /*<<< orphan*/  ixl_sysctl_fec_rs_ability ; 
 int /*<<< orphan*/  ixl_sysctl_fec_rs_request ; 
 int /*<<< orphan*/  ixl_sysctl_fw_link_management ; 
 int /*<<< orphan*/  ixl_sysctl_fw_lldp ; 
 int /*<<< orphan*/  ixl_sysctl_hena ; 
 int /*<<< orphan*/  ixl_sysctl_hkey ; 
 int /*<<< orphan*/  ixl_sysctl_hlut ; 
 int /*<<< orphan*/  ixl_sysctl_hw_res_alloc ; 
 int /*<<< orphan*/  ixl_sysctl_link_status ; 
 int /*<<< orphan*/  ixl_sysctl_pf_rx_itr ; 
 int /*<<< orphan*/  ixl_sysctl_pf_tx_itr ; 
 int /*<<< orphan*/  ixl_sysctl_phy_abilities ; 
 int /*<<< orphan*/  ixl_sysctl_queue_interrupt_table ; 
 int /*<<< orphan*/  ixl_sysctl_read_i2c_byte ; 
 int /*<<< orphan*/  ixl_sysctl_read_i2c_diag_data ; 
 int /*<<< orphan*/  ixl_sysctl_set_advertise ; 
 int /*<<< orphan*/  ixl_sysctl_set_flowcntl ; 
 int /*<<< orphan*/  ixl_sysctl_show_fw ; 
 int /*<<< orphan*/  ixl_sysctl_supported_speeds ; 
 int /*<<< orphan*/  ixl_sysctl_sw_filter_list ; 
 int /*<<< orphan*/  ixl_sysctl_switch_config ; 
 int /*<<< orphan*/  ixl_sysctl_unallocated_queues ; 
 int /*<<< orphan*/  ixl_sysctl_write_i2c_byte ; 

void
ixl_add_device_sysctls(struct ixl_pf *pf)
{
	device_t dev = pf->dev;
	struct i40e_hw *hw = &pf->hw;

	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(dev);
	struct sysctl_oid_list *ctx_list =
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev));

	struct sysctl_oid *debug_node;
	struct sysctl_oid_list *debug_list;

	struct sysctl_oid *fec_node;
	struct sysctl_oid_list *fec_list;

	/* Set up sysctls */
	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "fc", CTLTYPE_INT | CTLFLAG_RW,
	    pf, 0, ixl_sysctl_set_flowcntl, "I", IXL_SYSCTL_HELP_FC);

	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "advertise_speed", CTLTYPE_INT | CTLFLAG_RW,
	    pf, 0, ixl_sysctl_set_advertise, "I", IXL_SYSCTL_HELP_SET_ADVERTISE);

	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "supported_speeds", CTLTYPE_INT | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_supported_speeds, "I", IXL_SYSCTL_HELP_SUPPORTED_SPEED);

	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "current_speed", CTLTYPE_STRING | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_current_speed, "A", "Current Port Speed");

	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "fw_version", CTLTYPE_STRING | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_show_fw, "A", "Firmware version");

	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "unallocated_queues", CTLTYPE_INT | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_unallocated_queues, "I",
	    "Queues not allocated to a PF or VF");

	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "tx_itr", CTLTYPE_INT | CTLFLAG_RW,
	    pf, 0, ixl_sysctl_pf_tx_itr, "I",
	    "Immediately set TX ITR value for all queues");

	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "rx_itr", CTLTYPE_INT | CTLFLAG_RW,
	    pf, 0, ixl_sysctl_pf_rx_itr, "I",
	    "Immediately set RX ITR value for all queues");

	SYSCTL_ADD_INT(ctx, ctx_list,
	    OID_AUTO, "dynamic_rx_itr", CTLFLAG_RW,
	    &pf->dynamic_rx_itr, 0, "Enable dynamic RX ITR");

	SYSCTL_ADD_INT(ctx, ctx_list,
	    OID_AUTO, "dynamic_tx_itr", CTLFLAG_RW,
	    &pf->dynamic_tx_itr, 0, "Enable dynamic TX ITR");

	/* Add FEC sysctls for 25G adapters */
	if (i40e_is_25G_device(hw->device_id)) {
		fec_node = SYSCTL_ADD_NODE(ctx, ctx_list,
		    OID_AUTO, "fec", CTLFLAG_RD, NULL, "FEC Sysctls");
		fec_list = SYSCTL_CHILDREN(fec_node);

		SYSCTL_ADD_PROC(ctx, fec_list,
		    OID_AUTO, "fc_ability", CTLTYPE_INT | CTLFLAG_RW,
		    pf, 0, ixl_sysctl_fec_fc_ability, "I", "FC FEC ability enabled");

		SYSCTL_ADD_PROC(ctx, fec_list,
		    OID_AUTO, "rs_ability", CTLTYPE_INT | CTLFLAG_RW,
		    pf, 0, ixl_sysctl_fec_rs_ability, "I", "RS FEC ability enabled");

		SYSCTL_ADD_PROC(ctx, fec_list,
		    OID_AUTO, "fc_requested", CTLTYPE_INT | CTLFLAG_RW,
		    pf, 0, ixl_sysctl_fec_fc_request, "I", "FC FEC mode requested on link");

		SYSCTL_ADD_PROC(ctx, fec_list,
		    OID_AUTO, "rs_requested", CTLTYPE_INT | CTLFLAG_RW,
		    pf, 0, ixl_sysctl_fec_rs_request, "I", "RS FEC mode requested on link");

		SYSCTL_ADD_PROC(ctx, fec_list,
		    OID_AUTO, "auto_fec_enabled", CTLTYPE_INT | CTLFLAG_RW,
		    pf, 0, ixl_sysctl_fec_auto_enable, "I", "Let FW decide FEC ability/request modes");
	}

	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "fw_lldp", CTLTYPE_INT | CTLFLAG_RW,
	    pf, 0, ixl_sysctl_fw_lldp, "I", IXL_SYSCTL_HELP_FW_LLDP);

	/* Add sysctls meant to print debug information, but don't list them
	 * in "sysctl -a" output. */
	debug_node = SYSCTL_ADD_NODE(ctx, ctx_list,
	    OID_AUTO, "debug", CTLFLAG_RD | CTLFLAG_SKIP, NULL, "Debug Sysctls");
	debug_list = SYSCTL_CHILDREN(debug_node);

	SYSCTL_ADD_UINT(ctx, debug_list,
	    OID_AUTO, "shared_debug_mask", CTLFLAG_RW,
	    &pf->hw.debug_mask, 0, "Shared code debug message level");

	SYSCTL_ADD_UINT(ctx, debug_list,
	    OID_AUTO, "core_debug_mask", CTLFLAG_RW,
	    &pf->dbg_mask, 0, "Non-shared code debug message level");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "link_status", CTLTYPE_STRING | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_link_status, "A", IXL_SYSCTL_HELP_LINK_STATUS);

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "phy_abilities", CTLTYPE_STRING | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_phy_abilities, "A", "PHY Abilities");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "filter_list", CTLTYPE_STRING | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_sw_filter_list, "A", "SW Filter List");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "hw_res_alloc", CTLTYPE_STRING | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_hw_res_alloc, "A", "HW Resource Allocation");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "switch_config", CTLTYPE_STRING | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_switch_config, "A", "HW Switch Configuration");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "rss_key", CTLTYPE_STRING | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_hkey, "A", "View RSS key");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "rss_lut", CTLTYPE_STRING | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_hlut, "A", "View RSS lookup table");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "rss_hena", CTLTYPE_ULONG | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_hena, "LU", "View enabled packet types for RSS");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "disable_fw_link_management", CTLTYPE_INT | CTLFLAG_WR,
	    pf, 0, ixl_sysctl_fw_link_management, "I", "Disable FW Link Management");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "dump_debug_data", CTLTYPE_STRING | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_dump_debug_data, "A", "Dump Debug Data from FW");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "do_pf_reset", CTLTYPE_INT | CTLFLAG_WR,
	    pf, 0, ixl_sysctl_do_pf_reset, "I", "Tell HW to initiate a PF reset");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "do_core_reset", CTLTYPE_INT | CTLFLAG_WR,
	    pf, 0, ixl_sysctl_do_core_reset, "I", "Tell HW to initiate a CORE reset");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "do_global_reset", CTLTYPE_INT | CTLFLAG_WR,
	    pf, 0, ixl_sysctl_do_global_reset, "I", "Tell HW to initiate a GLOBAL reset");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "do_emp_reset", CTLTYPE_INT | CTLFLAG_WR,
	    pf, 0, ixl_sysctl_do_emp_reset, "I",
	    "(This doesn't work) Tell HW to initiate a EMP (entire firmware) reset");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "queue_interrupt_table", CTLTYPE_STRING | CTLFLAG_RD,
	    pf, 0, ixl_sysctl_queue_interrupt_table, "A", "View MSI-X indices for TX/RX queues");

	if (pf->has_i2c) {
		SYSCTL_ADD_PROC(ctx, debug_list,
		    OID_AUTO, "read_i2c_byte", CTLTYPE_INT | CTLFLAG_RW,
		    pf, 0, ixl_sysctl_read_i2c_byte, "I", IXL_SYSCTL_HELP_READ_I2C);

		SYSCTL_ADD_PROC(ctx, debug_list,
		    OID_AUTO, "write_i2c_byte", CTLTYPE_INT | CTLFLAG_RW,
		    pf, 0, ixl_sysctl_write_i2c_byte, "I", IXL_SYSCTL_HELP_WRITE_I2C);

		SYSCTL_ADD_PROC(ctx, debug_list,
		    OID_AUTO, "read_i2c_diag_data", CTLTYPE_STRING | CTLFLAG_RD,
		    pf, 0, ixl_sysctl_read_i2c_diag_data, "A", "Dump selected diagnostic data from FW");
	}
}