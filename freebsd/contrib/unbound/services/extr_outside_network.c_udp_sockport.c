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
struct ub_randstate {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {scalar_t__ sin6_scope_id; scalar_t__ sin6_flowinfo; void* sin6_port; } ;
struct sockaddr_in {void* sin_port; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  void* in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ addr_is_ip6 (struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int create_udp_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sai6_putrandom (struct sockaddr_in6*,int,struct ub_randstate*) ; 

__attribute__((used)) static int
udp_sockport(struct sockaddr_storage* addr, socklen_t addrlen, int pfxlen,
	int port, int* inuse, struct ub_randstate* rnd)
{
	int fd, noproto;
	if(addr_is_ip6(addr, addrlen)) {
		int freebind = 0;
		struct sockaddr_in6 sa = *(struct sockaddr_in6*)addr;
		sa.sin6_port = (in_port_t)htons((uint16_t)port);
		sa.sin6_flowinfo = 0;
		sa.sin6_scope_id = 0;
		if(pfxlen != 0) {
			freebind = 1;
			sai6_putrandom(&sa, pfxlen, rnd);
		}
		fd = create_udp_sock(AF_INET6, SOCK_DGRAM, 
			(struct sockaddr*)&sa, addrlen, 1, inuse, &noproto,
			0, 0, 0, NULL, 0, freebind, 0);
	} else {
		struct sockaddr_in* sa = (struct sockaddr_in*)addr;
		sa->sin_port = (in_port_t)htons((uint16_t)port);
		fd = create_udp_sock(AF_INET, SOCK_DGRAM, 
			(struct sockaddr*)addr, addrlen, 1, inuse, &noproto,
			0, 0, 0, NULL, 0, 0, 0);
	}
	return fd;
}