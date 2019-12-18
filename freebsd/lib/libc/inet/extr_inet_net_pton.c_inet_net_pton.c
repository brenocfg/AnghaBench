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
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  errno ; 
 int inet_net_pton_ipv4 (char const*,void*,size_t) ; 
 int inet_net_pton_ipv6 (char const*,void*,size_t) ; 

int
inet_net_pton(int af, const char *src, void *dst, size_t size) {
	switch (af) {
	case AF_INET:
		return (inet_net_pton_ipv4(src, dst, size));
	case AF_INET6:
		return (inet_net_pton_ipv6(src, dst, size));
	default:
		errno = EAFNOSUPPORT;
		return (-1);
	}
}