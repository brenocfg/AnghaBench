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
struct icmptypeent {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ sa_family_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 struct icmptypeent const* icmp6_type ; 
 struct icmptypeent const* icmp_type ; 
 unsigned int nitems (struct icmptypeent const*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

const struct icmptypeent *
geticmptypebyname(char *w, sa_family_t af)
{
	unsigned int	i;

	if (af != AF_INET6) {
		for (i=0; i < nitems(icmp_type); i++) {
			if (!strcmp(w, icmp_type[i].name))
				return (&icmp_type[i]);
		}
	} else {
		for (i=0; i < nitems(icmp6_type); i++) {
			if (!strcmp(w, icmp6_type[i].name))
				return (&icmp6_type[i]);
		}
	}
	return (NULL);
}