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
struct evdns_getaddrinfo_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evdns_getaddrinfo_cancel_impl (struct evdns_getaddrinfo_request*) ; 

void evutil_getaddrinfo_cancel_async_(struct evdns_getaddrinfo_request *data)
{
	if (evdns_getaddrinfo_cancel_impl && data) {
		evdns_getaddrinfo_cancel_impl(data);
	}
}