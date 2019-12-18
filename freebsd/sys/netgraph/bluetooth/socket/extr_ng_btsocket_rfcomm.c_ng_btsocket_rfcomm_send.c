#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;
struct TYPE_5__ {scalar_t__ state; int flags; int /*<<< orphan*/  pcb_mtx; TYPE_1__* so; } ;
typedef  TYPE_2__ ng_btsocket_rfcomm_pcb_t ;
struct TYPE_4__ {int /*<<< orphan*/  so_snd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 scalar_t__ NG_BTSOCKET_RFCOMM_DLC_CONNECTED ; 
 int NG_BTSOCKET_RFCOMM_DLC_SENDING ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ng_btsocket_rfcomm_task_wakeup () ; 
 int /*<<< orphan*/  sbappend (int /*<<< orphan*/ *,struct mbuf*,int) ; 
 TYPE_2__* so2rfcomm_pcb (struct socket*) ; 

int
ng_btsocket_rfcomm_send(struct socket *so, int flags, struct mbuf *m,
		struct sockaddr *nam, struct mbuf *control, struct thread *td)
{
	ng_btsocket_rfcomm_pcb_t	*pcb = so2rfcomm_pcb(so);
	int				 error = 0;

	/* Check socket and input */
	if (pcb == NULL || m == NULL || control != NULL) {
		error = EINVAL;
		goto drop;
	}

	mtx_lock(&pcb->pcb_mtx);

	/* Make sure DLC is connected */
	if (pcb->state != NG_BTSOCKET_RFCOMM_DLC_CONNECTED) {
		mtx_unlock(&pcb->pcb_mtx);
		error = ENOTCONN;
		goto drop;
	}

	/* Put the packet on the socket's send queue and wakeup RFCOMM task */
	sbappend(&pcb->so->so_snd, m, flags);
	m = NULL;
	
	if (!(pcb->flags & NG_BTSOCKET_RFCOMM_DLC_SENDING)) {
		pcb->flags |= NG_BTSOCKET_RFCOMM_DLC_SENDING;
		error = ng_btsocket_rfcomm_task_wakeup();
	}

	mtx_unlock(&pcb->pcb_mtx);
drop:
	NG_FREE_M(m); /* checks for != NULL */
	NG_FREE_M(control);

	return (error);
}