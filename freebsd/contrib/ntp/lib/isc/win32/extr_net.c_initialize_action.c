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

/* Variables and functions */
 int /*<<< orphan*/  InitSockets () ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 void* ipv4_result ; 
 void* ipv6_result ; 
 void* try_proto (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
initialize_action(void) {
	InitSockets();
	ipv4_result = try_proto(PF_INET);
#ifdef ISC_PLATFORM_HAVEIPV6
#ifdef WANT_IPV6
#ifdef ISC_PLATFORM_HAVEIN6PKTINFO
	ipv6_result = try_proto(PF_INET6);
#endif
#endif
#endif
}