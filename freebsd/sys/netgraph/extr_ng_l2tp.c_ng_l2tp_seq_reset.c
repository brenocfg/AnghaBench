#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct l2tp_seq {int wmax; int cwnd; int ssth; int /*<<< orphan*/ ** xwin; scalar_t__ rexmits; scalar_t__ acks; scalar_t__ xack; scalar_t__ rack; scalar_t__ nr; scalar_t__ ns; int /*<<< orphan*/  xack_timer; int /*<<< orphan*/  rack_timer; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_3__ {int /*<<< orphan*/  node; struct l2tp_seq seq; } ;

/* Variables and functions */
 int L2TP_MAX_XWIN ; 
 int /*<<< orphan*/  L2TP_SEQ_CHECK (struct l2tp_seq* const) ; 
 int /*<<< orphan*/  NG_NODE_FOREACH_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_l2tp_reset_session ; 
 int /*<<< orphan*/  ng_uncallout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_l2tp_seq_reset(priv_p priv)
{
	struct l2tp_seq *const seq = &priv->seq;
	hook_p hook;
	int i;

	/* Sanity check */
	L2TP_SEQ_CHECK(seq);

	/* Stop timers */
	ng_uncallout(&seq->rack_timer, priv->node);
	ng_uncallout(&seq->xack_timer, priv->node);

	/* Free retransmit queue */
	for (i = 0; i < L2TP_MAX_XWIN; i++) {
		if (seq->xwin[i] == NULL)
			break;
		m_freem(seq->xwin[i]);
	}

	/* Reset session hooks' sequence number states */
	NG_NODE_FOREACH_HOOK(priv->node, ng_l2tp_reset_session, NULL, hook);

	/* Reset node's sequence number state */
	seq->ns = 0;
	seq->nr = 0;
	seq->rack = 0;
	seq->xack = 0;
	seq->wmax = L2TP_MAX_XWIN;
	seq->cwnd = 1;
	seq->ssth = seq->wmax;
	seq->acks = 0;
	seq->rexmits = 0;
	bzero(seq->xwin, sizeof(seq->xwin));

	/* Done */
	L2TP_SEQ_CHECK(seq);
}