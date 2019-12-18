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
struct mbuf {int dummy; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  ngd_mtx; int /*<<< orphan*/  readq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IF_UNLOCK (int /*<<< orphan*/ *) ; 
 int NGDF_RWAIT ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _IF_ENQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ _IF_QFULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

__attribute__((used)) static int
ng_device_rcvdata(hook_p hook, item_p item)
{
	priv_p priv = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	struct mbuf *m;

	DBG;

	NGI_GET_M(item, m);
	NG_FREE_ITEM(item);

	IF_LOCK(&priv->readq);
	if (_IF_QFULL(&priv->readq)) {
		IF_UNLOCK(&priv->readq);
		NG_FREE_M(m);
		return (ENOBUFS);
	}

	_IF_ENQUEUE(&priv->readq, m);
	IF_UNLOCK(&priv->readq);
	mtx_lock(&priv->ngd_mtx);
	if (priv->flags & NGDF_RWAIT) {
		priv->flags &= ~NGDF_RWAIT;
		wakeup(priv);
	}
	mtx_unlock(&priv->ngd_mtx);

	return(0);
}