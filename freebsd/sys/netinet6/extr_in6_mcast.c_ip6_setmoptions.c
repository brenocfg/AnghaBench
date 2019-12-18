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
typedef  int u_int ;
struct sockopt {int sopt_name; int sopt_valsize; } ;
struct ip6_moptions {int im6o_multicast_hlim; int im6o_multicast_loop; } ;
struct inpcb {TYPE_2__* inp_socket; } ;
typedef  int /*<<< orphan*/  hlim ;
struct TYPE_4__ {TYPE_1__* so_proto; } ;
struct TYPE_3__ {scalar_t__ pr_protocol; scalar_t__ pr_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INP_UNLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 scalar_t__ IPPROTO_DIVERT ; 
#define  IPV6_JOIN_GROUP 139 
#define  IPV6_LEAVE_GROUP 138 
#define  IPV6_MSFILTER 137 
#define  IPV6_MULTICAST_HOPS 136 
#define  IPV6_MULTICAST_IF 135 
#define  IPV6_MULTICAST_LOOP 134 
#define  MCAST_BLOCK_SOURCE 133 
#define  MCAST_JOIN_GROUP 132 
#define  MCAST_JOIN_SOURCE_GROUP 131 
#define  MCAST_LEAVE_GROUP 130 
#define  MCAST_LEAVE_SOURCE_GROUP 129 
#define  MCAST_UNBLOCK_SOURCE 128 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_RAW ; 
 int V_ip6_defmcasthlim ; 
 int in6p_block_unblock_source (struct inpcb*,struct sockopt*) ; 
 struct ip6_moptions* in6p_findmoptions (struct inpcb*) ; 
 int in6p_join_group (struct inpcb*,struct sockopt*) ; 
 int in6p_leave_group (struct inpcb*,struct sockopt*) ; 
 int in6p_set_multicast_if (struct inpcb*,struct sockopt*) ; 
 int in6p_set_source_filters (struct inpcb*,struct sockopt*) ; 
 int sooptcopyin (struct sockopt*,int*,int,int) ; 

int
ip6_setmoptions(struct inpcb *inp, struct sockopt *sopt)
{
	struct ip6_moptions	*im6o;
	int			 error;

	error = 0;

	/*
	 * If socket is neither of type SOCK_RAW or SOCK_DGRAM,
	 * or is a divert socket, reject it.
	 */
	if (inp->inp_socket->so_proto->pr_protocol == IPPROTO_DIVERT ||
	    (inp->inp_socket->so_proto->pr_type != SOCK_RAW &&
	     inp->inp_socket->so_proto->pr_type != SOCK_DGRAM))
		return (EOPNOTSUPP);

	switch (sopt->sopt_name) {
	case IPV6_MULTICAST_IF:
		error = in6p_set_multicast_if(inp, sopt);
		break;

	case IPV6_MULTICAST_HOPS: {
		int hlim;

		if (sopt->sopt_valsize != sizeof(int)) {
			error = EINVAL;
			break;
		}
		error = sooptcopyin(sopt, &hlim, sizeof(hlim), sizeof(int));
		if (error)
			break;
		if (hlim < -1 || hlim > 255) {
			error = EINVAL;
			break;
		} else if (hlim == -1) {
			hlim = V_ip6_defmcasthlim;
		}
		im6o = in6p_findmoptions(inp);
		im6o->im6o_multicast_hlim = hlim;
		INP_WUNLOCK(inp);
		break;
	}

	case IPV6_MULTICAST_LOOP: {
		u_int loop;

		/*
		 * Set the loopback flag for outgoing multicast packets.
		 * Must be zero or one.
		 */
		if (sopt->sopt_valsize != sizeof(u_int)) {
			error = EINVAL;
			break;
		}
		error = sooptcopyin(sopt, &loop, sizeof(u_int), sizeof(u_int));
		if (error)
			break;
		if (loop > 1) {
			error = EINVAL;
			break;
		}
		im6o = in6p_findmoptions(inp);
		im6o->im6o_multicast_loop = loop;
		INP_WUNLOCK(inp);
		break;
	}

	case IPV6_JOIN_GROUP:
	case MCAST_JOIN_GROUP:
	case MCAST_JOIN_SOURCE_GROUP:
		error = in6p_join_group(inp, sopt);
		break;

	case IPV6_LEAVE_GROUP:
	case MCAST_LEAVE_GROUP:
	case MCAST_LEAVE_SOURCE_GROUP:
		error = in6p_leave_group(inp, sopt);
		break;

	case MCAST_BLOCK_SOURCE:
	case MCAST_UNBLOCK_SOURCE:
		error = in6p_block_unblock_source(inp, sopt);
		break;

	case IPV6_MSFILTER:
		error = in6p_set_source_filters(inp, sopt);
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}

	INP_UNLOCK_ASSERT(inp);

	return (error);
}