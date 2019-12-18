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
struct socket {int /*<<< orphan*/  so_state; int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_3__ {int flags; struct socket* so; } ;

/* Variables and functions */
 int KSF_CLONED ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  SO_SND ; 
 int /*<<< orphan*/  SS_NBIO ; 
 int /*<<< orphan*/  ng_ksocket_incoming ; 
 int /*<<< orphan*/  ng_ksocket_incoming2 ; 
 int /*<<< orphan*/  ng_send_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct socket* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soupcall_set (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_ksocket_connect(hook_p hook)
{
	node_p node = NG_HOOK_NODE(hook);
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct socket *const so = priv->so;

	/* Add our hook for incoming data and other events */
	SOCKBUF_LOCK(&priv->so->so_rcv);
	soupcall_set(priv->so, SO_RCV, ng_ksocket_incoming, node);
	SOCKBUF_UNLOCK(&priv->so->so_rcv);
	SOCKBUF_LOCK(&priv->so->so_snd);
	soupcall_set(priv->so, SO_SND, ng_ksocket_incoming, node);
	SOCKBUF_UNLOCK(&priv->so->so_snd);
	SOCK_LOCK(priv->so);
	priv->so->so_state |= SS_NBIO;
	SOCK_UNLOCK(priv->so);
	/*
	 * --Original comment--
	 * On a cloned socket we may have already received one or more
	 * upcalls which we couldn't handle without a hook.  Handle
	 * those now.
	 * We cannot call the upcall function directly
	 * from here, because until this function has returned our
	 * hook isn't connected.
	 *
	 * ---meta comment for -current ---
	 * XXX This is dubius.
	 * Upcalls between the time that the hook was
	 * first created and now (on another processesor) will
	 * be earlier on the queue than the request to finalise the hook.
	 * By the time the hook is finalised,
	 * The queued upcalls will have happened and the code
	 * will have discarded them because of a lack of a hook.
	 * (socket not open).
	 *
	 * This is a bad byproduct of the complicated way in which hooks
	 * are now created (3 daisy chained async events).
	 *
	 * Since we are a netgraph operation
	 * We know that we hold a lock on this node. This forces the
	 * request we make below to be queued rather than implemented
	 * immediately which will cause the upcall function to be called a bit
	 * later.
	 * However, as we will run any waiting queued operations immediately
	 * after doing this one, if we have not finalised the other end
	 * of the hook, those queued operations will fail.
	 */
	if (priv->flags & KSF_CLONED) {
		ng_send_fn(node, NULL, &ng_ksocket_incoming2, so, M_NOWAIT);
	}

	return (0);
}