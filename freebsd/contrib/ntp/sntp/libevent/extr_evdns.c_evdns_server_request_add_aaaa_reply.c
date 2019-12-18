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
struct evdns_server_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_INET ; 
 int /*<<< orphan*/  EVDNS_ANSWER_SECTION ; 
 int /*<<< orphan*/  TYPE_AAAA ; 
 int evdns_server_request_add_reply (struct evdns_server_request*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,void const*) ; 

int
evdns_server_request_add_aaaa_reply(struct evdns_server_request *req, const char *name, int n, const void *addrs, int ttl)
{
	return evdns_server_request_add_reply(
		  req, EVDNS_ANSWER_SECTION, name, TYPE_AAAA, CLASS_INET,
		  ttl, n*16, 0, addrs);
}