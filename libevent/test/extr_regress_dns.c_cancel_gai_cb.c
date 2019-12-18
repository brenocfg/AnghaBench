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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  evdns_getaddrinfo_cancel (struct evdns_getaddrinfo_request*) ; 

__attribute__((used)) static void
cancel_gai_cb(evutil_socket_t fd, short what, void *ptr)
{
	struct evdns_getaddrinfo_request *r = ptr;
	evdns_getaddrinfo_cancel(r);
}