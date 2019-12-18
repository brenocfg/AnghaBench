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
typedef  int u_int ;
struct sockaddr_un {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_LOCAL 128 
 scalar_t__ RPC_MAXADDRSIZE ; 

u_int
__rpc_get_a_size(int af)
{
	switch (af) {
	case AF_INET:
		return sizeof (struct sockaddr_in);
#ifdef INET6
	case AF_INET6:
		return sizeof (struct sockaddr_in6);
#endif
	case AF_LOCAL:
		return sizeof (struct sockaddr_un);
	default:
		break;
	}
	return ((u_int)RPC_MAXADDRSIZE);
}