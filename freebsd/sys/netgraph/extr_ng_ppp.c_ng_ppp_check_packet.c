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
struct ng_ppp_frag {scalar_t__ seq; int /*<<< orphan*/  last; int /*<<< orphan*/  first; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_5__ {int /*<<< orphan*/  mseq; int /*<<< orphan*/  frags; } ;

/* Variables and functions */
 scalar_t__ MP_NEXT_RECV_SEQ (TYPE_1__* const,scalar_t__) ; 
 int MP_RECV_SEQ_DIFF (TYPE_1__* const,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ng_ppp_frag* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct ng_ppp_frag* TAILQ_NEXT (struct ng_ppp_frag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_qent ; 

__attribute__((used)) static int
ng_ppp_check_packet(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_ppp_frag *qent, *qnext;

	/* Check for empty queue */
	if (TAILQ_EMPTY(&priv->frags))
		return (0);

	/* Check first fragment is the start of a deliverable packet */
	qent = TAILQ_FIRST(&priv->frags);
	if (!qent->first || MP_RECV_SEQ_DIFF(priv, qent->seq, priv->mseq) > 1)
		return (0);

	/* Check that all the fragments are there */
	while (!qent->last) {
		qnext = TAILQ_NEXT(qent, f_qent);
		if (qnext == NULL)	/* end of queue */
			return (0);
		if (qnext->seq != MP_NEXT_RECV_SEQ(priv, qent->seq))
			return (0);
		qent = qnext;
	}

	/* Got one */
	return (1);
}