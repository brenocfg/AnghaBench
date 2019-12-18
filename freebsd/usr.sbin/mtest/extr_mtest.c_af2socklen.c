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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;

/* Variables and functions */
 int const AF_INET ; 
 int const AF_INET6 ; 

__attribute__((used)) static __inline int
af2socklen(const int af)
{

#ifdef INET
	if (af == AF_INET)
		return (sizeof(struct sockaddr_in));
#endif
#ifdef INET6
	if (af == AF_INET6)
		return (sizeof(struct sockaddr_in6));
#endif
	return (-1);
}