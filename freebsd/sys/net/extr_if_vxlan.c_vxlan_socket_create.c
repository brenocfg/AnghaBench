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
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {TYPE_2__ sin_addr; } ;
union vxlan_sockaddr {TYPE_1__ in6; TYPE_3__ in4; } ;
struct vxlan_socket {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV4 (union vxlan_sockaddr*) ; 
 int /*<<< orphan*/  in6addr_any ; 
 struct vxlan_socket* vxlan_socket_alloc (union vxlan_sockaddr*) ; 
 int vxlan_socket_bind (struct vxlan_socket*,struct ifnet*) ; 
 int /*<<< orphan*/  vxlan_socket_destroy (struct vxlan_socket*) ; 
 int vxlan_socket_init (struct vxlan_socket*,struct ifnet*) ; 
 int /*<<< orphan*/  vxlan_socket_insert (struct vxlan_socket*) ; 

__attribute__((used)) static int
vxlan_socket_create(struct ifnet *ifp, int multicast,
    const union vxlan_sockaddr *saddr, struct vxlan_socket **vsop)
{
	union vxlan_sockaddr laddr;
	struct vxlan_socket *vso;
	int error;

	laddr = *saddr;

	/*
	 * If this socket will be multicast, then only the local port
	 * must be specified when binding.
	 */
	if (multicast != 0) {
		if (VXLAN_SOCKADDR_IS_IPV4(&laddr))
			laddr.in4.sin_addr.s_addr = INADDR_ANY;
#ifdef INET6
		else
			laddr.in6.sin6_addr = in6addr_any;
#endif
	}

	vso = vxlan_socket_alloc(&laddr);
	if (vso == NULL)
		return (ENOMEM);

	error = vxlan_socket_init(vso, ifp);
	if (error)
		goto fail;

	error = vxlan_socket_bind(vso, ifp);
	if (error)
		goto fail;

	/*
	 * There is a small window between the bind completing and
	 * inserting the socket, so that a concurrent create may fail.
	 * Let's not worry about that for now.
	 */
	vxlan_socket_insert(vso);
	*vsop = vso;

	return (0);

fail:
	vxlan_socket_destroy(vso);

	return (error);
}