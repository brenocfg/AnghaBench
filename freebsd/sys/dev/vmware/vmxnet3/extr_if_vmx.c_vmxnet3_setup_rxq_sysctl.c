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
struct vmxnet3_rxqueue {int vxrxq_id; struct sysctl_oid_list* vxrxq_sysctl; TYPE_1__* vxrxq_rs; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct UPT1_RxStats {int /*<<< orphan*/  error; int /*<<< orphan*/  nobuffer; int /*<<< orphan*/  bcast_bytes; int /*<<< orphan*/  bcast_packets; int /*<<< orphan*/  mcast_bytes; int /*<<< orphan*/  mcast_packets; int /*<<< orphan*/  ucast_bytes; int /*<<< orphan*/  ucast_packets; int /*<<< orphan*/  LRO_bytes; int /*<<< orphan*/  LRO_packets; } ;
typedef  int /*<<< orphan*/  namebuf ;
struct TYPE_2__ {struct UPT1_RxStats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
vmxnet3_setup_rxq_sysctl(struct vmxnet3_rxqueue *rxq,
    struct sysctl_ctx_list *ctx, struct sysctl_oid_list *child)
{
	struct sysctl_oid *node, *rxsnode;
	struct sysctl_oid_list *list, *rxslist;
	struct UPT1_RxStats *rxstats;
	char namebuf[16];

	rxstats = &rxq->vxrxq_rs->stats;

	snprintf(namebuf, sizeof(namebuf), "rxq%d", rxq->vxrxq_id);
	node = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, namebuf, CTLFLAG_RD,
	    NULL, "Receive Queue");
	rxq->vxrxq_sysctl = list = SYSCTL_CHILDREN(node);

	/*
	 * Add statistics reported by the host. These are updated by the
	 * iflib txq timer on txq 0.
	 */
	rxsnode = SYSCTL_ADD_NODE(ctx, list, OID_AUTO, "hstats", CTLFLAG_RD,
	    NULL, "Host Statistics");
	rxslist = SYSCTL_CHILDREN(rxsnode);
	SYSCTL_ADD_UQUAD(ctx, rxslist, OID_AUTO, "lro_packets", CTLFLAG_RD,
	    &rxstats->LRO_packets, "LRO packets");
	SYSCTL_ADD_UQUAD(ctx, rxslist, OID_AUTO, "lro_bytes", CTLFLAG_RD,
	    &rxstats->LRO_bytes, "LRO bytes");
	SYSCTL_ADD_UQUAD(ctx, rxslist, OID_AUTO, "ucast_packets", CTLFLAG_RD,
	    &rxstats->ucast_packets, "Unicast packets");
	SYSCTL_ADD_UQUAD(ctx, rxslist, OID_AUTO, "unicast_bytes", CTLFLAG_RD,
	    &rxstats->ucast_bytes, "Unicast bytes");
	SYSCTL_ADD_UQUAD(ctx, rxslist, OID_AUTO, "mcast_packets", CTLFLAG_RD,
	    &rxstats->mcast_packets, "Multicast packets");
	SYSCTL_ADD_UQUAD(ctx, rxslist, OID_AUTO, "mcast_bytes", CTLFLAG_RD,
	    &rxstats->mcast_bytes, "Multicast bytes");
	SYSCTL_ADD_UQUAD(ctx, rxslist, OID_AUTO, "bcast_packets", CTLFLAG_RD,
	    &rxstats->bcast_packets, "Broadcast packets");
	SYSCTL_ADD_UQUAD(ctx, rxslist, OID_AUTO, "bcast_bytes", CTLFLAG_RD,
	    &rxstats->bcast_bytes, "Broadcast bytes");
	SYSCTL_ADD_UQUAD(ctx, rxslist, OID_AUTO, "nobuffer", CTLFLAG_RD,
	    &rxstats->nobuffer, "No buffer");
	SYSCTL_ADD_UQUAD(ctx, rxslist, OID_AUTO, "error", CTLFLAG_RD,
	    &rxstats->error, "Errors");
}