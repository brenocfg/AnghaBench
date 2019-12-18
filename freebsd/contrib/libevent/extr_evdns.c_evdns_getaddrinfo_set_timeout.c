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
struct evdns_getaddrinfo_request {int /*<<< orphan*/  timeout; } ;
struct evdns_base {int /*<<< orphan*/  global_getaddrinfo_allow_skew; } ;

/* Variables and functions */
 int event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
evdns_getaddrinfo_set_timeout(struct evdns_base *evdns_base,
    struct evdns_getaddrinfo_request *data)
{
	return event_add(&data->timeout, &evdns_base->global_getaddrinfo_allow_skew);
}