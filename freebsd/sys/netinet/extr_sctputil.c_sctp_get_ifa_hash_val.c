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
typedef  int uint32_t ;
struct TYPE_3__ {int* s6_addr32; } ;
struct sockaddr_in6 {TYPE_1__ sin6_addr; } ;
struct TYPE_4__ {int s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 

uint32_t
sctp_get_ifa_hash_val(struct sockaddr *addr)
{
	switch (addr->sa_family) {
#ifdef INET
	case AF_INET:
		{
			struct sockaddr_in *sin;

			sin = (struct sockaddr_in *)addr;
			return (sin->sin_addr.s_addr ^ (sin->sin_addr.s_addr >> 16));
		}
#endif
#ifdef INET6
	case AF_INET6:
		{
			struct sockaddr_in6 *sin6;
			uint32_t hash_of_addr;

			sin6 = (struct sockaddr_in6 *)addr;
			hash_of_addr = (sin6->sin6_addr.s6_addr32[0] +
			    sin6->sin6_addr.s6_addr32[1] +
			    sin6->sin6_addr.s6_addr32[2] +
			    sin6->sin6_addr.s6_addr32[3]);
			hash_of_addr = (hash_of_addr ^ (hash_of_addr >> 16));
			return (hash_of_addr);
		}
#endif
	default:
		break;
	}
	return (0);
}