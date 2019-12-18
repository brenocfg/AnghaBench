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
struct socket {int dummy; } ;
typedef  TYPE_1__* priv_p ;
typedef  void* node_p ;
struct TYPE_3__ {int /*<<< orphan*/  fn_sent; } ;

/* Variables and functions */
 int M_WAITOK ; 
 TYPE_1__* NG_NODE_PRIVATE (void* const) ; 
 int NG_QUEUE ; 
 int NG_WAITOK ; 
 int SU_OK ; 
 scalar_t__ atomic_cmpset_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_ksocket_incoming2 ; 
 scalar_t__ ng_send_fn1 (void* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct socket*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ng_ksocket_incoming(struct socket *so, void *arg, int waitflag)
{
	const node_p node = arg;
	const priv_p priv = NG_NODE_PRIVATE(node);
	int wait = ((waitflag & M_WAITOK) ? NG_WAITOK : 0) | NG_QUEUE;

	/*
	 * Even if node is not locked, as soon as we are called, we assume
	 * it exist and it's private area is valid. With some care we can
	 * access it. Mark node that incoming event for it was sent to
	 * avoid unneded queue trashing.
	 */
	if (atomic_cmpset_int(&priv->fn_sent, 0, 1) &&
	    ng_send_fn1(node, NULL, &ng_ksocket_incoming2, so, 0, wait)) {
		atomic_store_rel_int(&priv->fn_sent, 0);
	}
	return (SU_OK);
}