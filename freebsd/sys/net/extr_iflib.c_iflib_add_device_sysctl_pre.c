#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
typedef  TYPE_3__* if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {int /*<<< orphan*/  isc_disable_msix; } ;
struct TYPE_9__ {int /*<<< orphan*/  ifc_sysctl_separate_txrx; int /*<<< orphan*/  ifc_sysctl_core_offset; int /*<<< orphan*/  ifc_sysctl_tx_abdicate; int /*<<< orphan*/  ifc_sysctl_rx_budget; TYPE_2__ ifc_softc_ctx; int /*<<< orphan*/  ifc_sysctl_qs_eq_override; int /*<<< orphan*/  ifc_sysctl_nrxqs; int /*<<< orphan*/  ifc_sysctl_ntxqs; TYPE_1__* ifc_sctx; struct sysctl_oid* ifc_sysctl_node; } ;
struct TYPE_7__ {int /*<<< orphan*/  isc_driver_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_OFFSET_UNSPECIFIED ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RDTUN ; 
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  IFLIB_NRXD_HANDLER ; 
 int /*<<< orphan*/  IFLIB_NTXD_HANDLER ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_CONST_STRING (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U16 (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U8 (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_dev (TYPE_3__*) ; 
 int /*<<< orphan*/  mp_ndesc_handler ; 

__attribute__((used)) static void
iflib_add_device_sysctl_pre(if_ctx_t ctx)
{
        device_t dev = iflib_get_dev(ctx);
	struct sysctl_oid_list *child, *oid_list;
	struct sysctl_ctx_list *ctx_list;
	struct sysctl_oid *node;

	ctx_list = device_get_sysctl_ctx(dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));
	ctx->ifc_sysctl_node = node = SYSCTL_ADD_NODE(ctx_list, child, OID_AUTO, "iflib",
						      CTLFLAG_RD, NULL, "IFLIB fields");
	oid_list = SYSCTL_CHILDREN(node);

	SYSCTL_ADD_CONST_STRING(ctx_list, oid_list, OID_AUTO, "driver_version",
		       CTLFLAG_RD, ctx->ifc_sctx->isc_driver_version,
		       "driver version");

	SYSCTL_ADD_U16(ctx_list, oid_list, OID_AUTO, "override_ntxqs",
		       CTLFLAG_RWTUN, &ctx->ifc_sysctl_ntxqs, 0,
			"# of txqs to use, 0 => use default #");
	SYSCTL_ADD_U16(ctx_list, oid_list, OID_AUTO, "override_nrxqs",
		       CTLFLAG_RWTUN, &ctx->ifc_sysctl_nrxqs, 0,
			"# of rxqs to use, 0 => use default #");
	SYSCTL_ADD_U16(ctx_list, oid_list, OID_AUTO, "override_qs_enable",
		       CTLFLAG_RWTUN, &ctx->ifc_sysctl_qs_eq_override, 0,
                       "permit #txq != #rxq");
	SYSCTL_ADD_INT(ctx_list, oid_list, OID_AUTO, "disable_msix",
                      CTLFLAG_RWTUN, &ctx->ifc_softc_ctx.isc_disable_msix, 0,
                      "disable MSI-X (default 0)");
	SYSCTL_ADD_U16(ctx_list, oid_list, OID_AUTO, "rx_budget",
		       CTLFLAG_RWTUN, &ctx->ifc_sysctl_rx_budget, 0,
		       "set the RX budget");
	SYSCTL_ADD_U16(ctx_list, oid_list, OID_AUTO, "tx_abdicate",
		       CTLFLAG_RWTUN, &ctx->ifc_sysctl_tx_abdicate, 0,
		       "cause TX to abdicate instead of running to completion");
	ctx->ifc_sysctl_core_offset = CORE_OFFSET_UNSPECIFIED;
	SYSCTL_ADD_U16(ctx_list, oid_list, OID_AUTO, "core_offset",
		       CTLFLAG_RDTUN, &ctx->ifc_sysctl_core_offset, 0,
		       "offset to start using cores at");
	SYSCTL_ADD_U8(ctx_list, oid_list, OID_AUTO, "separate_txrx",
		       CTLFLAG_RDTUN, &ctx->ifc_sysctl_separate_txrx, 0,
		       "use separate cores for TX and RX");

	/* XXX change for per-queue sizes */
	SYSCTL_ADD_PROC(ctx_list, oid_list, OID_AUTO, "override_ntxds",
		       CTLTYPE_STRING|CTLFLAG_RWTUN, ctx, IFLIB_NTXD_HANDLER,
                       mp_ndesc_handler, "A",
		       "list of # of TX descriptors to use, 0 = use default #");
	SYSCTL_ADD_PROC(ctx_list, oid_list, OID_AUTO, "override_nrxds",
		       CTLTYPE_STRING|CTLFLAG_RWTUN, ctx, IFLIB_NRXD_HANDLER,
                       mp_ndesc_handler, "A",
		       "list of # of RX descriptors to use, 0 = use default #");
}