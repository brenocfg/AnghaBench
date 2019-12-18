#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct mbuf {int dummy; } ;
struct l2tp_seq {int rexmits; int ssth; int cwnd; int /*<<< orphan*/  ns; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * xwin; scalar_t__ acks; int /*<<< orphan*/  rack; int /*<<< orphan*/  rack_timer; } ;
typedef  TYPE_3__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_8__ {int /*<<< orphan*/  memoryFailures; int /*<<< orphan*/  xmitRetransmits; } ;
struct TYPE_7__ {scalar_t__ rexmit_max; int rexmit_max_to; } ;
struct TYPE_9__ {TYPE_2__ stats; TYPE_1__ conf; struct l2tp_seq seq; } ;

/* Variables and functions */
 struct mbuf* L2TP_COPY_MBUF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2TP_SEQ_CHECK (struct l2tp_seq* const) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 TYPE_3__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_callout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int),int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_l2tp_seq_failure (TYPE_3__* const) ; 
 int /*<<< orphan*/  ng_l2tp_xmit_ctrl (TYPE_3__* const,struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_l2tp_seq_rack_timeout(node_p node, hook_p hook, void *arg1, int arg2)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct l2tp_seq *const seq = &priv->seq;
	struct mbuf *m;
	u_int delay;

	/* Make sure callout is still active before doing anything */
	if (callout_pending(&seq->rack_timer) ||
	    (!callout_active(&seq->rack_timer)))
		return;

	/* Sanity check */
	L2TP_SEQ_CHECK(seq);

	mtx_lock(&seq->mtx);
	priv->stats.xmitRetransmits++;

	/* Have we reached the retransmit limit? If so, notify owner. */
	if (seq->rexmits++ >= priv->conf.rexmit_max)
		ng_l2tp_seq_failure(priv);

	/* Restart timer, this time with an increased delay */
	delay = (seq->rexmits > 12) ? (1 << 12) : (1 << seq->rexmits);
	if (delay > priv->conf.rexmit_max_to)
		delay = priv->conf.rexmit_max_to;
	ng_callout(&seq->rack_timer, node, NULL,
	    hz * delay, ng_l2tp_seq_rack_timeout, NULL, 0);

	/* Do slow-start/congestion algorithm windowing algorithm */
	seq->ns = seq->rack;
	seq->ssth = (seq->cwnd + 1) / 2;
	seq->cwnd = 1;
	seq->acks = 0;

	/* Retransmit oldest unack'd packet */
	m = L2TP_COPY_MBUF(seq->xwin[0], M_NOWAIT);
	mtx_unlock(&seq->mtx);
	if (m == NULL)
		priv->stats.memoryFailures++;
	else
		ng_l2tp_xmit_ctrl(priv, m, seq->ns++);

	/* callout_deactivate() is not needed here 
	    as ng_callout() is getting called each time */

	/* Sanity check */
	L2TP_SEQ_CHECK(seq);
}