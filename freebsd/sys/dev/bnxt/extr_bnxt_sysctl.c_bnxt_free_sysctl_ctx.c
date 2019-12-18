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
struct bnxt_softc {int /*<<< orphan*/ * flow_ctrl_oid; int /*<<< orphan*/  flow_ctrl_ctx; int /*<<< orphan*/ * hw_lro_oid; int /*<<< orphan*/  hw_lro_ctx; TYPE_2__* nvm_info; TYPE_1__* ver_info; int /*<<< orphan*/ * hw_stats_oid; int /*<<< orphan*/  hw_stats; } ;
struct TYPE_4__ {int /*<<< orphan*/ * nvm_oid; int /*<<< orphan*/  nvm_ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ver_oid; int /*<<< orphan*/  ver_ctx; } ;

/* Variables and functions */
 scalar_t__ BNXT_PF (struct bnxt_softc*) ; 
 int sysctl_ctx_free (int /*<<< orphan*/ *) ; 

int
bnxt_free_sysctl_ctx(struct bnxt_softc *softc)
{
	int orc;
	int rc = 0;

	if (softc->hw_stats_oid != NULL) {
		orc = sysctl_ctx_free(&softc->hw_stats);
		if (orc)
			rc = orc;
		else
			softc->hw_stats_oid = NULL;
	}
	if (softc->ver_info->ver_oid != NULL) {
		orc = sysctl_ctx_free(&softc->ver_info->ver_ctx);
		if (orc)
			rc = orc;
		else
			softc->ver_info->ver_oid = NULL;
	}
	if (BNXT_PF(softc) && softc->nvm_info->nvm_oid != NULL) {
		orc = sysctl_ctx_free(&softc->nvm_info->nvm_ctx);
		if (orc)
			rc = orc;
		else
			softc->nvm_info->nvm_oid = NULL;
	}
	if (softc->hw_lro_oid != NULL) {
		orc = sysctl_ctx_free(&softc->hw_lro_ctx);
		if (orc)
			rc = orc;
		else
			softc->hw_lro_oid = NULL;
	}

	if (softc->flow_ctrl_oid != NULL) {
		orc = sysctl_ctx_free(&softc->flow_ctrl_ctx);
		if (orc)
			rc = orc;
		else
			softc->flow_ctrl_oid = NULL;
	}

	return rc;
}