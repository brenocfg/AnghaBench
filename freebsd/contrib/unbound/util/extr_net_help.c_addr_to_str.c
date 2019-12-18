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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; scalar_t__ sin_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ addr_is_ip6 (struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 scalar_t__ inet_ntop (int,void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*) ; 

void 
addr_to_str(struct sockaddr_storage* addr, socklen_t addrlen, 
	char* buf, size_t len)
{
	int af = (int)((struct sockaddr_in*)addr)->sin_family;
	void* sinaddr = &((struct sockaddr_in*)addr)->sin_addr;
	if(addr_is_ip6(addr, addrlen))
		sinaddr = &((struct sockaddr_in6*)addr)->sin6_addr;
	if(inet_ntop(af, sinaddr, buf, (socklen_t)len) == 0) {
		snprintf(buf, len, "(inet_ntop_error)");
	}
}