#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int vflag; int family; int proto; scalar_t__ state; int /*<<< orphan*/  stack; struct addr* laddr; int /*<<< orphan*/  pcb; struct sock* next; struct addr* faddr; int /*<<< orphan*/  protoname; } ;
struct TYPE_2__ {int /*<<< orphan*/  ss_len; } ;
struct addr {struct addr* next; int /*<<< orphan*/  state; int /*<<< orphan*/  encaps_port; TYPE_1__ address; } ;
typedef  int /*<<< orphan*/  kvaddr_t ;

/* Variables and functions */
#define  AF_INET 132 
#define  AF_INET6 131 
#define  AF_UNIX 130 
 int HASHSIZE ; 
 int INP_IPV4 ; 
 int INP_IPV6 ; 
#define  IPPROTO_SCTP 129 
#define  IPPROTO_TCP 128 
 scalar_t__ SCTP_BOUND ; 
 scalar_t__ SCTP_CLOSED ; 
 scalar_t__ SCTP_LISTEN ; 
 int /*<<< orphan*/  TCP_FUNCTION_NAME_LEN_MAX ; 
 scalar_t__ TCP_NSTATES ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errx (int,char*,void*,void*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ opt_S ; 
 scalar_t__ opt_U ; 
 scalar_t__ opt_s ; 
 int /*<<< orphan*/  opt_w ; 
 int printaddr (TYPE_1__*) ; 
 int /*<<< orphan*/  sctp_conn_state (scalar_t__) ; 
 int /*<<< orphan*/  sctp_path_state (int /*<<< orphan*/ ) ; 
 struct sock** sockhash ; 
 int /*<<< orphan*/ * tcpstates ; 
 scalar_t__ xprintf (char*,...) ; 

__attribute__((used)) static void
displaysock(struct sock *s, int pos)
{
	kvaddr_t p;
	int hash, first, offset;
	struct addr *laddr, *faddr;
	struct sock *s_tmp;

	while (pos < 29)
		pos += xprintf(" ");
	pos += xprintf("%s", s->protoname);
	if (s->vflag & INP_IPV4)
		pos += xprintf("4");
	if (s->vflag & INP_IPV6)
		pos += xprintf("6");
	if (s->vflag & (INP_IPV4 | INP_IPV6))
		pos += xprintf(" ");
	laddr = s->laddr;
	faddr = s->faddr;
	first = 1;
	while (laddr != NULL || faddr != NULL) {
		offset = 36;
		while (pos < offset)
			pos += xprintf(" ");
		switch (s->family) {
		case AF_INET:
		case AF_INET6:
			if (laddr != NULL) {
				pos += printaddr(&laddr->address);
				if (s->family == AF_INET6 && pos >= 58)
					pos += xprintf(" ");
			}
			offset += opt_w ? 46 : 22;
			while (pos < offset)
				pos += xprintf(" ");
			if (faddr != NULL)
				pos += printaddr(&faddr->address);
			offset += opt_w ? 46 : 22;
			break;
		case AF_UNIX:
			if ((laddr == NULL) || (faddr == NULL))
				errx(1, "laddr = %p or faddr = %p is NULL",
				    (void *)laddr, (void *)faddr);
			/* server */
			if (laddr->address.ss_len > 0) {
				pos += printaddr(&laddr->address);
				break;
			}
			/* client */
			p = *(kvaddr_t*)&(faddr->address);
			if (p == 0) {
				pos += xprintf("(not connected)");
				offset += opt_w ? 92 : 44;
				break;
			}
			pos += xprintf("-> ");
			for (hash = 0; hash < HASHSIZE; ++hash) {
				for (s_tmp = sockhash[hash];
				    s_tmp != NULL;
				    s_tmp = s_tmp->next)
					if (s_tmp->pcb == p)
						break;
				if (s_tmp != NULL)
					break;
			}
			if (s_tmp == NULL || s_tmp->laddr == NULL ||
			    s_tmp->laddr->address.ss_len == 0)
				pos += xprintf("??");
			else
				pos += printaddr(&s_tmp->laddr->address);
			offset += opt_w ? 92 : 44;
			break;
		default:
			abort();
		}
		if (opt_U) {
			if (faddr != NULL &&
			    s->proto == IPPROTO_SCTP &&
			    s->state != SCTP_CLOSED &&
			    s->state != SCTP_BOUND &&
			    s->state != SCTP_LISTEN) {
				while (pos < offset)
					pos += xprintf(" ");
				pos += xprintf("%u",
				    ntohs(faddr->encaps_port));
			}
			offset += 7;
		}
		if (opt_s) {
			if (faddr != NULL &&
			    s->proto == IPPROTO_SCTP &&
			    s->state != SCTP_CLOSED &&
			    s->state != SCTP_BOUND &&
			    s->state != SCTP_LISTEN) {
				while (pos < offset)
					pos += xprintf(" ");
				pos += xprintf("%s",
				    sctp_path_state(faddr->state));
			}
			offset += 13;
		}
		if (first) {
			if (opt_s) {
				if (s->proto == IPPROTO_SCTP ||
				    s->proto == IPPROTO_TCP) {
					while (pos < offset)
						pos += xprintf(" ");
					switch (s->proto) {
					case IPPROTO_SCTP:
						pos += xprintf("%s",
						    sctp_conn_state(s->state));
						break;
					case IPPROTO_TCP:
						if (s->state >= 0 &&
						    s->state < TCP_NSTATES)
							pos += xprintf("%s",
							    tcpstates[s->state]);
						else
							pos += xprintf("?");
						break;
					}
				}
				offset += 13;
			}
			if (opt_S && s->proto == IPPROTO_TCP) {
				while (pos < offset)
					pos += xprintf(" ");
				xprintf("%.*s", TCP_FUNCTION_NAME_LEN_MAX,
				    s->stack);
			}
		}
		if (laddr != NULL)
			laddr = laddr->next;
		if (faddr != NULL)
			faddr = faddr->next;
		if ((laddr != NULL) || (faddr != NULL)) {
			xprintf("\n");
			pos = 0;
		}
		first = 0;
	}
	xprintf("\n");
}