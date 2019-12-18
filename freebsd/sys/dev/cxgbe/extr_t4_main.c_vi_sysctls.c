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
struct vi_info {scalar_t__ nrxq; scalar_t__ ntxq; scalar_t__ first_rxq; scalar_t__ first_txq; scalar_t__ nofldrxq; scalar_t__ first_ofld_rxq; scalar_t__ nofldtxq; scalar_t__ first_ofld_txq; scalar_t__ nnmrxq; scalar_t__ nnmtxq; scalar_t__ first_nm_rxq; scalar_t__ first_nm_txq; int /*<<< orphan*/  rss_size; int /*<<< orphan*/  rss_base; int /*<<< orphan*/  viid; int /*<<< orphan*/  dev; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 scalar_t__ IS_MAIN_VI (struct vi_info*) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct vi_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_holdoff_pktc_idx ; 
 int /*<<< orphan*/  sysctl_holdoff_pktc_idx_ofld ; 
 int /*<<< orphan*/  sysctl_holdoff_tmr_idx ; 
 int /*<<< orphan*/  sysctl_holdoff_tmr_idx_ofld ; 
 int /*<<< orphan*/  sysctl_noflowq ; 
 int /*<<< orphan*/  sysctl_qsize_rxq ; 
 int /*<<< orphan*/  sysctl_qsize_txq ; 

void
vi_sysctls(struct vi_info *vi)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *oid;
	struct sysctl_oid_list *children;

	ctx = device_get_sysctl_ctx(vi->dev);

	/*
	 * dev.v?(cxgbe|cxl).X.
	 */
	oid = device_get_sysctl_tree(vi->dev);
	children = SYSCTL_CHILDREN(oid);

	SYSCTL_ADD_UINT(ctx, children, OID_AUTO, "viid", CTLFLAG_RD, NULL,
	    vi->viid, "VI identifer");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "nrxq", CTLFLAG_RD,
	    &vi->nrxq, 0, "# of rx queues");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "ntxq", CTLFLAG_RD,
	    &vi->ntxq, 0, "# of tx queues");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "first_rxq", CTLFLAG_RD,
	    &vi->first_rxq, 0, "index of first rx queue");
	SYSCTL_ADD_INT(ctx, children, OID_AUTO, "first_txq", CTLFLAG_RD,
	    &vi->first_txq, 0, "index of first tx queue");
	SYSCTL_ADD_UINT(ctx, children, OID_AUTO, "rss_base", CTLFLAG_RD, NULL,
	    vi->rss_base, "start of RSS indirection table");
	SYSCTL_ADD_UINT(ctx, children, OID_AUTO, "rss_size", CTLFLAG_RD, NULL,
	    vi->rss_size, "size of RSS indirection table");

	if (IS_MAIN_VI(vi)) {
		SYSCTL_ADD_PROC(ctx, children, OID_AUTO, "rsrv_noflowq",
		    CTLTYPE_INT | CTLFLAG_RW, vi, 0, sysctl_noflowq, "IU",
		    "Reserve queue 0 for non-flowid packets");
	}

#ifdef TCP_OFFLOAD
	if (vi->nofldrxq != 0) {
		SYSCTL_ADD_INT(ctx, children, OID_AUTO, "nofldrxq", CTLFLAG_RD,
		    &vi->nofldrxq, 0,
		    "# of rx queues for offloaded TCP connections");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO, "first_ofld_rxq",
		    CTLFLAG_RD, &vi->first_ofld_rxq, 0,
		    "index of first TOE rx queue");
		SYSCTL_ADD_PROC(ctx, children, OID_AUTO, "holdoff_tmr_idx_ofld",
		    CTLTYPE_INT | CTLFLAG_RW, vi, 0,
		    sysctl_holdoff_tmr_idx_ofld, "I",
		    "holdoff timer index for TOE queues");
		SYSCTL_ADD_PROC(ctx, children, OID_AUTO, "holdoff_pktc_idx_ofld",
		    CTLTYPE_INT | CTLFLAG_RW, vi, 0,
		    sysctl_holdoff_pktc_idx_ofld, "I",
		    "holdoff packet counter index for TOE queues");
	}
#endif
#if defined(TCP_OFFLOAD) || defined(RATELIMIT)
	if (vi->nofldtxq != 0) {
		SYSCTL_ADD_INT(ctx, children, OID_AUTO, "nofldtxq", CTLFLAG_RD,
		    &vi->nofldtxq, 0,
		    "# of tx queues for TOE/ETHOFLD");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO, "first_ofld_txq",
		    CTLFLAG_RD, &vi->first_ofld_txq, 0,
		    "index of first TOE/ETHOFLD tx queue");
	}
#endif
#ifdef DEV_NETMAP
	if (vi->nnmrxq != 0) {
		SYSCTL_ADD_INT(ctx, children, OID_AUTO, "nnmrxq", CTLFLAG_RD,
		    &vi->nnmrxq, 0, "# of netmap rx queues");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO, "nnmtxq", CTLFLAG_RD,
		    &vi->nnmtxq, 0, "# of netmap tx queues");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO, "first_nm_rxq",
		    CTLFLAG_RD, &vi->first_nm_rxq, 0,
		    "index of first netmap rx queue");
		SYSCTL_ADD_INT(ctx, children, OID_AUTO, "first_nm_txq",
		    CTLFLAG_RD, &vi->first_nm_txq, 0,
		    "index of first netmap tx queue");
	}
#endif

	SYSCTL_ADD_PROC(ctx, children, OID_AUTO, "holdoff_tmr_idx",
	    CTLTYPE_INT | CTLFLAG_RW, vi, 0, sysctl_holdoff_tmr_idx, "I",
	    "holdoff timer index");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO, "holdoff_pktc_idx",
	    CTLTYPE_INT | CTLFLAG_RW, vi, 0, sysctl_holdoff_pktc_idx, "I",
	    "holdoff packet counter index");

	SYSCTL_ADD_PROC(ctx, children, OID_AUTO, "qsize_rxq",
	    CTLTYPE_INT | CTLFLAG_RW, vi, 0, sysctl_qsize_rxq, "I",
	    "rx queue size");
	SYSCTL_ADD_PROC(ctx, children, OID_AUTO, "qsize_txq",
	    CTLTYPE_INT | CTLFLAG_RW, vi, 0, sysctl_qsize_txq, "I",
	    "tx queue size");
}