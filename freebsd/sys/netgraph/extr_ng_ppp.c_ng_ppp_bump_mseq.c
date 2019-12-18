#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ng_ppp_link {void* seq; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* int32_t ;
struct TYPE_4__ {int numActiveLinks; size_t* activeLinks; struct ng_ppp_link* links; void* mseq; } ;

/* Variables and functions */
 scalar_t__ MP_RECV_SEQ_DIFF (TYPE_1__* const,void*,void*) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_ppp_bump_mseq(node_p node, int32_t new_mseq)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	int i;
	
	if (MP_RECV_SEQ_DIFF(priv, priv->mseq, new_mseq) < 0) {
		priv->mseq = new_mseq;
		for (i = 0; i < priv->numActiveLinks; i++) {
			struct ng_ppp_link *const alink =
			    &priv->links[priv->activeLinks[i]];

			if (MP_RECV_SEQ_DIFF(priv,
			    alink->seq, new_mseq) < 0)
				alink->seq = new_mseq;
		}
	}
}