#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xsocket {int xso_len; uintptr_t xso_so; uintptr_t so_pcb; int /*<<< orphan*/  so_rcv; int /*<<< orphan*/  so_snd; scalar_t__ so_oobmark; scalar_t__ so_qlimit; scalar_t__ so_incqlen; scalar_t__ so_qlen; int /*<<< orphan*/  so_state; int /*<<< orphan*/  so_pgid; int /*<<< orphan*/  so_uid; int /*<<< orphan*/  so_error; int /*<<< orphan*/  so_timeo; int /*<<< orphan*/  xso_family; int /*<<< orphan*/  xso_protocol; int /*<<< orphan*/  so_linger; int /*<<< orphan*/  so_options; int /*<<< orphan*/  so_type; } ;
struct socket {int /*<<< orphan*/  so_rcv; int /*<<< orphan*/  so_snd; scalar_t__ so_oobmark; int /*<<< orphan*/  so_qstate; scalar_t__ sol_qlimit; scalar_t__ sol_incqlen; scalar_t__ sol_qlen; TYPE_4__* so_sigio; TYPE_3__* so_cred; int /*<<< orphan*/  so_error; int /*<<< orphan*/  so_timeo; TYPE_2__* so_proto; scalar_t__ so_pcb; int /*<<< orphan*/  so_state; int /*<<< orphan*/  so_linger; int /*<<< orphan*/  so_options; int /*<<< orphan*/  so_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  sio_pgid; } ;
struct TYPE_7__ {int /*<<< orphan*/  cr_uid; } ;
struct TYPE_6__ {TYPE_1__* pr_domain; int /*<<< orphan*/  pr_protocol; } ;
struct TYPE_5__ {int /*<<< orphan*/  dom_family; } ;

/* Variables and functions */
 scalar_t__ SOLISTENING (struct socket*) ; 
 int /*<<< orphan*/  bzero (struct xsocket*,int) ; 
 int /*<<< orphan*/  sbtoxsockbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
sotoxsocket(struct socket *so, struct xsocket *xso)
{

	bzero(xso, sizeof(*xso));
	xso->xso_len = sizeof *xso;
	xso->xso_so = (uintptr_t)so;
	xso->so_type = so->so_type;
	xso->so_options = so->so_options;
	xso->so_linger = so->so_linger;
	xso->so_state = so->so_state;
	xso->so_pcb = (uintptr_t)so->so_pcb;
	xso->xso_protocol = so->so_proto->pr_protocol;
	xso->xso_family = so->so_proto->pr_domain->dom_family;
	xso->so_timeo = so->so_timeo;
	xso->so_error = so->so_error;
	xso->so_uid = so->so_cred->cr_uid;
	xso->so_pgid = so->so_sigio ? so->so_sigio->sio_pgid : 0;
	if (SOLISTENING(so)) {
		xso->so_qlen = so->sol_qlen;
		xso->so_incqlen = so->sol_incqlen;
		xso->so_qlimit = so->sol_qlimit;
		xso->so_oobmark = 0;
	} else {
		xso->so_state |= so->so_qstate;
		xso->so_qlen = xso->so_incqlen = xso->so_qlimit = 0;
		xso->so_oobmark = so->so_oobmark;
		sbtoxsockbuf(&so->so_snd, &xso->so_snd);
		sbtoxsockbuf(&so->so_rcv, &xso->so_rcv);
	}
}