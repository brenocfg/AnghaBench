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
struct socket {TYPE_2__* so_proto; int /*<<< orphan*/  so_vnet; } ;
struct sockaddr_un {char* sun_path; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_sockaddr ) (struct socket*,struct sockaddr**) ;} ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_LOCAL 128 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int stub1 (struct socket*,struct sockaddr**) ; 

int
__rpc_sockisbound(struct socket *so)
{
	struct sockaddr *sa;
	int error, bound;

	CURVNET_SET(so->so_vnet);
	error = so->so_proto->pr_usrreqs->pru_sockaddr(so, &sa);
	CURVNET_RESTORE();
	if (error)
		return (0);

	switch (sa->sa_family) {
		case AF_INET:
			bound = (((struct sockaddr_in *) sa)->sin_port != 0);
			break;
#ifdef INET6
		case AF_INET6:
			bound = (((struct sockaddr_in6 *) sa)->sin6_port != 0);
			break;
#endif
		case AF_LOCAL:
			/* XXX check this */
			bound = (((struct sockaddr_un *) sa)->sun_path[0] != '\0');
			break;
		default:
			bound = FALSE;
			break;
	}

	free(sa, M_SONAME);

	return bound;
}