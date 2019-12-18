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
typedef  scalar_t__ evdns_getaddrinfo_fn ;

/* Variables and functions */
 scalar_t__ evdns_getaddrinfo_impl ; 

void
evutil_set_evdns_getaddrinfo_fn_(evdns_getaddrinfo_fn fn)
{
	if (!evdns_getaddrinfo_impl)
		evdns_getaddrinfo_impl = fn;
}