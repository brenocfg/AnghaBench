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
struct thread {int dummy; } ;
struct socket {scalar_t__ so_pcb; } ;
struct inpcb {int inp_ip_p; int /*<<< orphan*/  inp_flags; int /*<<< orphan*/  inp_vflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_HDRINCL ; 
 int /*<<< orphan*/  INP_INFO_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_INFO_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_IPV4 ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PRIV_NETINET_DIVERT ; 
 int /*<<< orphan*/  V_divcbinfo ; 
 int /*<<< orphan*/  div_recvspace ; 
 int /*<<< orphan*/  div_sendspace ; 
 int in_pcballoc (struct socket*,int /*<<< orphan*/ *) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
div_attach(struct socket *so, int proto, struct thread *td)
{
	struct inpcb *inp;
	int error;

	inp  = sotoinpcb(so);
	KASSERT(inp == NULL, ("div_attach: inp != NULL"));
	if (td != NULL) {
		error = priv_check(td, PRIV_NETINET_DIVERT);
		if (error)
			return (error);
	}
	error = soreserve(so, div_sendspace, div_recvspace);
	if (error)
		return error;
	INP_INFO_WLOCK(&V_divcbinfo);
	error = in_pcballoc(so, &V_divcbinfo);
	if (error) {
		INP_INFO_WUNLOCK(&V_divcbinfo);
		return error;
	}
	inp = (struct inpcb *)so->so_pcb;
	INP_INFO_WUNLOCK(&V_divcbinfo);
	inp->inp_ip_p = proto;
	inp->inp_vflag |= INP_IPV4;
	inp->inp_flags |= INP_HDRINCL;
	INP_WUNLOCK(inp);
	return 0;
}