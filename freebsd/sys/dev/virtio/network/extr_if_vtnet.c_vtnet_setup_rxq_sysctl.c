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
struct vtnet_rxq_stats {int /*<<< orphan*/  vrxs_rescheduled; int /*<<< orphan*/  vrxs_csum_failed; int /*<<< orphan*/  vrxs_csum; int /*<<< orphan*/  vrxs_ierrors; int /*<<< orphan*/  vrxs_iqdrops; int /*<<< orphan*/  vrxs_ibytes; int /*<<< orphan*/  vrxs_ipackets; } ;
struct vtnet_rxq {int vtnrx_id; struct vtnet_rxq_stats vtnrx_stats; } ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
typedef  int /*<<< orphan*/  namebuf ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
vtnet_setup_rxq_sysctl(struct sysctl_ctx_list *ctx,
    struct sysctl_oid_list *child, struct vtnet_rxq *rxq)
{
	struct sysctl_oid *node;
	struct sysctl_oid_list *list;
	struct vtnet_rxq_stats *stats;
	char namebuf[16];

	snprintf(namebuf, sizeof(namebuf), "rxq%d", rxq->vtnrx_id);
	node = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, namebuf,
	    CTLFLAG_RD, NULL, "Receive Queue");
	list = SYSCTL_CHILDREN(node);

	stats = &rxq->vtnrx_stats;

	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "ipackets", CTLFLAG_RD,
	    &stats->vrxs_ipackets, "Receive packets");
	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "ibytes", CTLFLAG_RD,
	    &stats->vrxs_ibytes, "Receive bytes");
	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "iqdrops", CTLFLAG_RD,
	    &stats->vrxs_iqdrops, "Receive drops");
	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "ierrors", CTLFLAG_RD,
	    &stats->vrxs_ierrors, "Receive errors");
	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "csum", CTLFLAG_RD,
	    &stats->vrxs_csum, "Receive checksum offloaded");
	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "csum_failed", CTLFLAG_RD,
	    &stats->vrxs_csum_failed, "Receive checksum offload failed");
	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "rescheduled", CTLFLAG_RD,
	    &stats->vrxs_rescheduled,
	    "Receive interrupt handler rescheduled");
}