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
struct evdns_getaddrinfo_request {int /*<<< orphan*/  timeout; struct evdns_getaddrinfo_request* cname_result; scalar_t__ pending_result; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_freeaddrinfo (scalar_t__) ; 
 int /*<<< orphan*/  mm_free (struct evdns_getaddrinfo_request*) ; 

__attribute__((used)) static void
free_getaddrinfo_request(struct evdns_getaddrinfo_request *data)
{
	/* DO NOT CALL this if either of the requests is pending.  Only once
	 * both callbacks have been invoked is it safe to free the request */
	if (data->pending_result)
		evutil_freeaddrinfo(data->pending_result);
	if (data->cname_result)
		mm_free(data->cname_result);
	event_del(&data->timeout);
	mm_free(data);
	return;
}