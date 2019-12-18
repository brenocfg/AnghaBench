#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ng_btsocket_sco_rtentry_p ;
typedef  TYPE_2__* ng_btsocket_sco_pcb_p ;
struct TYPE_14__ {int /*<<< orphan*/  so_error; } ;
struct TYPE_13__ {int flags; int /*<<< orphan*/ * hook; int /*<<< orphan*/  pcb_mtx; TYPE_4__* so; int /*<<< orphan*/  state; TYPE_1__* rt; } ;
struct TYPE_12__ {int /*<<< orphan*/ * hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETDOWN ; 
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_2__* LIST_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_BTSOCKET_SCO ; 
 int /*<<< orphan*/  NG_BTSOCKET_SCO_CLOSED ; 
 int NG_BTSOCKET_SCO_TIMO ; 
 scalar_t__ NG_HOOK_NOT_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_UNREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ng_btsocket_sco_rt ; 
 int /*<<< orphan*/  ng_btsocket_sco_rt_mtx ; 
 int /*<<< orphan*/  ng_btsocket_sco_sockets ; 
 int /*<<< orphan*/  ng_btsocket_sco_sockets_mtx ; 
 int /*<<< orphan*/  ng_btsocket_sco_untimeout (TYPE_2__*) ; 
 int /*<<< orphan*/  soisdisconnected (TYPE_4__*) ; 

__attribute__((used)) static void
ng_btsocket_sco_rtclean(void *context, int pending)
{
	ng_btsocket_sco_pcb_p		pcb = NULL, pcb_next = NULL;
	ng_btsocket_sco_rtentry_p	rt = NULL;

	/*
	 * First disconnect all sockets that use "invalid" hook
	 */

	mtx_lock(&ng_btsocket_sco_sockets_mtx);

	for(pcb = LIST_FIRST(&ng_btsocket_sco_sockets); pcb != NULL; ) {
		mtx_lock(&pcb->pcb_mtx);
		pcb_next = LIST_NEXT(pcb, next);

		if (pcb->rt != NULL &&
		    pcb->rt->hook != NULL && NG_HOOK_NOT_VALID(pcb->rt->hook)) {
			if (pcb->flags & NG_BTSOCKET_SCO_TIMO)
				ng_btsocket_sco_untimeout(pcb);

			pcb->rt = NULL;
			pcb->so->so_error = ENETDOWN;
			pcb->state = NG_BTSOCKET_SCO_CLOSED;
			soisdisconnected(pcb->so);
		}

		mtx_unlock(&pcb->pcb_mtx);
		pcb = pcb_next;
	}

	mtx_unlock(&ng_btsocket_sco_sockets_mtx);

	/*
	 * Now cleanup routing table
	 */

	mtx_lock(&ng_btsocket_sco_rt_mtx);

	for (rt = LIST_FIRST(&ng_btsocket_sco_rt); rt != NULL; ) {
		ng_btsocket_sco_rtentry_p	rt_next = LIST_NEXT(rt, next);

		if (rt->hook != NULL && NG_HOOK_NOT_VALID(rt->hook)) {
			LIST_REMOVE(rt, next);

			NG_HOOK_SET_PRIVATE(rt->hook, NULL);
			NG_HOOK_UNREF(rt->hook); /* Remove extra reference */

			bzero(rt, sizeof(*rt));
			free(rt, M_NETGRAPH_BTSOCKET_SCO);
		}

		rt = rt_next;
	}

	mtx_unlock(&ng_btsocket_sco_rt_mtx);
}