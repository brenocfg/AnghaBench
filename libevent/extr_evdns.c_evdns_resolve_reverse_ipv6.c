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
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  evdns_callback_type ;

/* Variables and functions */
 int /*<<< orphan*/  current_base ; 
 scalar_t__ evdns_base_resolve_reverse_ipv6 (int /*<<< orphan*/ ,struct in6_addr const*,int,int /*<<< orphan*/ ,void*) ; 

int evdns_resolve_reverse_ipv6(const struct in6_addr *in, int flags, evdns_callback_type callback, void *ptr) {
	return evdns_base_resolve_reverse_ipv6(current_base, in, flags, callback, ptr)
		? 0 : -1;
}