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
struct ng_ppp_frag {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_3__ {int /*<<< orphan*/  frags; int /*<<< orphan*/  fragsfree; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_FREE_M (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 struct ng_ppp_frag* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct ng_ppp_frag*,int /*<<< orphan*/ ) ; 
 struct ng_ppp_frag* TAILQ_NEXT (struct ng_ppp_frag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_qent ; 

__attribute__((used)) static void
ng_ppp_frag_reset(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_ppp_frag *qent, *qnext;

	for (qent = TAILQ_FIRST(&priv->frags); qent; qent = qnext) {
		qnext = TAILQ_NEXT(qent, f_qent);
		NG_FREE_M(qent->data);
		TAILQ_INSERT_HEAD(&priv->fragsfree, qent, f_qent);
	}
	TAILQ_INIT(&priv->frags);
}