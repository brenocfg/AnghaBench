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
typedef  int /*<<< orphan*/  u_long ;
struct unpcb {int unp_refcount; scalar_t__ unp_ino; scalar_t__ unp_gencnt; int /*<<< orphan*/  unp_flags; struct socket* unp_socket; int /*<<< orphan*/  unp_refs; } ;
struct thread {int dummy; } ;
struct TYPE_4__ {scalar_t__ sb_hiwat; } ;
struct TYPE_3__ {scalar_t__ sb_hiwat; } ;
struct socket {int so_type; int /*<<< orphan*/ * so_listen; struct unpcb* so_pcb; TYPE_2__ so_rcv; TYPE_1__ so_snd; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct unpcb*,int /*<<< orphan*/ ) ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
#define  SOCK_DGRAM 130 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 int /*<<< orphan*/  UNP_LINK_WLOCK () ; 
 int UNP_LINK_WOWNED () ; 
 int /*<<< orphan*/  UNP_LINK_WUNLOCK () ; 
 int /*<<< orphan*/  UNP_NASCENT ; 
 int /*<<< orphan*/  UNP_PCB_LOCK_INIT (struct unpcb*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct unpcb* uma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unp_count ; 
 int /*<<< orphan*/  unp_dhead ; 
 scalar_t__ unp_gencnt ; 
 scalar_t__ unp_ino ; 
 int /*<<< orphan*/  unp_link ; 
 int /*<<< orphan*/  unp_shead ; 
 int /*<<< orphan*/  unp_sphead ; 
 int /*<<< orphan*/  unp_zone ; 
 int /*<<< orphan*/  unpdg_recvspace ; 
 int /*<<< orphan*/  unpdg_sendspace ; 
 int /*<<< orphan*/  unpsp_recvspace ; 
 int /*<<< orphan*/  unpsp_sendspace ; 
 int /*<<< orphan*/  unpst_recvspace ; 
 int /*<<< orphan*/  unpst_sendspace ; 

__attribute__((used)) static int
uipc_attach(struct socket *so, int proto, struct thread *td)
{
	u_long sendspace, recvspace;
	struct unpcb *unp;
	int error;
	bool locked;

	KASSERT(so->so_pcb == NULL, ("uipc_attach: so_pcb != NULL"));
	if (so->so_snd.sb_hiwat == 0 || so->so_rcv.sb_hiwat == 0) {
		switch (so->so_type) {
		case SOCK_STREAM:
			sendspace = unpst_sendspace;
			recvspace = unpst_recvspace;
			break;

		case SOCK_DGRAM:
			sendspace = unpdg_sendspace;
			recvspace = unpdg_recvspace;
			break;

		case SOCK_SEQPACKET:
			sendspace = unpsp_sendspace;
			recvspace = unpsp_recvspace;
			break;

		default:
			panic("uipc_attach");
		}
		error = soreserve(so, sendspace, recvspace);
		if (error)
			return (error);
	}
	unp = uma_zalloc(unp_zone, M_NOWAIT | M_ZERO);
	if (unp == NULL)
		return (ENOBUFS);
	LIST_INIT(&unp->unp_refs);
	UNP_PCB_LOCK_INIT(unp);
	unp->unp_socket = so;
	so->so_pcb = unp;
	unp->unp_refcount = 1;
	if (so->so_listen != NULL)
		unp->unp_flags |= UNP_NASCENT;

	if ((locked = UNP_LINK_WOWNED()) == false)
		UNP_LINK_WLOCK();

	unp->unp_gencnt = ++unp_gencnt;
	unp->unp_ino = ++unp_ino;
	unp_count++;
	switch (so->so_type) {
	case SOCK_STREAM:
		LIST_INSERT_HEAD(&unp_shead, unp, unp_link);
		break;

	case SOCK_DGRAM:
		LIST_INSERT_HEAD(&unp_dhead, unp, unp_link);
		break;

	case SOCK_SEQPACKET:
		LIST_INSERT_HEAD(&unp_sphead, unp, unp_link);
		break;

	default:
		panic("uipc_attach");
	}

	if (locked == false)
		UNP_LINK_WUNLOCK();

	return (0);
}