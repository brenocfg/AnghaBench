#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_1__* ng_h4_info_p ;
struct TYPE_8__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_7__ {TYPE_4__ outq; int /*<<< orphan*/  dying; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  M_NETGRAPH_H4 ; 
 int /*<<< orphan*/  NG_H4_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_H4_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_REVIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _IF_DRAIN (TYPE_4__*) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_h4_shutdown(node_p node)
{
	ng_h4_info_p	sc = (ng_h4_info_p) NG_NODE_PRIVATE(node);

	NG_H4_LOCK(sc);

	if (!sc->dying) {
		NG_H4_UNLOCK(sc);

		NG_NODE_REVIVE(node);	/* we will persist */

		return (EOPNOTSUPP);
	}

	NG_H4_UNLOCK(sc);

	NG_NODE_SET_PRIVATE(node, NULL);

	_IF_DRAIN(&sc->outq);

	NG_NODE_UNREF(node);
	mtx_destroy(&sc->outq.ifq_mtx);
	bzero(sc, sizeof(*sc));
	free(sc, M_NETGRAPH_H4);

	return (0);
}