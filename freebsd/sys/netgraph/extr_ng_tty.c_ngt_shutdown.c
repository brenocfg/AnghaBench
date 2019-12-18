#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty {int dummy; } ;
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_6__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_5__ {int /*<<< orphan*/  node; TYPE_4__ outq; struct tty* tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_DRAIN (TYPE_4__*) ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  ttyhook_unregister (struct tty*) ; 

__attribute__((used)) static int
ngt_shutdown(node_p node)
{
	const sc_p sc = NG_NODE_PRIVATE(node);
	struct tty *tp;

	tp = sc->tp;
	if (tp != NULL) {
		tty_lock(tp);
		ttyhook_unregister(tp);
	}
	/* Free resources */
	IF_DRAIN(&sc->outq);
	mtx_destroy(&(sc)->outq.ifq_mtx);
	NG_NODE_UNREF(sc->node);
	free(sc, M_NETGRAPH);

	return (0);
}