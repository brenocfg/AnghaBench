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
struct sockaddr {int dummy; } ;
struct evhttp {int dummy; } ;
struct evconnlistener {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  evhttp_get_request (struct evhttp*,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

__attribute__((used)) static void
accept_socket_cb(struct evconnlistener *listener, evutil_socket_t nfd, struct sockaddr *peer_sa, int peer_socklen, void *arg)
{
	struct evhttp *http = arg;

	evhttp_get_request(http, nfd, peer_sa, peer_socklen);
}