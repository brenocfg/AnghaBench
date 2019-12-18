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
struct evutil_addrinfo {int ai_family; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_protocol; } ;
struct evdns_base {int dummy; } ;
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  hint ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int bufferevent_socket_connect_hostname_hints (struct bufferevent*,struct evdns_base*,struct evutil_addrinfo*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct evutil_addrinfo*,int /*<<< orphan*/ ,int) ; 

int
bufferevent_socket_connect_hostname(struct bufferevent *bev,
    struct evdns_base *evdns_base, int family, const char *hostname, int port)
{
	struct evutil_addrinfo hint;
	memset(&hint, 0, sizeof(hint));
	hint.ai_family = family;
	hint.ai_protocol = IPPROTO_TCP;
	hint.ai_socktype = SOCK_STREAM;

	return bufferevent_socket_connect_hostname_hints(bev, evdns_base, &hint, hostname, port);
}