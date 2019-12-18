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
typedef  unsigned long u_long ;
struct unpcb {scalar_t__ unp_conn; } ;
struct sockstat {uintptr_t so_addr; char* dname; int dom_family; uintptr_t so_pcb; uintptr_t inp_ppcb; uintptr_t unp_conn; int /*<<< orphan*/  recvq; int /*<<< orphan*/  sendq; int /*<<< orphan*/  so_snd_sb_state; int /*<<< orphan*/  so_rcv_sb_state; int /*<<< orphan*/  proto; int /*<<< orphan*/  type; void* fs_typedep; } ;
struct TYPE_4__ {int /*<<< orphan*/  sb_ccc; int /*<<< orphan*/  sb_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  sb_ccc; int /*<<< orphan*/  sb_state; } ;
struct socket {int dom_family; TYPE_2__ so_rcv; TYPE_1__ so_snd; scalar_t__ so_pcb; int /*<<< orphan*/  pr_protocol; int /*<<< orphan*/  so_type; scalar_t__ dom_name; scalar_t__ pr_domain; scalar_t__ so_proto; } ;
struct protosw {int dom_family; TYPE_2__ so_rcv; TYPE_1__ so_snd; scalar_t__ so_pcb; int /*<<< orphan*/  pr_protocol; int /*<<< orphan*/  so_type; scalar_t__ dom_name; scalar_t__ pr_domain; scalar_t__ so_proto; } ;
struct inpcb {scalar_t__ inp_ppcb; } ;
struct filestat {uintptr_t so_addr; char* dname; int dom_family; uintptr_t so_pcb; uintptr_t inp_ppcb; uintptr_t unp_conn; int /*<<< orphan*/  recvq; int /*<<< orphan*/  sendq; int /*<<< orphan*/  so_snd_sb_state; int /*<<< orphan*/  so_rcv_sb_state; int /*<<< orphan*/  proto; int /*<<< orphan*/  type; void* fs_typedep; } ;
struct domain {int dom_family; TYPE_2__ so_rcv; TYPE_1__ so_snd; scalar_t__ so_pcb; int /*<<< orphan*/  pr_protocol; int /*<<< orphan*/  so_type; scalar_t__ dom_name; scalar_t__ pr_domain; scalar_t__ so_proto; } ;
typedef  size_t ssize_t ;
typedef  struct sockstat kvm_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  assert (struct sockstat*) ; 
 int /*<<< orphan*/  bzero (struct sockstat*,int) ; 
 int kvm_read (struct sockstat*,unsigned long,char*,int) ; 
 int /*<<< orphan*/  kvm_read_all (struct sockstat*,unsigned long,struct socket*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnx (char*,void*) ; 

__attribute__((used)) static int
procstat_get_socket_info_kvm(kvm_t *kd, struct filestat *fst,
    struct sockstat *sock, char *errbuf)
{
	struct domain dom;
	struct inpcb inpcb;
	struct protosw proto;
	struct socket s;
	struct unpcb unpcb;
	ssize_t len;
	void *so;

	assert(kd);
	assert(sock);
	assert(fst);
	bzero(sock, sizeof(*sock));
	so = fst->fs_typedep;
	if (so == NULL)
		goto fail;
	sock->so_addr = (uintptr_t)so;
	/* fill in socket */
	if (!kvm_read_all(kd, (unsigned long)so, &s,
	    sizeof(struct socket))) {
		warnx("can't read sock at %p", (void *)so);
		goto fail;
	}
	/* fill in protosw entry */
	if (!kvm_read_all(kd, (unsigned long)s.so_proto, &proto,
	    sizeof(struct protosw))) {
		warnx("can't read protosw at %p", (void *)s.so_proto);
		goto fail;
	}
	/* fill in domain */
	if (!kvm_read_all(kd, (unsigned long)proto.pr_domain, &dom,
	    sizeof(struct domain))) {
		warnx("can't read domain at %p",
		    (void *)proto.pr_domain);
		goto fail;
	}
	if ((len = kvm_read(kd, (unsigned long)dom.dom_name, sock->dname,
	    sizeof(sock->dname) - 1)) < 0) {
		warnx("can't read domain name at %p", (void *)dom.dom_name);
		sock->dname[0] = '\0';
	}
	else
		sock->dname[len] = '\0';
	
	/*
	 * Fill in known data.
	 */
	sock->type = s.so_type;
	sock->proto = proto.pr_protocol;
	sock->dom_family = dom.dom_family;
	sock->so_pcb = (uintptr_t)s.so_pcb;

	/*
	 * Protocol specific data.
	 */
	switch(dom.dom_family) {
	case AF_INET:
	case AF_INET6:
		if (proto.pr_protocol == IPPROTO_TCP) {
			if (s.so_pcb) {
				if (kvm_read(kd, (u_long)s.so_pcb,
				    (char *)&inpcb, sizeof(struct inpcb))
				    != sizeof(struct inpcb)) {
					warnx("can't read inpcb at %p",
					    (void *)s.so_pcb);
				} else
					sock->inp_ppcb =
					    (uintptr_t)inpcb.inp_ppcb;
				sock->sendq = s.so_snd.sb_ccc;
				sock->recvq = s.so_rcv.sb_ccc;
			}
		}
		break;
	case AF_UNIX:
		if (s.so_pcb) {
			if (kvm_read(kd, (u_long)s.so_pcb, (char *)&unpcb,
			    sizeof(struct unpcb)) != sizeof(struct unpcb)){
				warnx("can't read unpcb at %p",
				    (void *)s.so_pcb);
			} else if (unpcb.unp_conn) {
				sock->so_rcv_sb_state = s.so_rcv.sb_state;
				sock->so_snd_sb_state = s.so_snd.sb_state;
				sock->unp_conn = (uintptr_t)unpcb.unp_conn;
				sock->sendq = s.so_snd.sb_ccc;
				sock->recvq = s.so_rcv.sb_ccc;
			}
		}
		break;
	default:
		break;
	}
	return (0);

fail:
	if (errbuf != NULL)
		snprintf(errbuf, _POSIX2_LINE_MAX, "error");
	return (1);
}