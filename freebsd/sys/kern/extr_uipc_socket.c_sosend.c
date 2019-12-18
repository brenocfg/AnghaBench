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
struct uio {int dummy; } ;
struct thread {int dummy; } ;
struct socket {TYPE_2__* so_proto; int /*<<< orphan*/  so_vnet; } ;
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_sosend ) (struct socket*,struct sockaddr*,struct uio*,struct mbuf*,struct mbuf*,int,struct thread*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  SOLISTENING (struct socket*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int stub1 (struct socket*,struct sockaddr*,struct uio*,struct mbuf*,struct mbuf*,int,struct thread*) ; 

int
sosend(struct socket *so, struct sockaddr *addr, struct uio *uio,
    struct mbuf *top, struct mbuf *control, int flags, struct thread *td)
{
	int error;

	CURVNET_SET(so->so_vnet);
	if (!SOLISTENING(so))
		error = so->so_proto->pr_usrreqs->pru_sosend(so, addr, uio,
		    top, control, flags, td);
	else {
		m_freem(top);
		m_freem(control);
		error = ENOTCONN;
	}
	CURVNET_RESTORE();
	return (error);
}