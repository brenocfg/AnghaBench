#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {TYPE_1__ sin_addr; } ;
union vxlan_sockaddr {TYPE_3__ in6; TYPE_2__ in4; } ;
struct vxlan_socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV4 (union vxlan_sockaddr*) ; 
 int /*<<< orphan*/  in6addr_any ; 
 struct vxlan_socket* vxlan_socket_lookup (union vxlan_sockaddr*) ; 

__attribute__((used)) static struct vxlan_socket *
vxlan_socket_mc_lookup(const union vxlan_sockaddr *vxlsa)
{
	union vxlan_sockaddr laddr;
	struct vxlan_socket *vso;

	laddr = *vxlsa;

	if (VXLAN_SOCKADDR_IS_IPV4(&laddr))
		laddr.in4.sin_addr.s_addr = INADDR_ANY;
#ifdef INET6
	else
		laddr.in6.sin6_addr = in6addr_any;
#endif

	vso = vxlan_socket_lookup(&laddr);

	return (vso);
}