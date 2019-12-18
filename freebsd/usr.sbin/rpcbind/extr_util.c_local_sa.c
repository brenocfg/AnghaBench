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
struct sockaddr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ local_in4 ; 
 scalar_t__ local_in6 ; 

struct sockaddr *
local_sa(int af)
{
	switch (af) {
	case AF_INET:
		return (struct sockaddr *)local_in4;
#ifdef INET6
	case AF_INET6:
		return (struct sockaddr *)local_in6;
#endif
	default:
		return NULL;
	}
}