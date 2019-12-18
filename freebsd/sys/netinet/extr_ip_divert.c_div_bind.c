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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct socket {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INP_HASH_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_HASH_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_INFO_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_INFO_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  V_divcbinfo ; 
 int in_pcbbind (struct inpcb*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
div_bind(struct socket *so, struct sockaddr *nam, struct thread *td)
{
	struct inpcb *inp;
	int error;

	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("div_bind: inp == NULL"));
	/* in_pcbbind assumes that nam is a sockaddr_in
	 * and in_pcbbind requires a valid address. Since divert
	 * sockets don't we need to make sure the address is
	 * filled in properly.
	 * XXX -- divert should not be abusing in_pcbind
	 * and should probably have its own family.
	 */
	if (nam->sa_family != AF_INET)
		return EAFNOSUPPORT;
	((struct sockaddr_in *)nam)->sin_addr.s_addr = INADDR_ANY;
	INP_INFO_WLOCK(&V_divcbinfo);
	INP_WLOCK(inp);
	INP_HASH_WLOCK(&V_divcbinfo);
	error = in_pcbbind(inp, nam, td->td_ucred);
	INP_HASH_WUNLOCK(&V_divcbinfo);
	INP_WUNLOCK(inp);
	INP_INFO_WUNLOCK(&V_divcbinfo);
	return error;
}