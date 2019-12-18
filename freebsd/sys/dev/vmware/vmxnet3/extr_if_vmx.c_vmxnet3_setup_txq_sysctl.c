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
struct vmxnet3_txqueue {int vxtxq_id; struct sysctl_oid_list* vxtxq_sysctl; TYPE_1__* vxtxq_ts; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct UPT1_TxStats {int /*<<< orphan*/  discard; int /*<<< orphan*/  error; int /*<<< orphan*/  mcast_bytes; int /*<<< orphan*/  mcast_packets; int /*<<< orphan*/  ucast_bytes; int /*<<< orphan*/  ucast_packets; int /*<<< orphan*/  TSO_bytes; int /*<<< orphan*/  TSO_packets; } ;
typedef  int /*<<< orphan*/  namebuf ;
struct TYPE_2__ {struct UPT1_TxStats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
vmxnet3_setup_txq_sysctl(struct vmxnet3_txqueue *txq,
    struct sysctl_ctx_list *ctx, struct sysctl_oid_list *child)
{
	struct sysctl_oid *node, *txsnode;
	struct sysctl_oid_list *list, *txslist;
	struct UPT1_TxStats *txstats;
	char namebuf[16];

	txstats = &txq->vxtxq_ts->stats;

	snprintf(namebuf, sizeof(namebuf), "txq%d", txq->vxtxq_id);
	node = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, namebuf, CTLFLAG_RD,
	    NULL, "Transmit Queue");
	txq->vxtxq_sysctl = list = SYSCTL_CHILDREN(node);

	/*
	 * Add statistics reported by the host. These are updated by the
	 * iflib txq timer on txq 0.
	 */
	txsnode = SYSCTL_ADD_NODE(ctx, list, OID_AUTO, "hstats", CTLFLAG_RD,
	    NULL, "Host Statistics");
	txslist = SYSCTL_CHILDREN(txsnode);
	SYSCTL_ADD_UQUAD(ctx, txslist, OID_AUTO, "tso_packets", CTLFLAG_RD,
	    &txstats->TSO_packets, "TSO packets");
	SYSCTL_ADD_UQUAD(ctx, txslist, OID_AUTO, "tso_bytes", CTLFLAG_RD,
	    &txstats->TSO_bytes, "TSO bytes");
	SYSCTL_ADD_UQUAD(ctx, txslist, OID_AUTO, "ucast_packets", CTLFLAG_RD,
	    &txstats->ucast_packets, "Unicast packets");
	SYSCTL_ADD_UQUAD(ctx, txslist, OID_AUTO, "unicast_bytes", CTLFLAG_RD,
	    &txstats->ucast_bytes, "Unicast bytes");
	SYSCTL_ADD_UQUAD(ctx, txslist, OID_AUTO, "mcast_packets", CTLFLAG_RD,
	    &txstats->mcast_packets, "Multicast packets");
	SYSCTL_ADD_UQUAD(ctx, txslist, OID_AUTO, "mcast_bytes", CTLFLAG_RD,
	    &txstats->mcast_bytes, "Multicast bytes");
	SYSCTL_ADD_UQUAD(ctx, txslist, OID_AUTO, "error", CTLFLAG_RD,
	    &txstats->error, "Errors");
	SYSCTL_ADD_UQUAD(ctx, txslist, OID_AUTO, "discard", CTLFLAG_RD,
	    &txstats->discard, "Discards");
}