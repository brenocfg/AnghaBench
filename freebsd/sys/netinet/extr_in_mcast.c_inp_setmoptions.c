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
typedef  int u_char ;
struct sockopt {int sopt_name; int sopt_valsize; } ;
struct ip_moptions {int imo_multicast_vif; int imo_multicast_ttl; int imo_multicast_loop; } ;
struct inpcb {TYPE_2__* inp_socket; } ;
struct TYPE_4__ {TYPE_1__* so_proto; } ;
struct TYPE_3__ {scalar_t__ pr_protocol; scalar_t__ pr_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INP_UNLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 scalar_t__ IPPROTO_DIVERT ; 
#define  IP_ADD_MEMBERSHIP 144 
#define  IP_ADD_SOURCE_MEMBERSHIP 143 
#define  IP_BLOCK_SOURCE 142 
#define  IP_DROP_MEMBERSHIP 141 
#define  IP_DROP_SOURCE_MEMBERSHIP 140 
#define  IP_MSFILTER 139 
#define  IP_MULTICAST_IF 138 
#define  IP_MULTICAST_LOOP 137 
#define  IP_MULTICAST_TTL 136 
#define  IP_MULTICAST_VIF 135 
#define  IP_UNBLOCK_SOURCE 134 
#define  MCAST_BLOCK_SOURCE 133 
#define  MCAST_JOIN_GROUP 132 
#define  MCAST_JOIN_SOURCE_GROUP 131 
#define  MCAST_LEAVE_GROUP 130 
#define  MCAST_LEAVE_SOURCE_GROUP 129 
#define  MCAST_UNBLOCK_SOURCE 128 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_RAW ; 
 int inp_block_unblock_source (struct inpcb*,struct sockopt*) ; 
 struct ip_moptions* inp_findmoptions (struct inpcb*) ; 
 int inp_join_group (struct inpcb*,struct sockopt*) ; 
 int inp_leave_group (struct inpcb*,struct sockopt*) ; 
 int inp_set_multicast_if (struct inpcb*,struct sockopt*) ; 
 int inp_set_source_filters (struct inpcb*,struct sockopt*) ; 
 int /*<<< orphan*/  legal_vif_num (int) ; 
 int sooptcopyin (struct sockopt*,int*,int,int) ; 

int
inp_setmoptions(struct inpcb *inp, struct sockopt *sopt)
{
	struct ip_moptions	*imo;
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
	case IP_MULTICAST_VIF: {
		int vifi;
		/*
		 * Select a multicast VIF for transmission.
		 * Only useful if multicast forwarding is active.
		 */
		if (legal_vif_num == NULL) {
			error = EOPNOTSUPP;
			break;
		}
		error = sooptcopyin(sopt, &vifi, sizeof(int), sizeof(int));
		if (error)
			break;
		if (!legal_vif_num(vifi) && (vifi != -1)) {
			error = EINVAL;
			break;
		}
		imo = inp_findmoptions(inp);
		imo->imo_multicast_vif = vifi;
		INP_WUNLOCK(inp);
		break;
	}

	case IP_MULTICAST_IF:
		error = inp_set_multicast_if(inp, sopt);
		break;

	case IP_MULTICAST_TTL: {
		u_char ttl;

		/*
		 * Set the IP time-to-live for outgoing multicast packets.
		 * The original multicast API required a char argument,
		 * which is inconsistent with the rest of the socket API.
		 * We allow either a char or an int.
		 */
		if (sopt->sopt_valsize == sizeof(u_char)) {
			error = sooptcopyin(sopt, &ttl, sizeof(u_char),
			    sizeof(u_char));
			if (error)
				break;
		} else {
			u_int ittl;

			error = sooptcopyin(sopt, &ittl, sizeof(u_int),
			    sizeof(u_int));
			if (error)
				break;
			if (ittl > 255) {
				error = EINVAL;
				break;
			}
			ttl = (u_char)ittl;
		}
		imo = inp_findmoptions(inp);
		imo->imo_multicast_ttl = ttl;
		INP_WUNLOCK(inp);
		break;
	}

	case IP_MULTICAST_LOOP: {
		u_char loop;

		/*
		 * Set the loopback flag for outgoing multicast packets.
		 * Must be zero or one.  The original multicast API required a
		 * char argument, which is inconsistent with the rest
		 * of the socket API.  We allow either a char or an int.
		 */
		if (sopt->sopt_valsize == sizeof(u_char)) {
			error = sooptcopyin(sopt, &loop, sizeof(u_char),
			    sizeof(u_char));
			if (error)
				break;
		} else {
			u_int iloop;

			error = sooptcopyin(sopt, &iloop, sizeof(u_int),
					    sizeof(u_int));
			if (error)
				break;
			loop = (u_char)iloop;
		}
		imo = inp_findmoptions(inp);
		imo->imo_multicast_loop = !!loop;
		INP_WUNLOCK(inp);
		break;
	}

	case IP_ADD_MEMBERSHIP:
	case IP_ADD_SOURCE_MEMBERSHIP:
	case MCAST_JOIN_GROUP:
	case MCAST_JOIN_SOURCE_GROUP:
		error = inp_join_group(inp, sopt);
		break;

	case IP_DROP_MEMBERSHIP:
	case IP_DROP_SOURCE_MEMBERSHIP:
	case MCAST_LEAVE_GROUP:
	case MCAST_LEAVE_SOURCE_GROUP:
		error = inp_leave_group(inp, sopt);
		break;

	case IP_BLOCK_SOURCE:
	case IP_UNBLOCK_SOURCE:
	case MCAST_BLOCK_SOURCE:
	case MCAST_UNBLOCK_SOURCE:
		error = inp_block_unblock_source(inp, sopt);
		break;

	case IP_MSFILTER:
		error = inp_set_source_filters(inp, sopt);
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}

	INP_UNLOCK_ASSERT(inp);

	return (error);
}