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
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin_addr; } ;
union vxlan_sockaddr {TYPE_2__ in6; TYPE_1__ in4; } ;
struct vxlan_socket {int /*<<< orphan*/  vxlso_sock; } ;
struct sockopt {int sopt_valsize; struct ipv6_mreq* sopt_val; int /*<<< orphan*/  sopt_name; int /*<<< orphan*/  sopt_level; void* sopt_dir; } ;
struct ipv6_mreq {int ipv6mr_interface; int /*<<< orphan*/  ipv6mr_multiaddr; int /*<<< orphan*/  imr_interface; int /*<<< orphan*/  imr_multiaddr; } ;
struct ip_mreq {int ipv6mr_interface; int /*<<< orphan*/  ipv6mr_multiaddr; int /*<<< orphan*/  imr_interface; int /*<<< orphan*/  imr_multiaddr; } ;
typedef  int /*<<< orphan*/  sopt ;
typedef  int /*<<< orphan*/  mreq ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_JOIN_GROUP ; 
 int /*<<< orphan*/  IP_ADD_MEMBERSHIP ; 
 void* SOPT_SET ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV4 (union vxlan_sockaddr const*) ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV6 (union vxlan_sockaddr const*) ; 
 int /*<<< orphan*/  bzero (struct sockopt*,int) ; 
 int sosetopt (int /*<<< orphan*/ ,struct sockopt*) ; 

__attribute__((used)) static int
vxlan_socket_mc_join_group(struct vxlan_socket *vso,
    const union vxlan_sockaddr *group, const union vxlan_sockaddr *local,
    int *ifidx, union vxlan_sockaddr *source)
{
	struct sockopt sopt;
	int error;

	*source = *local;

	if (VXLAN_SOCKADDR_IS_IPV4(group)) {
		struct ip_mreq mreq;

		mreq.imr_multiaddr = group->in4.sin_addr;
		mreq.imr_interface = local->in4.sin_addr;

		bzero(&sopt, sizeof(sopt));
		sopt.sopt_dir = SOPT_SET;
		sopt.sopt_level = IPPROTO_IP;
		sopt.sopt_name = IP_ADD_MEMBERSHIP;
		sopt.sopt_val = &mreq;
		sopt.sopt_valsize = sizeof(mreq);
		error = sosetopt(vso->vxlso_sock, &sopt);
		if (error)
			return (error);

		/*
		 * BMV: Ideally, there would be a formal way for us to get
		 * the local interface that was selected based on the
		 * imr_interface address. We could then update *ifidx so
		 * vxlan_sockaddr_mc_info_match() would return a match for
		 * later creates that explicitly set the multicast interface.
		 *
		 * If we really need to, we can of course look in the INP's
		 * membership list:
		 *     sotoinpcb(vso->vxlso_sock)->inp_moptions->
		 *         imo_head[]->imf_inm->inm_ifp
		 * similarly to imo_match_group().
		 */
		source->in4.sin_addr = local->in4.sin_addr;

	} else if (VXLAN_SOCKADDR_IS_IPV6(group)) {
		struct ipv6_mreq mreq;

		mreq.ipv6mr_multiaddr = group->in6.sin6_addr;
		mreq.ipv6mr_interface = *ifidx;

		bzero(&sopt, sizeof(sopt));
		sopt.sopt_dir = SOPT_SET;
		sopt.sopt_level = IPPROTO_IPV6;
		sopt.sopt_name = IPV6_JOIN_GROUP;
		sopt.sopt_val = &mreq;
		sopt.sopt_valsize = sizeof(mreq);
		error = sosetopt(vso->vxlso_sock, &sopt);
		if (error)
			return (error);

		/*
		 * BMV: As with IPv4, we would really like to know what
		 * interface in6p_lookup_mcast_ifp() selected.
		 */
	} else
		error = EAFNOSUPPORT;

	return (error);
}