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
struct sockaddr {scalar_t__ sa_family; } ;
union vxlan_sockaddr {struct sockaddr sa; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 

__attribute__((used)) static int
vxlan_sockaddr_supported(const union vxlan_sockaddr *vxladdr, int unspec)
{
	const struct sockaddr *sa;
	int supported;

	sa = &vxladdr->sa;
	supported = 0;

	if (sa->sa_family == AF_UNSPEC && unspec != 0) {
		supported = 1;
	} else if (sa->sa_family == AF_INET) {
#ifdef INET
		supported = 1;
#endif
	} else if (sa->sa_family == AF_INET6) {
#ifdef INET6
		supported = 1;
#endif
	}

	return (supported);
}