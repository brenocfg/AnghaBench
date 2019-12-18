#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct unpcb {scalar_t__ unp_conn; } ;
struct TYPE_12__ {int /*<<< orphan*/  sb_state; } ;
struct socket {TYPE_5__* so_proto; TYPE_6__ so_rcv; TYPE_6__ so_snd; int /*<<< orphan*/ * so_pcb; int /*<<< orphan*/  so_type; int /*<<< orphan*/  so_vnet; } ;
struct sockaddr {int sa_len; } ;
struct TYPE_8__ {uintptr_t kf_sock_pcb; uintptr_t kf_sock_inpcb; uintptr_t kf_sock_unpconn; int /*<<< orphan*/  kf_sa_peer; int /*<<< orphan*/  kf_sa_local; void* kf_sock_recvq; void* kf_sock_sendq; int /*<<< orphan*/  kf_sock_snd_sb_state; int /*<<< orphan*/  kf_sock_rcv_sb_state; int /*<<< orphan*/  kf_sock_protocol0; int /*<<< orphan*/  kf_sock_domain0; int /*<<< orphan*/  kf_sock_type0; } ;
struct TYPE_9__ {TYPE_2__ kf_sock; } ;
struct kinfo_file {int /*<<< orphan*/  kf_path; TYPE_3__ kf_un; int /*<<< orphan*/  kf_type; } ;
struct inpcb {scalar_t__ inp_ppcb; } ;
struct filedesc {int dummy; } ;
struct file {struct socket* f_data; } ;
struct TYPE_11__ {TYPE_4__* pr_domain; TYPE_1__* pr_usrreqs; int /*<<< orphan*/  pr_protocol; } ;
struct TYPE_10__ {int /*<<< orphan*/  dom_name; int /*<<< orphan*/  dom_family; } ;
struct TYPE_7__ {int (* pru_sockaddr ) (struct socket*,struct sockaddr**) ;int (* pru_peeraddr ) (struct socket*,struct sockaddr**) ;} ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  KF_TYPE_SOCKET ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  bcopy (struct sockaddr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 void* sbused (TYPE_6__*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct socket*,struct sockaddr**) ; 
 int stub2 (struct socket*,struct sockaddr**) ; 

__attribute__((used)) static int
soo_fill_kinfo(struct file *fp, struct kinfo_file *kif, struct filedesc *fdp)
{
	struct sockaddr *sa;
	struct inpcb *inpcb;
	struct unpcb *unpcb;
	struct socket *so;
	int error;

	kif->kf_type = KF_TYPE_SOCKET;
	so = fp->f_data;
	CURVNET_SET(so->so_vnet);
	kif->kf_un.kf_sock.kf_sock_domain0 =
	    so->so_proto->pr_domain->dom_family;
	kif->kf_un.kf_sock.kf_sock_type0 = so->so_type;
	kif->kf_un.kf_sock.kf_sock_protocol0 = so->so_proto->pr_protocol;
	kif->kf_un.kf_sock.kf_sock_pcb = (uintptr_t)so->so_pcb;
	switch (kif->kf_un.kf_sock.kf_sock_domain0) {
	case AF_INET:
	case AF_INET6:
		if (kif->kf_un.kf_sock.kf_sock_protocol0 == IPPROTO_TCP) {
			if (so->so_pcb != NULL) {
				inpcb = (struct inpcb *)(so->so_pcb);
				kif->kf_un.kf_sock.kf_sock_inpcb =
				    (uintptr_t)inpcb->inp_ppcb;
				kif->kf_un.kf_sock.kf_sock_sendq =
				    sbused(&so->so_snd);
				kif->kf_un.kf_sock.kf_sock_recvq =
				    sbused(&so->so_rcv);
			}
		}
		break;
	case AF_UNIX:
		if (so->so_pcb != NULL) {
			unpcb = (struct unpcb *)(so->so_pcb);
			if (unpcb->unp_conn) {
				kif->kf_un.kf_sock.kf_sock_unpconn =
				    (uintptr_t)unpcb->unp_conn;
				kif->kf_un.kf_sock.kf_sock_rcv_sb_state =
				    so->so_rcv.sb_state;
				kif->kf_un.kf_sock.kf_sock_snd_sb_state =
				    so->so_snd.sb_state;
				kif->kf_un.kf_sock.kf_sock_sendq =
				    sbused(&so->so_snd);
				kif->kf_un.kf_sock.kf_sock_recvq =
				    sbused(&so->so_rcv);
			}
		}
		break;
	}
	error = so->so_proto->pr_usrreqs->pru_sockaddr(so, &sa);
	if (error == 0 &&
	    sa->sa_len <= sizeof(kif->kf_un.kf_sock.kf_sa_local)) {
		bcopy(sa, &kif->kf_un.kf_sock.kf_sa_local, sa->sa_len);
		free(sa, M_SONAME);
	}
	error = so->so_proto->pr_usrreqs->pru_peeraddr(so, &sa);
	if (error == 0 &&
	    sa->sa_len <= sizeof(kif->kf_un.kf_sock.kf_sa_peer)) {
		bcopy(sa, &kif->kf_un.kf_sock.kf_sa_peer, sa->sa_len);
		free(sa, M_SONAME);
	}
	strncpy(kif->kf_path, so->so_proto->pr_domain->dom_name,
	    sizeof(kif->kf_path));
	CURVNET_RESTORE();
	return (0);	
}