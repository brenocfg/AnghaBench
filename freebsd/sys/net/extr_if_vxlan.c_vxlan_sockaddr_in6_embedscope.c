#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
union vxlan_sockaddr {int /*<<< orphan*/  in6; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VXLAN_SOCKADDR_IS_IPV6 (union vxlan_sockaddr*) ; 
 int /*<<< orphan*/  V_ip6_use_defzone ; 
 int sa6_embedscope (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vxlan_sockaddr_in6_embedscope(union vxlan_sockaddr *vxladdr)
{
	int error;

	MPASS(VXLAN_SOCKADDR_IS_IPV6(vxladdr));
#ifdef INET6
	error = sa6_embedscope(&vxladdr->in6, V_ip6_use_defzone);
#else
	error = EAFNOSUPPORT;
#endif

	return (error);
}