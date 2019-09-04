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
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  freeaddrinfo_stub ; 
 int /*<<< orphan*/  getaddrinfo_stub ; 
 int /*<<< orphan*/  getnameinfo_stub ; 
 int /*<<< orphan*/ * ipv6_dll ; 
 int /*<<< orphan*/  ipv6_freeaddrinfo ; 
 int /*<<< orphan*/  ipv6_getaddrinfo ; 
 int /*<<< orphan*/  ipv6_getnameinfo ; 

__attribute__((used)) static void socket_cleanup(void)
{
	WSACleanup();
	if (ipv6_dll)
		FreeLibrary(ipv6_dll);
	ipv6_dll = NULL;
	ipv6_freeaddrinfo = freeaddrinfo_stub;
	ipv6_getaddrinfo = getaddrinfo_stub;
	ipv6_getnameinfo = getnameinfo_stub;
}