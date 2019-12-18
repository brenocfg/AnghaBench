#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vi_info {int /*<<< orphan*/  ctx; TYPE_4__* ifp; TYPE_2__* pi; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  lro_flushed; int /*<<< orphan*/  lro_queued; TYPE_4__* ifp; } ;
struct TYPE_11__ {scalar_t__ abs_id; scalar_t__ cntxt_id; int /*<<< orphan*/  flags; } ;
struct sge_rxq {int /*<<< orphan*/  fl; int /*<<< orphan*/  vlan_extraction; int /*<<< orphan*/  rxcsum; TYPE_3__ lro; TYPE_5__ iq; TYPE_4__* ifp; } ;
struct TYPE_7__ {scalar_t__ iq_base; } ;
struct adapter {int flags; TYPE_1__ sge; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_10__ {int if_capenable; } ;
struct TYPE_8__ {struct adapter* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  FL_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FL_UNLOCK (int /*<<< orphan*/ *) ; 
 int IFCAP_HWRXTSTMP ; 
 int IFCAP_LRO ; 
 int /*<<< orphan*/  IQ_LRO_ENABLED ; 
 int /*<<< orphan*/  IQ_RX_TIMESTAMP ; 
 int IS_VF ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U64 (int /*<<< orphan*/ *,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (int /*<<< orphan*/ *,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  add_fl_sysctls (struct adapter*,int /*<<< orphan*/ *,struct sysctl_oid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_iq_sysctls (int /*<<< orphan*/ *,struct sysctl_oid*,TYPE_5__*) ; 
 int alloc_iq_fl (struct vi_info*,TYPE_5__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cong_drop ; 
 int /*<<< orphan*/  lro_entries ; 
 int /*<<< orphan*/  lro_mbufs ; 
 int /*<<< orphan*/  refill_fl (struct adapter*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int tcp_lro_init_args (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnl_cong (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
alloc_rxq(struct vi_info *vi, struct sge_rxq *rxq, int intr_idx, int idx,
    struct sysctl_oid *oid)
{
	int rc;
	struct adapter *sc = vi->pi->adapter;
	struct sysctl_oid_list *children;
	char name[16];

	rc = alloc_iq_fl(vi, &rxq->iq, &rxq->fl, intr_idx,
	    tnl_cong(vi->pi, cong_drop));
	if (rc != 0)
		return (rc);

	if (idx == 0)
		sc->sge.iq_base = rxq->iq.abs_id - rxq->iq.cntxt_id;
	else
		KASSERT(rxq->iq.cntxt_id + sc->sge.iq_base == rxq->iq.abs_id,
		    ("iq_base mismatch"));
	KASSERT(sc->sge.iq_base == 0 || sc->flags & IS_VF,
	    ("PF with non-zero iq_base"));

	/*
	 * The freelist is just barely above the starvation threshold right now,
	 * fill it up a bit more.
	 */
	FL_LOCK(&rxq->fl);
	refill_fl(sc, &rxq->fl, 128);
	FL_UNLOCK(&rxq->fl);

#if defined(INET) || defined(INET6)
	rc = tcp_lro_init_args(&rxq->lro, vi->ifp, lro_entries, lro_mbufs);
	if (rc != 0)
		return (rc);
	MPASS(rxq->lro.ifp == vi->ifp);	/* also indicates LRO init'ed */

	if (vi->ifp->if_capenable & IFCAP_LRO)
		rxq->iq.flags |= IQ_LRO_ENABLED;
#endif
	if (vi->ifp->if_capenable & IFCAP_HWRXTSTMP)
		rxq->iq.flags |= IQ_RX_TIMESTAMP;
	rxq->ifp = vi->ifp;

	children = SYSCTL_CHILDREN(oid);

	snprintf(name, sizeof(name), "%d", idx);
	oid = SYSCTL_ADD_NODE(&vi->ctx, children, OID_AUTO, name, CTLFLAG_RD,
	    NULL, "rx queue");
	children = SYSCTL_CHILDREN(oid);

	add_iq_sysctls(&vi->ctx, oid, &rxq->iq);
#if defined(INET) || defined(INET6)
	SYSCTL_ADD_U64(&vi->ctx, children, OID_AUTO, "lro_queued", CTLFLAG_RD,
	    &rxq->lro.lro_queued, 0, NULL);
	SYSCTL_ADD_U64(&vi->ctx, children, OID_AUTO, "lro_flushed", CTLFLAG_RD,
	    &rxq->lro.lro_flushed, 0, NULL);
#endif
	SYSCTL_ADD_UQUAD(&vi->ctx, children, OID_AUTO, "rxcsum", CTLFLAG_RD,
	    &rxq->rxcsum, "# of times hardware assisted with checksum");
	SYSCTL_ADD_UQUAD(&vi->ctx, children, OID_AUTO, "vlan_extraction",
	    CTLFLAG_RD, &rxq->vlan_extraction,
	    "# of times hardware extracted 802.1Q tag");

	add_fl_sysctls(sc, &vi->ctx, oid, &rxq->fl);

	return (rc);
}