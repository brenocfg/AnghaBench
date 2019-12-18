#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xsocket {int xso_len; uintptr_t xso_so; int so_options; uintptr_t so_pcb; int /*<<< orphan*/  so_oobmark; int /*<<< orphan*/  so_rcv; int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_qlimit; int /*<<< orphan*/  so_incqlen; int /*<<< orphan*/  so_qlen; int /*<<< orphan*/  so_error; int /*<<< orphan*/  so_timeo; int /*<<< orphan*/  xso_family; int /*<<< orphan*/  xso_protocol; int /*<<< orphan*/  so_state; int /*<<< orphan*/  so_linger; int /*<<< orphan*/  so_type; } ;
struct socket {int so_options; int /*<<< orphan*/  so_oobmark; int /*<<< orphan*/  so_rcv; int /*<<< orphan*/  so_snd; int /*<<< orphan*/  sol_qlimit; int /*<<< orphan*/  sol_incqlen; int /*<<< orphan*/  sol_qlen; int /*<<< orphan*/  so_error; int /*<<< orphan*/  so_timeo; scalar_t__ so_proto; scalar_t__ so_pcb; int /*<<< orphan*/  so_state; int /*<<< orphan*/  so_linger; int /*<<< orphan*/  so_type; } ;
struct protosw {int /*<<< orphan*/  dom_family; scalar_t__ pr_domain; int /*<<< orphan*/  pr_protocol; } ;
struct domain {int /*<<< orphan*/  dom_family; scalar_t__ pr_domain; int /*<<< orphan*/  pr_protocol; } ;
typedef  int /*<<< orphan*/  proto ;
typedef  int /*<<< orphan*/  domain ;

/* Variables and functions */
 int SO_ACCEPTCONN ; 
 int /*<<< orphan*/  bzero (struct xsocket*,int) ; 
 scalar_t__ kread (uintptr_t,struct protosw*,int) ; 
 int /*<<< orphan*/  sbtoxsockbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
sotoxsocket(struct socket *so, struct xsocket *xso)
{
	struct protosw proto;
	struct domain domain;

	bzero(xso, sizeof *xso);
	xso->xso_len = sizeof *xso;
	xso->xso_so = (uintptr_t)so;
	xso->so_type = so->so_type;
	xso->so_options = so->so_options;
	xso->so_linger = so->so_linger;
	xso->so_state = so->so_state;
	xso->so_pcb = (uintptr_t)so->so_pcb;
	if (kread((uintptr_t)so->so_proto, &proto, sizeof(proto)) != 0)
		return (-1);
	xso->xso_protocol = proto.pr_protocol;
	if (kread((uintptr_t)proto.pr_domain, &domain, sizeof(domain)) != 0)
		return (-1);
	xso->xso_family = domain.dom_family;
	xso->so_timeo = so->so_timeo;
	xso->so_error = so->so_error;
	if ((so->so_options & SO_ACCEPTCONN) != 0) {
		xso->so_qlen = so->sol_qlen;
		xso->so_incqlen = so->sol_incqlen;
		xso->so_qlimit = so->sol_qlimit;
	} else {
		sbtoxsockbuf(&so->so_snd, &xso->so_snd);
		sbtoxsockbuf(&so->so_rcv, &xso->so_rcv);
		xso->so_oobmark = so->so_oobmark;
	}
	return (0);
}