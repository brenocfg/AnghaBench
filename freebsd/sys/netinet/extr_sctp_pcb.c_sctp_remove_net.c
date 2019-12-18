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
struct sctp_association {struct sctp_nets* alternate; struct sctp_nets* last_control_chunk_from; int /*<<< orphan*/  nets; struct sctp_nets* last_data_chunk_from; struct sctp_nets* primary_destination; struct sctp_nets* deleted_primary; int /*<<< orphan*/  numnets; } ;
struct sctp_tcb {struct sctp_association asoc; int /*<<< orphan*/  sctp_ep; } ;
struct sctp_nets {int /*<<< orphan*/  lastsv; int /*<<< orphan*/  lastsa; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCTP_DEBUG_ASCONF1 ; 
 int /*<<< orphan*/  SCTP_MOBILITY_BASE ; 
 int /*<<< orphan*/  SCTP_MOBILITY_FASTHANDOFF ; 
 int /*<<< orphan*/  SCTP_MOBILITY_PRIM_DELETED ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_PRIM_DELETED ; 
 void* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sctp_nets*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct sctp_nets* sctp_find_alternate_net (struct sctp_tcb*,struct sctp_nets*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_free_remote_addr (struct sctp_nets*) ; 
 scalar_t__ sctp_is_mobility_feature_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_mobility_feature_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_next ; 
 int /*<<< orphan*/  sctp_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ *) ; 

void
sctp_remove_net(struct sctp_tcb *stcb, struct sctp_nets *net)
{
	struct sctp_association *asoc;

	asoc = &stcb->asoc;
	asoc->numnets--;
	TAILQ_REMOVE(&asoc->nets, net, sctp_next);
	if (net == asoc->primary_destination) {
		/* Reset primary */
		struct sctp_nets *lnet;

		lnet = TAILQ_FIRST(&asoc->nets);
		/*
		 * Mobility adaptation Ideally, if deleted destination is
		 * the primary, it becomes a fast retransmission trigger by
		 * the subsequent SET PRIMARY. (by micchie)
		 */
		if (sctp_is_mobility_feature_on(stcb->sctp_ep,
		    SCTP_MOBILITY_BASE) ||
		    sctp_is_mobility_feature_on(stcb->sctp_ep,
		    SCTP_MOBILITY_FASTHANDOFF)) {
			SCTPDBG(SCTP_DEBUG_ASCONF1, "remove_net: primary dst is deleting\n");
			if (asoc->deleted_primary != NULL) {
				SCTPDBG(SCTP_DEBUG_ASCONF1, "remove_net: deleted primary may be already stored\n");
				goto out;
			}
			asoc->deleted_primary = net;
			atomic_add_int(&net->ref_count, 1);
			memset(&net->lastsa, 0, sizeof(net->lastsa));
			memset(&net->lastsv, 0, sizeof(net->lastsv));
			sctp_mobility_feature_on(stcb->sctp_ep,
			    SCTP_MOBILITY_PRIM_DELETED);
			sctp_timer_start(SCTP_TIMER_TYPE_PRIM_DELETED,
			    stcb->sctp_ep, stcb, NULL);
		}
out:
		/* Try to find a confirmed primary */
		asoc->primary_destination = sctp_find_alternate_net(stcb, lnet, 0);
	}
	if (net == asoc->last_data_chunk_from) {
		/* Reset primary */
		asoc->last_data_chunk_from = TAILQ_FIRST(&asoc->nets);
	}
	if (net == asoc->last_control_chunk_from) {
		/* Clear net */
		asoc->last_control_chunk_from = NULL;
	}
	if (net == stcb->asoc.alternate) {
		sctp_free_remote_addr(stcb->asoc.alternate);
		stcb->asoc.alternate = NULL;
	}
	sctp_free_remote_addr(net);
}