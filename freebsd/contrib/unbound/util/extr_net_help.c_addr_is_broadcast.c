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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; scalar_t__ sin_family; } ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 int AF_INET ; 
 scalar_t__ memcmp (void*,char*,int) ; 

int addr_is_broadcast(struct sockaddr_storage* addr, socklen_t addrlen)
{
	int af = (int)((struct sockaddr_in*)addr)->sin_family;
	void* sinaddr = &((struct sockaddr_in*)addr)->sin_addr;
	return af == AF_INET && addrlen>=(socklen_t)sizeof(struct sockaddr_in)
		&& memcmp(sinaddr, "\377\377\377\377", 4) == 0;
}