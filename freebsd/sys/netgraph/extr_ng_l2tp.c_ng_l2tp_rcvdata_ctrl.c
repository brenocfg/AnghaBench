#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int16_t ;
struct TYPE_8__ {int len; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct l2tp_seq {int cwnd; int /*<<< orphan*/  mtx; int /*<<< orphan*/  ns; int /*<<< orphan*/  rack_timer; struct mbuf** xwin; } ;
typedef  TYPE_4__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_9__ {int /*<<< orphan*/  memoryFailures; int /*<<< orphan*/  xmitDrops; int /*<<< orphan*/  xmitTooBig; int /*<<< orphan*/  xmitInvalid; } ;
struct TYPE_7__ {int /*<<< orphan*/  enabled; } ;
struct TYPE_10__ {struct l2tp_seq seq; TYPE_3__ stats; TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  ERROUT (int /*<<< orphan*/ ) ; 
 struct mbuf* L2TP_COPY_MBUF (struct mbuf*,int /*<<< orphan*/ ) ; 
 int L2TP_MAX_XWIN ; 
 int /*<<< orphan*/  L2TP_SEQ_CHECK (struct l2tp_seq*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 TYPE_4__* NG_NODE_PRIVATE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_callout (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_l2tp_seq_rack_timeout ; 
 int ng_l2tp_xmit_ctrl (TYPE_4__* const,struct mbuf*,scalar_t__) ; 

__attribute__((used)) static int
ng_l2tp_rcvdata_ctrl(hook_p hook, item_p item)
{
	const node_p node = NG_HOOK_NODE(hook);
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct l2tp_seq *const seq = &priv->seq;
	struct mbuf *m;
	int error;
	int i;
	u_int16_t	ns;

	/* Sanity check */
	L2TP_SEQ_CHECK(&priv->seq);

	/* If not configured, reject */
	if (!priv->conf.enabled) {
		NG_FREE_ITEM(item);
		ERROUT(ENXIO);
	}

	/* Grab mbuf and discard other stuff XXX */
	NGI_GET_M(item, m);
	NG_FREE_ITEM(item);

	/* Packet should have session ID prepended */
	if (m->m_pkthdr.len < 2) {
		priv->stats.xmitInvalid++;
		m_freem(m);
		ERROUT(EINVAL);
	}

	/* Check max length */
	if (m->m_pkthdr.len >= 0x10000 - 14) {
		priv->stats.xmitTooBig++;
		m_freem(m);
		ERROUT(EOVERFLOW);
	}

	mtx_lock(&seq->mtx);

	/* Find next empty slot in transmit queue */
	for (i = 0; i < L2TP_MAX_XWIN && seq->xwin[i] != NULL; i++);
	if (i == L2TP_MAX_XWIN) {
		mtx_unlock(&seq->mtx);
		priv->stats.xmitDrops++;
		m_freem(m);
		ERROUT(ENOBUFS);
	}
	seq->xwin[i] = m;

	/* If peer's receive window is already full, nothing else to do */
	if (i >= seq->cwnd) {
		mtx_unlock(&seq->mtx);
		ERROUT(0);
	}

	/* Start retransmit timer if not already running */
	if (!callout_active(&seq->rack_timer))
		ng_callout(&seq->rack_timer, node, NULL,
		    hz, ng_l2tp_seq_rack_timeout, NULL, 0);
	
	ns = seq->ns++;
	
	mtx_unlock(&seq->mtx);

	/* Copy packet */
	if ((m = L2TP_COPY_MBUF(m, M_NOWAIT)) == NULL) {
		priv->stats.memoryFailures++;
		ERROUT(ENOBUFS);
	}

	/* Send packet and increment xmit sequence number */
	error = ng_l2tp_xmit_ctrl(priv, m, ns);
done:
	/* Done */
	L2TP_SEQ_CHECK(&priv->seq);
	return (error);
}