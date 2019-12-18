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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct socket {int dummy; } ;
struct sockaddr_rfcomm {scalar_t__ rfcomm_family; int rfcomm_len; int rfcomm_channel; int /*<<< orphan*/  rfcomm_bdaddr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_12__ {int state; int /*<<< orphan*/  session_mtx; int /*<<< orphan*/  l2so; int /*<<< orphan*/  mtu; int /*<<< orphan*/  dlcs; } ;
typedef  TYPE_1__ ng_btsocket_rfcomm_session_t ;
struct TYPE_13__ {int channel; int dlci; int /*<<< orphan*/  pcb_mtx; int /*<<< orphan*/  state; int /*<<< orphan*/  src; int /*<<< orphan*/  mtu; int /*<<< orphan*/  so; TYPE_1__* session; int /*<<< orphan*/  dst; } ;
typedef  TYPE_2__ ng_btsocket_rfcomm_pcb_t ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_14__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ AF_BLUETOOTH ; 
 int /*<<< orphan*/  BLUETOOTH_PROTO_L2CAP ; 
 int EAFNOSUPPORT ; 
 int EBUSY ; 
 int ECONNRESET ; 
 int EDESTADDRREQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  INITIATOR (TYPE_1__*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_BTSOCKET_RFCOMM_DLC_CONFIGURING ; 
 int /*<<< orphan*/  NG_BTSOCKET_RFCOMM_DLC_W4_CONNECT ; 
#define  NG_BTSOCKET_RFCOMM_SESSION_CONNECTED 130 
#define  NG_BTSOCKET_RFCOMM_SESSION_CONNECTING 129 
#define  NG_BTSOCKET_RFCOMM_SESSION_OPEN 128 
 int /*<<< orphan*/  NG_HCI_BDADDR_ANY ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int RFCOMM_MKDLCI (int,int) ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ng_btsocket_rfcomm_pcb_by_dlci (TYPE_1__*,int) ; 
 int ng_btsocket_rfcomm_send_pn (TYPE_2__*) ; 
 TYPE_1__* ng_btsocket_rfcomm_session_by_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ng_btsocket_rfcomm_session_create (TYPE_1__**,struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct thread*) ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_sessions_mtx ; 
 int ng_btsocket_rfcomm_task_wakeup () ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_timeout (TYPE_2__*) ; 
 int /*<<< orphan*/  session_next ; 
 TYPE_4__* so2l2cap_pcb (int /*<<< orphan*/ ) ; 
 TYPE_2__* so2rfcomm_pcb (struct socket*) ; 
 int /*<<< orphan*/  soclose (struct socket*) ; 
 int socreate (int /*<<< orphan*/ ,struct socket**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  soisconnecting (int /*<<< orphan*/ ) ; 

int
ng_btsocket_rfcomm_connect(struct socket *so, struct sockaddr *nam, 
		struct thread *td)
{
	ng_btsocket_rfcomm_pcb_t	*pcb = so2rfcomm_pcb(so);
	struct sockaddr_rfcomm		*sa = (struct sockaddr_rfcomm *) nam;
	ng_btsocket_rfcomm_session_t	*s = NULL;
	struct socket			*l2so = NULL;
	int				 dlci, error = 0;

	if (pcb == NULL)
		return (EINVAL);

	/* Verify address */
	if (sa == NULL)
		return (EINVAL);
	if (sa->rfcomm_family != AF_BLUETOOTH)
		return (EAFNOSUPPORT);
	if (sa->rfcomm_len != sizeof(*sa))
		return (EINVAL);
	if (sa->rfcomm_channel > 30)
		return (EINVAL);
	if (sa->rfcomm_channel == 0 ||
	    bcmp(&sa->rfcomm_bdaddr, NG_HCI_BDADDR_ANY, sizeof(bdaddr_t)) == 0)
		return (EDESTADDRREQ);

	/*
	 * Note that we will not check for errors in socreate() because
	 * if we failed to create L2CAP socket at this point we still
	 * might have already open session.
	 */

	error = socreate(PF_BLUETOOTH, &l2so, SOCK_SEQPACKET,
			BLUETOOTH_PROTO_L2CAP, td->td_ucred, td);

	/* 
	 * Look for session between "pcb->src" and "sa->rfcomm_bdaddr" (dst)
	 */

	mtx_lock(&ng_btsocket_rfcomm_sessions_mtx);

	s = ng_btsocket_rfcomm_session_by_addr(&pcb->src, &sa->rfcomm_bdaddr);
	if (s == NULL) {
		/*
		 * We need to create new RFCOMM session. Check if we have L2CAP
		 * socket. If l2so == NULL then error has the error code from
		 * socreate()
		 */

		if (l2so == NULL) {
			mtx_unlock(&ng_btsocket_rfcomm_sessions_mtx);
			return (error);
		}

		error = ng_btsocket_rfcomm_session_create(&s, l2so,
				&pcb->src, &sa->rfcomm_bdaddr, td);
		if (error != 0) {
			mtx_unlock(&ng_btsocket_rfcomm_sessions_mtx);
			soclose(l2so);

			return (error);
		}
	} else if (l2so != NULL)
		soclose(l2so); /* we don't need new L2CAP socket */

	/*
	 * Check if we already have the same DLCI the same session
	 */

	mtx_lock(&s->session_mtx);
	mtx_lock(&pcb->pcb_mtx);

	dlci = RFCOMM_MKDLCI(!INITIATOR(s), sa->rfcomm_channel);

	if (ng_btsocket_rfcomm_pcb_by_dlci(s, dlci) != NULL) {
		mtx_unlock(&pcb->pcb_mtx);
		mtx_unlock(&s->session_mtx);
		mtx_unlock(&ng_btsocket_rfcomm_sessions_mtx);

		return (EBUSY);
	}

	/*
	 * Check session state and if its not acceptable then refuse connection
	 */

	switch (s->state) {
	case NG_BTSOCKET_RFCOMM_SESSION_CONNECTING:
	case NG_BTSOCKET_RFCOMM_SESSION_CONNECTED:
	case NG_BTSOCKET_RFCOMM_SESSION_OPEN:
		/*
		 * Update destination address and channel and attach 
		 * DLC to the session
		 */

		bcopy(&sa->rfcomm_bdaddr, &pcb->dst, sizeof(pcb->dst));
		pcb->channel = sa->rfcomm_channel;
		pcb->dlci = dlci;

		LIST_INSERT_HEAD(&s->dlcs, pcb, session_next);
		pcb->session = s;

		ng_btsocket_rfcomm_timeout(pcb);
		soisconnecting(pcb->so);

		if (s->state == NG_BTSOCKET_RFCOMM_SESSION_OPEN) {
			pcb->mtu = s->mtu;
			bcopy(&so2l2cap_pcb(s->l2so)->src, &pcb->src,
				sizeof(pcb->src));

			pcb->state = NG_BTSOCKET_RFCOMM_DLC_CONFIGURING;

			error = ng_btsocket_rfcomm_send_pn(pcb);
			if (error == 0)
				error = ng_btsocket_rfcomm_task_wakeup();
		} else
			pcb->state = NG_BTSOCKET_RFCOMM_DLC_W4_CONNECT;
		break;

	default:
		error = ECONNRESET;
		break;
	}

	mtx_unlock(&pcb->pcb_mtx);
	mtx_unlock(&s->session_mtx);
	mtx_unlock(&ng_btsocket_rfcomm_sessions_mtx);

	return (error);
}