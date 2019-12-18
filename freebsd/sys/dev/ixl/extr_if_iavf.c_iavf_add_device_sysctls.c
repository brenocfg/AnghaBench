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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct ixl_vsi {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  debug_mask; } ;
struct iavf_sc {int /*<<< orphan*/  dbg_mask; TYPE_1__ hw; int /*<<< orphan*/  dev; struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLFLAG_SKIP ; 
 int CTLFLAG_WR ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct iavf_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_sysctl_current_speed ; 
 int /*<<< orphan*/  iavf_sysctl_queue_interrupt_table ; 
 int /*<<< orphan*/  iavf_sysctl_rx_itr ; 
 int /*<<< orphan*/  iavf_sysctl_sw_filter_list ; 
 int /*<<< orphan*/  iavf_sysctl_tx_itr ; 
 int /*<<< orphan*/  iavf_sysctl_vf_reset ; 
 int /*<<< orphan*/  iavf_sysctl_vflr_reset ; 
 int /*<<< orphan*/  ixl_add_queues_sysctls (int /*<<< orphan*/ ,struct ixl_vsi*) ; 
 int /*<<< orphan*/  ixl_add_vsi_sysctls (int /*<<< orphan*/ ,struct ixl_vsi*,struct sysctl_ctx_list*,char*) ; 

__attribute__((used)) static void
iavf_add_device_sysctls(struct iavf_sc *sc)
{
	struct ixl_vsi *vsi = &sc->vsi;
	device_t dev = sc->dev;

	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(dev);
	struct sysctl_oid_list *ctx_list =
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev));
	struct sysctl_oid *debug_node;
	struct sysctl_oid_list *debug_list;

	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "current_speed", CTLTYPE_STRING | CTLFLAG_RD,
	    sc, 0, iavf_sysctl_current_speed, "A", "Current Port Speed");

	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "tx_itr", CTLTYPE_INT | CTLFLAG_RW,
	    sc, 0, iavf_sysctl_tx_itr, "I",
	    "Immediately set TX ITR value for all queues");

	SYSCTL_ADD_PROC(ctx, ctx_list,
	    OID_AUTO, "rx_itr", CTLTYPE_INT | CTLFLAG_RW,
	    sc, 0, iavf_sysctl_rx_itr, "I",
	    "Immediately set RX ITR value for all queues");

	/* Add sysctls meant to print debug information, but don't list them
	 * in "sysctl -a" output. */
	debug_node = SYSCTL_ADD_NODE(ctx, ctx_list,
	    OID_AUTO, "debug", CTLFLAG_RD | CTLFLAG_SKIP, NULL, "Debug Sysctls");
	debug_list = SYSCTL_CHILDREN(debug_node);

	SYSCTL_ADD_UINT(ctx, debug_list,
	    OID_AUTO, "shared_debug_mask", CTLFLAG_RW,
	    &sc->hw.debug_mask, 0, "Shared code debug message level");

	SYSCTL_ADD_UINT(ctx, debug_list,
	    OID_AUTO, "core_debug_mask", CTLFLAG_RW,
	    &sc->dbg_mask, 0, "Non-shared code debug message level");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "filter_list", CTLTYPE_STRING | CTLFLAG_RD,
	    sc, 0, iavf_sysctl_sw_filter_list, "A", "SW Filter List");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "queue_interrupt_table", CTLTYPE_STRING | CTLFLAG_RD,
	    sc, 0, iavf_sysctl_queue_interrupt_table, "A", "View MSI-X indices for TX/RX queues");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "do_vf_reset", CTLTYPE_INT | CTLFLAG_WR,
	    sc, 0, iavf_sysctl_vf_reset, "A", "Request a VF reset from PF");

	SYSCTL_ADD_PROC(ctx, debug_list,
	    OID_AUTO, "do_vflr_reset", CTLTYPE_INT | CTLFLAG_WR,
	    sc, 0, iavf_sysctl_vflr_reset, "A", "Request a VFLR reset from HW");

	/* Add stats sysctls */
	ixl_add_vsi_sysctls(dev, vsi, ctx, "vsi");
	ixl_add_queues_sysctls(dev, vsi);

}