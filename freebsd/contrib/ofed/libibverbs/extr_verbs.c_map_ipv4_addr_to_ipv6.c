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
struct in6_addr {scalar_t__* s6_addr32; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ htobe32 (int) ; 

__attribute__((used)) static inline void map_ipv4_addr_to_ipv6(__be32 ipv4, struct in6_addr *ipv6)
{
	ipv6->s6_addr32[0] = 0;
	ipv6->s6_addr32[1] = 0;
	ipv6->s6_addr32[2] = htobe32(0x0000FFFF);
	ipv6->s6_addr32[3] = ipv4;
}