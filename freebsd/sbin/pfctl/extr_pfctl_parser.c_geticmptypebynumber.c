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
typedef  scalar_t__ u_int8_t ;
struct icmptypeent {scalar_t__ type; } ;
typedef  scalar_t__ sa_family_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 struct icmptypeent const* icmp6_type ; 
 struct icmptypeent const* icmp_type ; 
 unsigned int nitems (struct icmptypeent const*) ; 

const struct icmptypeent *
geticmptypebynumber(u_int8_t type, sa_family_t af)
{
	unsigned int	i;

	if (af != AF_INET6) {
		for (i=0; i < nitems(icmp_type); i++) {
			if (type == icmp_type[i].type)
				return (&icmp_type[i]);
		}
	} else {
		for (i=0; i < nitems(icmp6_type); i++) {
			if (type == icmp6_type[i].type)
				 return (&icmp6_type[i]);
		}
	}
	return (NULL);
}