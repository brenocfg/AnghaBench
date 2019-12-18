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
struct sysctl_ctx_list {int dummy; } ;
struct bnxt_softc {int /*<<< orphan*/  flow_ctrl_ctx; void* flow_ctrl_oid; int /*<<< orphan*/  dev; int /*<<< orphan*/  hw_lro_ctx; void* hw_lro_oid; TYPE_2__* nvm_info; TYPE_1__* ver_info; int /*<<< orphan*/  hw_stats; void* hw_stats_oid; } ;
struct TYPE_4__ {int /*<<< orphan*/  nvm_ctx; void* nvm_oid; } ;
struct TYPE_3__ {int /*<<< orphan*/  ver_ctx; void* ver_oid; } ;

/* Variables and functions */
 scalar_t__ BNXT_PF (struct bnxt_softc*) ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OID_AUTO ; 
 void* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

int
bnxt_init_sysctl_ctx(struct bnxt_softc *softc)
{
	struct sysctl_ctx_list *ctx;

	sysctl_ctx_init(&softc->hw_stats);
	ctx = device_get_sysctl_ctx(softc->dev);
	softc->hw_stats_oid = SYSCTL_ADD_NODE(ctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(softc->dev)), OID_AUTO,
	    "hwstats", CTLFLAG_RD, 0, "hardware statistics");
	if (!softc->hw_stats_oid) {
		sysctl_ctx_free(&softc->hw_stats);
		return ENOMEM;
	}

	sysctl_ctx_init(&softc->ver_info->ver_ctx);
	ctx = device_get_sysctl_ctx(softc->dev);
	softc->ver_info->ver_oid = SYSCTL_ADD_NODE(ctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(softc->dev)), OID_AUTO,
	    "ver", CTLFLAG_RD, 0, "hardware/firmware version information");
	if (!softc->ver_info->ver_oid) {
		sysctl_ctx_free(&softc->ver_info->ver_ctx);
		return ENOMEM;
	}

	if (BNXT_PF(softc)) {
		sysctl_ctx_init(&softc->nvm_info->nvm_ctx);
		ctx = device_get_sysctl_ctx(softc->dev);
		softc->nvm_info->nvm_oid = SYSCTL_ADD_NODE(ctx,
		    SYSCTL_CHILDREN(device_get_sysctl_tree(softc->dev)), OID_AUTO,
		    "nvram", CTLFLAG_RD, 0, "nvram information");
		if (!softc->nvm_info->nvm_oid) {
			sysctl_ctx_free(&softc->nvm_info->nvm_ctx);
			return ENOMEM;
		}
	}

	sysctl_ctx_init(&softc->hw_lro_ctx);
	ctx = device_get_sysctl_ctx(softc->dev);
	softc->hw_lro_oid = SYSCTL_ADD_NODE(ctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(softc->dev)), OID_AUTO,
	    "hw_lro", CTLFLAG_RD, 0, "hardware lro");
	if (!softc->hw_lro_oid) {
		sysctl_ctx_free(&softc->hw_lro_ctx);
		return ENOMEM;
	}

	sysctl_ctx_init(&softc->flow_ctrl_ctx);
	ctx = device_get_sysctl_ctx(softc->dev);
	softc->flow_ctrl_oid = SYSCTL_ADD_NODE(ctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(softc->dev)), OID_AUTO,
	    "fc", CTLFLAG_RD, 0, "flow ctrl");
	if (!softc->flow_ctrl_oid) {
		sysctl_ctx_free(&softc->flow_ctrl_ctx);
		return ENOMEM;
	}

	return 0;
}