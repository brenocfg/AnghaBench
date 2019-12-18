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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; } ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 

int
addr_is_ip6(struct sockaddr_storage* addr, socklen_t len)
{
	if(len == (socklen_t)sizeof(struct sockaddr_in6) &&
		((struct sockaddr_in6*)addr)->sin6_family == AF_INET6)
		return 1;
	else    return 0;
}