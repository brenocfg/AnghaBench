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
struct icmpcodeent {scalar_t__ type; scalar_t__ code; } ;
typedef  scalar_t__ sa_family_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 struct icmpcodeent const* icmp6_code ; 
 struct icmpcodeent const* icmp_code ; 
 unsigned int nitems (struct icmpcodeent const*) ; 

const struct icmpcodeent *
geticmpcodebynumber(u_int8_t type, u_int8_t code, sa_family_t af)
{
	unsigned int	i;

	if (af != AF_INET6) {
		for (i=0; i < nitems(icmp_code); i++) {
			if (type == icmp_code[i].type &&
			    code == icmp_code[i].code)
				return (&icmp_code[i]);
		}
	} else {
		for (i=0; i < nitems(icmp6_code); i++) {
			if (type == icmp6_code[i].type &&
			    code == icmp6_code[i].code)
				return (&icmp6_code[i]);
		}
	}
	return (NULL);
}