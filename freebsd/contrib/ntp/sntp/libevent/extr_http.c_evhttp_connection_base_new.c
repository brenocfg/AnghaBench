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
struct evhttp_connection {int dummy; } ;
struct event_base {int dummy; } ;
struct evdns_base {int dummy; } ;

/* Variables and functions */
 struct evhttp_connection* evhttp_connection_base_bufferevent_new (struct event_base*,struct evdns_base*,int /*<<< orphan*/ *,char const*,unsigned short) ; 

struct evhttp_connection *
evhttp_connection_base_new(struct event_base *base, struct evdns_base *dnsbase,
    const char *address, unsigned short port)
{
	return evhttp_connection_base_bufferevent_new(base, dnsbase, NULL, address, port);
}