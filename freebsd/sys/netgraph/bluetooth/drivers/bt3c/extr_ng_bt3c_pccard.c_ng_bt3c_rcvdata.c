#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
typedef  int /*<<< orphan*/  item_p ;
typedef  scalar_t__ hook_p ;
typedef  TYPE_2__* bt3c_softc_p ;
struct TYPE_4__ {scalar_t__ hook; int /*<<< orphan*/  node; int /*<<< orphan*/  outq; int /*<<< orphan*/  stat; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EHOSTDOWN ; 
 int EINVAL ; 
 int /*<<< orphan*/  IF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_BT3C_ERR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_BT3C_STAT_OERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (scalar_t__) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _IF_ENQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ _IF_QFULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt3c_send ; 
 int ng_send_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_bt3c_rcvdata(hook_p hook, item_p item)
{
	bt3c_softc_p	 sc = (bt3c_softc_p)NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	struct mbuf	*m = NULL;
	int		 error = 0;

	if (sc == NULL) {
		error = EHOSTDOWN;
		goto out;
	}

	if (hook != sc->hook) {
		error = EINVAL;
		goto out;
	}

	NGI_GET_M(item, m);

	IF_LOCK(&sc->outq);
	if (_IF_QFULL(&sc->outq)) {
		NG_BT3C_ERR(sc->dev,
"Outgoing queue is full. Dropping mbuf, len=%d\n", m->m_pkthdr.len);

		NG_BT3C_STAT_OERROR(sc->stat);

		NG_FREE_M(m);
	} else 
		_IF_ENQUEUE(&sc->outq, m);
	IF_UNLOCK(&sc->outq);

	error = ng_send_fn(sc->node, NULL, bt3c_send, NULL, 0 /* new send */);
out:
        NG_FREE_ITEM(item);

	return (error);
}