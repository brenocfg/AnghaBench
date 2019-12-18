#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct l2tp_seq {int /*<<< orphan*/  mtx; int /*<<< orphan*/  xack_timer; int /*<<< orphan*/  rack_timer; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_5__ {struct l2tp_seq seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2TP_SEQ_CHECK (struct l2tp_seq* const) ; 
 int /*<<< orphan*/  M_NETGRAPH_L2TP ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_l2tp_seq_reset (TYPE_1__* const) ; 
 int /*<<< orphan*/  ng_uncallout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_l2tp_shutdown(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct l2tp_seq *const seq = &priv->seq;

	/* Sanity check */
	L2TP_SEQ_CHECK(seq);

	/* Reset sequence number state */
	ng_l2tp_seq_reset(priv);

	/* Free private data if neither timer is running */
	ng_uncallout(&seq->rack_timer, node);
	ng_uncallout(&seq->xack_timer, node);

	mtx_destroy(&seq->mtx);

	free(priv, M_NETGRAPH_L2TP);

	/* Unref node */
	NG_NODE_UNREF(node);
	return (0);
}