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
struct sockopt {scalar_t__ sopt_level; scalar_t__ sopt_name; int sopt_dir; } ;
struct socket {int /*<<< orphan*/  so_fibnum; } ;
struct TYPE_2__ {int /*<<< orphan*/  inc_fibnum; } ;
struct inpcb {TYPE_1__ inp_inc; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 scalar_t__ IPPROTO_IPV6 ; 
#define  IPV6_CHECKSUM 137 
#define  MRT6_ADD_MFC 136 
#define  MRT6_ADD_MIF 135 
#define  MRT6_DEL_MFC 134 
#define  MRT6_DEL_MIF 133 
#define  MRT6_DONE 132 
#define  MRT6_INIT 131 
#define  MRT6_PIM 130 
 scalar_t__ SOL_SOCKET ; 
#define  SOPT_GET 129 
#define  SOPT_SET 128 
 scalar_t__ SO_SETFIB ; 
 int icmp6_ctloutput (struct socket*,struct sockopt*) ; 
 int ip6_ctloutput (struct socket*,struct sockopt*) ; 
 int ip6_mrouter_get (struct socket*,struct sockopt*) ; 
 int ip6_mrouter_set (struct socket*,struct sockopt*) ; 
 int ip6_raw_ctloutput (struct socket*,struct sockopt*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

int
rip6_ctloutput(struct socket *so, struct sockopt *sopt)
{
	struct inpcb *inp;
	int error;

	if (sopt->sopt_level == IPPROTO_ICMPV6)
		/*
		 * XXX: is it better to call icmp6_ctloutput() directly
		 * from protosw?
		 */
		return (icmp6_ctloutput(so, sopt));
	else if (sopt->sopt_level != IPPROTO_IPV6) {
		if (sopt->sopt_level == SOL_SOCKET &&
		    sopt->sopt_name == SO_SETFIB) {
			inp = sotoinpcb(so);
			INP_WLOCK(inp);
			inp->inp_inc.inc_fibnum = so->so_fibnum;
			INP_WUNLOCK(inp);
			return (0);
		}
		return (EINVAL);
	}

	error = 0;

	switch (sopt->sopt_dir) {
	case SOPT_GET:
		switch (sopt->sopt_name) {
		case MRT6_INIT:
		case MRT6_DONE:
		case MRT6_ADD_MIF:
		case MRT6_DEL_MIF:
		case MRT6_ADD_MFC:
		case MRT6_DEL_MFC:
		case MRT6_PIM:
			error = ip6_mrouter_get ?  ip6_mrouter_get(so, sopt) :
			    EOPNOTSUPP;
			break;
		case IPV6_CHECKSUM:
			error = ip6_raw_ctloutput(so, sopt);
			break;
		default:
			error = ip6_ctloutput(so, sopt);
			break;
		}
		break;

	case SOPT_SET:
		switch (sopt->sopt_name) {
		case MRT6_INIT:
		case MRT6_DONE:
		case MRT6_ADD_MIF:
		case MRT6_DEL_MIF:
		case MRT6_ADD_MFC:
		case MRT6_DEL_MFC:
		case MRT6_PIM:
			error = ip6_mrouter_set ?  ip6_mrouter_set(so, sopt) :
			    EOPNOTSUPP;
			break;
		case IPV6_CHECKSUM:
			error = ip6_raw_ctloutput(so, sopt);
			break;
		default:
			error = ip6_ctloutput(so, sopt);
			break;
		}
		break;
	}

	return (error);
}