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
typedef  struct ng_pptpgre_roq {int /*<<< orphan*/  item; } const ng_pptpgre_roq ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  roqh ;
typedef  TYPE_1__* hpriv_p ;
struct TYPE_3__ {int /*<<< orphan*/  hook; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FWD_NEW_DATA (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct ng_pptpgre_roq const* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ng_pptpgre_roq const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static int
ng_pptpgre_sendq(const hpriv_p hpriv, roqh *q, const struct ng_pptpgre_roq *st)
{
	struct ng_pptpgre_roq *np;
	struct mbuf *m;
	int error = 0;

	mtx_assert(&hpriv->mtx, MA_NOTOWNED);
	while (!SLIST_EMPTY(q)) {
		np = SLIST_FIRST(q);
		SLIST_REMOVE_HEAD(q, next);
		NGI_GET_M(np->item, m);
		NG_FWD_NEW_DATA(error, np->item, hpriv->hook, m);
		if (np != st)
			free(np, M_NETGRAPH);
	}
	return (error);
}