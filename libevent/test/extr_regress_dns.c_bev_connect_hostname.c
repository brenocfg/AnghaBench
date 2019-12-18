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
struct evutil_addrinfo {scalar_t__ ai_flags; } ;
struct evdns_base {int dummy; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int bufferevent_socket_connect_hostname (struct bufferevent*,struct evdns_base*,int /*<<< orphan*/ ,char const*,int) ; 
 int bufferevent_socket_connect_hostname_hints (struct bufferevent*,struct evdns_base*,struct evutil_addrinfo*,char const*,int) ; 

__attribute__((used)) static int bev_connect_hostname(struct bufferevent *bev, struct evdns_base *dns,
    struct evutil_addrinfo *hints, const char *host, int port)
{
	if (hints->ai_flags)
		return bufferevent_socket_connect_hostname_hints(bev, dns, hints, host, port);
	else
		return bufferevent_socket_connect_hostname(bev, dns, AF_INET, host, port);
}