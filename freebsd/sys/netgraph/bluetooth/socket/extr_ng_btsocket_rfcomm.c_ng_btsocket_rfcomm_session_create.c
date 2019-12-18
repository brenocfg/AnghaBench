#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int16_t ;
struct thread {int dummy; } ;
struct sockopt {int sopt_valsize; int /*<<< orphan*/ * sopt_td; void* sopt_val; int /*<<< orphan*/  sopt_name; int /*<<< orphan*/  sopt_level; int /*<<< orphan*/  sopt_dir; } ;
struct socket {int /*<<< orphan*/  so_state; int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;
struct sockaddr_l2cap {int l2cap_len; void* l2cap_bdaddr_type; scalar_t__ l2cap_cid; int /*<<< orphan*/  l2cap_bdaddr; void* l2cap_psm; void* l2cap_family; } ;
struct sockaddr {int dummy; } ;
struct rfcomm_frame_hdr {int dummy; } ;
typedef  TYPE_1__* ng_btsocket_rfcomm_session_p ;
typedef  int /*<<< orphan*/  mtu ;
typedef  int /*<<< orphan*/  l2sa ;
typedef  int /*<<< orphan*/ * bdaddr_p ;
struct TYPE_7__ {int /*<<< orphan*/  session_mtx; struct socket* l2so; int /*<<< orphan*/  state; scalar_t__ flags; scalar_t__ mtu; int /*<<< orphan*/  dlcs; int /*<<< orphan*/  outq; } ;

/* Variables and functions */
 void* AF_BLUETOOTH ; 
 void* BDADDR_BREDR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MTX_DEF ; 
 int MTX_DUPOK ; 
 int /*<<< orphan*/  M_NETGRAPH_BTSOCKET_RFCOMM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_BTSOCKET_RFCOMM_SESSION_CLOSED ; 
 int /*<<< orphan*/  NG_BTSOCKET_RFCOMM_SESSION_CONNECTING ; 
 scalar_t__ NG_BTSOCKET_RFCOMM_SESSION_INITIATOR ; 
 int /*<<< orphan*/  NG_BTSOCKET_RFCOMM_SESSION_LISTENING ; 
 int /*<<< orphan*/  NG_BT_MBUFQ_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_L2CAP_PSM_RFCOMM ; 
 scalar_t__ RFCOMM_DEFAULT_MTU ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOL_L2CAP ; 
 int /*<<< orphan*/  SOPT_SET ; 
 int /*<<< orphan*/  SO_L2CAP_IMTU ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  SO_SND ; 
 int /*<<< orphan*/  SS_NBIO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_sessions ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_sessions_mtx ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_upcall ; 
 int sobind (struct socket*,struct sockaddr*,struct thread*) ; 
 int soconnect (struct socket*,struct sockaddr*,struct thread*) ; 
 int solisten (struct socket*,int,struct thread*) ; 
 int sosetopt (struct socket*,struct sockopt*) ; 
 int /*<<< orphan*/  soupcall_clear (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soupcall_set (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_btsocket_rfcomm_session_create(ng_btsocket_rfcomm_session_p *sp,
		struct socket *l2so, bdaddr_p src, bdaddr_p dst,
		struct thread *td)
{
	ng_btsocket_rfcomm_session_p	s = NULL;
	struct sockaddr_l2cap		l2sa;
	struct sockopt			l2sopt;
	int				error;
	u_int16_t			mtu;

	mtx_assert(&ng_btsocket_rfcomm_sessions_mtx, MA_OWNED);

	/* Allocate the RFCOMM session */
        s = malloc(sizeof(*s),
		M_NETGRAPH_BTSOCKET_RFCOMM, M_NOWAIT | M_ZERO);
        if (s == NULL)
                return (ENOMEM);

	/* Set defaults */
	s->mtu = RFCOMM_DEFAULT_MTU;
	s->flags = 0;
	s->state = NG_BTSOCKET_RFCOMM_SESSION_CLOSED;
	NG_BT_MBUFQ_INIT(&s->outq, ifqmaxlen);

	/*
	 * XXX Mark session mutex as DUPOK to prevent "duplicated lock of 
	 * the same type" message. When accepting new L2CAP connection
	 * ng_btsocket_rfcomm_session_accept() holds both session mutexes 
	 * for "old" (accepting) session and "new" (created) session.
	 */

	mtx_init(&s->session_mtx, "btsocks_rfcomm_session_mtx", NULL,
		MTX_DEF|MTX_DUPOK);

	LIST_INIT(&s->dlcs);

	/* Prepare L2CAP socket */
	SOCKBUF_LOCK(&l2so->so_rcv);
	soupcall_set(l2so, SO_RCV, ng_btsocket_rfcomm_upcall, NULL);
	SOCKBUF_UNLOCK(&l2so->so_rcv);
	SOCKBUF_LOCK(&l2so->so_snd);
	soupcall_set(l2so, SO_SND, ng_btsocket_rfcomm_upcall, NULL);
	SOCKBUF_UNLOCK(&l2so->so_snd);
	l2so->so_state |= SS_NBIO;
	s->l2so = l2so;

	mtx_lock(&s->session_mtx);

	/*
	 * "src" == NULL and "dst" == NULL means just create session.
	 * caller must do the rest
	 */

	if (src == NULL && dst == NULL)
		goto done;

	/*
	 * Set incoming MTU on L2CAP socket. It is RFCOMM session default MTU 
	 * plus 5 bytes: RFCOMM frame header, one extra byte for length and one
	 * extra byte for credits.
	 */

	mtu = s->mtu + sizeof(struct rfcomm_frame_hdr) + 1 + 1;

	l2sopt.sopt_dir = SOPT_SET;
	l2sopt.sopt_level = SOL_L2CAP;
	l2sopt.sopt_name = SO_L2CAP_IMTU;
	l2sopt.sopt_val = (void *) &mtu;
	l2sopt.sopt_valsize = sizeof(mtu);
	l2sopt.sopt_td = NULL;

	error = sosetopt(s->l2so, &l2sopt);
	if (error != 0)
		goto bad;

	/* Bind socket to "src" address */
	l2sa.l2cap_len = sizeof(l2sa);
	l2sa.l2cap_family = AF_BLUETOOTH;
	l2sa.l2cap_psm = (dst == NULL)? htole16(NG_L2CAP_PSM_RFCOMM) : 0;
	bcopy(src, &l2sa.l2cap_bdaddr, sizeof(l2sa.l2cap_bdaddr));
	l2sa.l2cap_cid = 0;
	l2sa.l2cap_bdaddr_type = BDADDR_BREDR;

	error = sobind(s->l2so, (struct sockaddr *) &l2sa, td);
	if (error != 0)
		goto bad;

	/* If "dst" is not NULL then initiate connect(), otherwise listen() */
	if (dst == NULL) {
		s->flags = 0;
		s->state = NG_BTSOCKET_RFCOMM_SESSION_LISTENING;

		error = solisten(s->l2so, 10, td);
		if (error != 0)
			goto bad;
	} else {
		s->flags = NG_BTSOCKET_RFCOMM_SESSION_INITIATOR;
		s->state = NG_BTSOCKET_RFCOMM_SESSION_CONNECTING;

		l2sa.l2cap_len = sizeof(l2sa);   
		l2sa.l2cap_family = AF_BLUETOOTH;
		l2sa.l2cap_psm = htole16(NG_L2CAP_PSM_RFCOMM);
	        bcopy(dst, &l2sa.l2cap_bdaddr, sizeof(l2sa.l2cap_bdaddr));
		l2sa.l2cap_cid = 0;
		l2sa.l2cap_bdaddr_type = BDADDR_BREDR;

		error = soconnect(s->l2so, (struct sockaddr *) &l2sa, td);
		if (error != 0)
			goto bad;
	}

done:
	LIST_INSERT_HEAD(&ng_btsocket_rfcomm_sessions, s, next);
	*sp = s;

	mtx_unlock(&s->session_mtx);

	return (0);

bad:
	mtx_unlock(&s->session_mtx);

	/* Return L2CAP socket back to its original state */
	SOCKBUF_LOCK(&l2so->so_rcv);
	soupcall_clear(s->l2so, SO_RCV);
	SOCKBUF_UNLOCK(&l2so->so_rcv);
	SOCKBUF_LOCK(&l2so->so_snd);
	soupcall_clear(s->l2so, SO_SND);
	SOCKBUF_UNLOCK(&l2so->so_snd);
	l2so->so_state &= ~SS_NBIO;

	mtx_destroy(&s->session_mtx);
	bzero(s, sizeof(*s));
	free(s, M_NETGRAPH_BTSOCKET_RFCOMM);

	return (error);
}