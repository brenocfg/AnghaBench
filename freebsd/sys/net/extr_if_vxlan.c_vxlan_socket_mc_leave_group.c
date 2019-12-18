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
struct sockopt {int sopt_valsize; struct ipv6_mreq* sopt_val; int /*<<< orphan*/  sopt_name; int /*<<< orphan*/  sopt_level; int /*<<< orphan*/  sopt_dir; } ;
struct ipv6_mreq {int ipv6mr_interface; int /*<<< orphan*/  ipv6mr_multiaddr; int /*<<< orphan*/  imr_interface; int /*<<< orphan*/  imr_multiaddr; } ;
struct ip_mreq {int ipv6mr_interface; int /*<<< orphan*/  ipv6mr_multiaddr; int /*<<< orphan*/  imr_interface; int /*<<< orphan*/  imr_multiaddr; } ;
typedef  int /*<<< orphan*/  sopt ;
typedef  int /*<<< orphan*/  mreq ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_LEAVE_GROUP ; 
 int /*<<< orphan*/  IP_DROP_MEMBERSHIP ; 
 int /*<<< orphan*/  SOPT_SET ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV4 (union vxlan_sockaddr const*) ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV6 (union vxlan_sockaddr const*) ; 
 int /*<<< orphan*/  bzero (struct sockopt*,int) ; 
 int sosetopt (int /*<<< orphan*/ ,struct sockopt*) ; 

__attribute__((used)) static int
vxlan_socket_mc_leave_group(struct vxlan_socket *vso,
    const union vxlan_sockaddr *group, const union vxlan_sockaddr *source,
    int ifidx)
{
	struct sockopt sopt;
	int error;

	bzero(&sopt, sizeof(sopt));
	sopt.sopt_dir = SOPT_SET;

	if (VXLAN_SOCKADDR_IS_IPV4(group)) {
		struct ip_mreq mreq;

		mreq.imr_multiaddr = group->in4.sin_addr;
		mreq.imr_interface = source->in4.sin_addr;

		sopt.sopt_level = IPPROTO_IP;
		sopt.sopt_name = IP_DROP_MEMBERSHIP;
		sopt.sopt_val = &mreq;
		sopt.sopt_valsize = sizeof(mreq);
		error = sosetopt(vso->vxlso_sock, &sopt);

	} else if (VXLAN_SOCKADDR_IS_IPV6(group)) {
		struct ipv6_mreq mreq;

		mreq.ipv6mr_multiaddr = group->in6.sin6_addr;
		mreq.ipv6mr_interface = ifidx;

		sopt.sopt_level = IPPROTO_IPV6;
		sopt.sopt_name = IPV6_LEAVE_GROUP;
		sopt.sopt_val = &mreq;
		sopt.sopt_valsize = sizeof(mreq);
		error = sosetopt(vso->vxlso_sock, &sopt);

	} else
		error = EAFNOSUPPORT;

	return (error);
}