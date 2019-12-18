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
struct sysctl_oid {int dummy; } ;
struct bnxt_softc {int /*<<< orphan*/  flow_ctrl_ctx; struct sysctl_oid* flow_ctrl_oid; } ;

/* Variables and functions */
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_INT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct bnxt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  bnxt_flow_ctrl_autoneg ; 
 int /*<<< orphan*/  bnxt_flow_ctrl_rx ; 
 int /*<<< orphan*/  bnxt_flow_ctrl_tx ; 

int
bnxt_create_pause_fc_sysctls(struct bnxt_softc *softc)
{
	struct sysctl_oid *oid = softc->flow_ctrl_oid;

	if (!oid)
		return ENOMEM;

	SYSCTL_ADD_PROC(&softc->flow_ctrl_ctx, SYSCTL_CHILDREN(oid), OID_AUTO,
			"tx", CTLTYPE_INT|CTLFLAG_RWTUN, softc, 0,
			bnxt_flow_ctrl_tx, "A",
			"Enable or Disable Tx Flow Ctrl: 0 / 1");

	SYSCTL_ADD_PROC(&softc->flow_ctrl_ctx, SYSCTL_CHILDREN(oid), OID_AUTO,
			"rx", CTLTYPE_INT|CTLFLAG_RWTUN, softc, 0,
			bnxt_flow_ctrl_rx, "A",
			"Enable or Disable Tx Flow Ctrl: 0 / 1");

	SYSCTL_ADD_PROC(&softc->flow_ctrl_ctx, SYSCTL_CHILDREN(oid), OID_AUTO,
			"autoneg", CTLTYPE_INT|CTLFLAG_RWTUN, softc, 0,
			bnxt_flow_ctrl_autoneg, "A",
			"Enable or Disable Autoneg Flow Ctrl: 0 / 1");

	return 0;
}