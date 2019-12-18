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
struct evutil_addrinfo {int /*<<< orphan*/ * ai_canonname; } ;
struct evdns_getaddrinfo_request {int /*<<< orphan*/ * cname_result; } ;

/* Variables and functions */

__attribute__((used)) static void
add_cname_to_reply(struct evdns_getaddrinfo_request *data,
    struct evutil_addrinfo *ai)
{
	if (data->cname_result && ai) {
		ai->ai_canonname = data->cname_result;
		data->cname_result = NULL;
	}
}