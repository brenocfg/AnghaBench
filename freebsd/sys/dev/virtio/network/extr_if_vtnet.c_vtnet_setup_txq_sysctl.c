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
struct vtnet_txq_stats {int /*<<< orphan*/  vtxs_rescheduled; int /*<<< orphan*/  vtxs_tso; int /*<<< orphan*/  vtxs_csum; int /*<<< orphan*/  vtxs_omcasts; int /*<<< orphan*/  vtxs_obytes; int /*<<< orphan*/  vtxs_opackets; } ;
struct vtnet_txq {int vtntx_id; struct vtnet_txq_stats vtntx_stats; } ;
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
vtnet_setup_txq_sysctl(struct sysctl_ctx_list *ctx,
    struct sysctl_oid_list *child, struct vtnet_txq *txq)
{
	struct sysctl_oid *node;
	struct sysctl_oid_list *list;
	struct vtnet_txq_stats *stats;
	char namebuf[16];

	snprintf(namebuf, sizeof(namebuf), "txq%d", txq->vtntx_id);
	node = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, namebuf,
	    CTLFLAG_RD, NULL, "Transmit Queue");
	list = SYSCTL_CHILDREN(node);

	stats = &txq->vtntx_stats;

	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "opackets", CTLFLAG_RD,
	    &stats->vtxs_opackets, "Transmit packets");
	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "obytes", CTLFLAG_RD,
	    &stats->vtxs_obytes, "Transmit bytes");
	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "omcasts", CTLFLAG_RD,
	    &stats->vtxs_omcasts, "Transmit multicasts");
	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "csum", CTLFLAG_RD,
	    &stats->vtxs_csum, "Transmit checksum offloaded");
	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "tso", CTLFLAG_RD,
	    &stats->vtxs_tso, "Transmit segmentation offloaded");
	SYSCTL_ADD_UQUAD(ctx, list, OID_AUTO, "rescheduled", CTLFLAG_RD,
	    &stats->vtxs_rescheduled,
	    "Transmit interrupt handler rescheduled");
}