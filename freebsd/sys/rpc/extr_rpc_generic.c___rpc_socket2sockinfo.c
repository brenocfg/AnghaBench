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
struct sockopt {int* sopt_val; int sopt_valsize; int /*<<< orphan*/ * sopt_td; int /*<<< orphan*/  sopt_name; int /*<<< orphan*/  sopt_level; int /*<<< orphan*/  sopt_dir; } ;
struct socket {TYPE_2__* so_proto; int /*<<< orphan*/  so_vnet; } ;
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_len; } ;
struct __rpc_sockinfo {int si_proto; int si_socktype; scalar_t__ si_af; int /*<<< orphan*/  si_alen; } ;
typedef  scalar_t__ sa_family_t ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_sockaddr ) (struct socket*,struct sockaddr**) ;} ;

/* Variables and functions */
 scalar_t__ AF_LOCAL ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  M_SONAME ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOPT_GET ; 
 int /*<<< orphan*/  SO_TYPE ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int sogetopt (struct socket*,struct sockopt*) ; 
 int stub1 (struct socket*,struct sockaddr**) ; 

int
__rpc_socket2sockinfo(struct socket *so, struct __rpc_sockinfo *sip)
{
	int type, proto;
	struct sockaddr *sa;
	sa_family_t family;
	struct sockopt opt;
	int error;

	CURVNET_SET(so->so_vnet);
	error = so->so_proto->pr_usrreqs->pru_sockaddr(so, &sa);
	CURVNET_RESTORE();
	if (error)
		return 0;

	sip->si_alen = sa->sa_len;
	family = sa->sa_family;
	free(sa, M_SONAME);

	opt.sopt_dir = SOPT_GET;
	opt.sopt_level = SOL_SOCKET;
	opt.sopt_name = SO_TYPE;
	opt.sopt_val = &type;
	opt.sopt_valsize = sizeof type;
	opt.sopt_td = NULL;
	error = sogetopt(so, &opt);
	if (error)
		return 0;

	/* XXX */
	if (family != AF_LOCAL) {
		if (type == SOCK_STREAM)
			proto = IPPROTO_TCP;
		else if (type == SOCK_DGRAM)
			proto = IPPROTO_UDP;
		else
			return 0;
	} else
		proto = 0;

	sip->si_af = family;
	sip->si_proto = proto;
	sip->si_socktype = type;

	return 1;
}