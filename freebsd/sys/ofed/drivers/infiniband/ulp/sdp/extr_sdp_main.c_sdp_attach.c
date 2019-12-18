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
struct thread {int dummy; } ;
struct TYPE_4__ {scalar_t__ sb_hiwat; int /*<<< orphan*/  sb_flags; } ;
struct TYPE_3__ {scalar_t__ sb_hiwat; int /*<<< orphan*/  sb_flags; } ;
struct socket {int so_options; scalar_t__ so_linger; scalar_t__ so_pcb; int /*<<< orphan*/  so_cred; TYPE_2__ so_snd; TYPE_1__ so_rcv; } ;
struct sdp_sock {int /*<<< orphan*/  rxctlq; int /*<<< orphan*/  state; scalar_t__ qp_active; scalar_t__ flags; int /*<<< orphan*/  cred; struct socket* socket; int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct sdp_sock*,int /*<<< orphan*/ ) ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SB_AUTOSIZE ; 
 int /*<<< orphan*/  SDP_LIST_WLOCK () ; 
 int /*<<< orphan*/  SDP_LIST_WUNLOCK () ; 
 int SO_LINGER ; 
 int /*<<< orphan*/  TCPS_CLOSED ; 
 scalar_t__ TCP_LINGERTIME ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sdp_count ; 
 int /*<<< orphan*/  sdp_init_sock (struct socket*) ; 
 int /*<<< orphan*/  sdp_list ; 
 int /*<<< orphan*/  sdp_recvspace ; 
 int /*<<< orphan*/  sdp_sendspace ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 
 int /*<<< orphan*/  sdp_zone ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sdp_sock* uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sdp_attach(struct socket *so, int proto, struct thread *td)
{
	struct sdp_sock *ssk;
	int error;

	ssk = sdp_sk(so);
	KASSERT(ssk == NULL, ("sdp_attach: ssk already set on so %p", so));
	if (so->so_snd.sb_hiwat == 0 || so->so_rcv.sb_hiwat == 0) {
		error = soreserve(so, sdp_sendspace, sdp_recvspace);
		if (error)
			return (error);
	}
	so->so_rcv.sb_flags |= SB_AUTOSIZE;
	so->so_snd.sb_flags |= SB_AUTOSIZE;
	ssk = uma_zalloc(sdp_zone, M_NOWAIT | M_ZERO);
	if (ssk == NULL)
		return (ENOBUFS);
	rw_init(&ssk->lock, "sdpsock");
	ssk->socket = so;
	ssk->cred = crhold(so->so_cred);
	so->so_pcb = (caddr_t)ssk;
	sdp_init_sock(so);
	ssk->flags = 0;
	ssk->qp_active = 0;
	ssk->state = TCPS_CLOSED;
	mbufq_init(&ssk->rxctlq, INT_MAX);
	SDP_LIST_WLOCK();
	LIST_INSERT_HEAD(&sdp_list, ssk, list);
	sdp_count++;
	SDP_LIST_WUNLOCK();
	if ((so->so_options & SO_LINGER) && so->so_linger == 0)
		so->so_linger = TCP_LINGERTIME;

	return (0);
}