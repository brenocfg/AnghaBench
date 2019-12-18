#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ng_pptpgre_roq {int /*<<< orphan*/  seq; } ;
typedef  int /*<<< orphan*/  roqh ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_3__* hpriv_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_10__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  roq; int /*<<< orphan*/  recvSeq; int /*<<< orphan*/  roq_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  recvReorderTimeouts; } ;
struct TYPE_9__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int PPTP_SEQ_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct ng_pptpgre_roq* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_HEAD_INITIALIZER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INSERT_AFTER (struct ng_pptpgre_roq*,struct ng_pptpgre_roq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ng_pptpgre_roq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ng_pptpgre_ack (TYPE_3__* const) ; 
 int /*<<< orphan*/  ng_pptpgre_sendq (TYPE_3__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_pptpgre_start_reorder_timer (TYPE_3__* const) ; 
 int /*<<< orphan*/  sendq ; 

__attribute__((used)) static void
ng_pptpgre_reorder_timeout(node_p node, hook_p hook, void *arg1, int arg2)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	const hpriv_p hpriv = arg1;
	roqh sendq = SLIST_HEAD_INITIALIZER(sendq);
	struct ng_pptpgre_roq *np, *last = NULL;

	priv->stats.recvReorderTimeouts++;
	mtx_lock(&hpriv->mtx);
	if (SLIST_EMPTY(&hpriv->roq)) { /* should not happen */
		mtx_unlock(&hpriv->mtx);
		return;
	}

	last = np = SLIST_FIRST(&hpriv->roq);
	hpriv->roq_len--;
	SLIST_REMOVE_HEAD(&hpriv->roq, next);
	SLIST_INSERT_HEAD(&sendq, np, next);

	/* Look if we have more packets in sequence */
	while (!SLIST_EMPTY(&hpriv->roq)) {
		np = SLIST_FIRST(&hpriv->roq);
		if (PPTP_SEQ_DIFF(np->seq, last->seq) > 1)
			break; /* the gap in the sequence */

		/* Next packet is in sequence, move it to the sendq. */
		hpriv->roq_len--;
		SLIST_REMOVE_HEAD(&hpriv->roq, next);
		SLIST_INSERT_AFTER(last, np, next);
		last = np;
	}

	hpriv->recvSeq = last->seq;
	if (!SLIST_EMPTY(&hpriv->roq))
		ng_pptpgre_start_reorder_timer(hpriv);

	/* We need to acknowledge last packet; do it soon... */
	ng_pptpgre_ack(hpriv);		/* drops lock */
	ng_pptpgre_sendq(hpriv, &sendq, NULL);
	mtx_assert(&hpriv->mtx, MA_NOTOWNED);
}