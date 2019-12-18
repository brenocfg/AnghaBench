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
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {void* sin6_port; } ;
struct sockaddr_in {void* sin_port; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  void* in_port_t ;

/* Variables and functions */
 scalar_t__ addr_is_ip6 (struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

void
sockaddr_store_port(struct sockaddr_storage* addr, socklen_t addrlen, int port)
{
	if(addr_is_ip6(addr, addrlen)) {
		struct sockaddr_in6* sa = (struct sockaddr_in6*)addr;
		sa->sin6_port = (in_port_t)htons((uint16_t)port);
	} else {
		struct sockaddr_in* sa = (struct sockaddr_in*)addr;
		sa->sin_port = (in_port_t)htons((uint16_t)port);
	}
}