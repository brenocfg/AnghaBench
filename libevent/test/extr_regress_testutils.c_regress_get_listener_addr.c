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
struct evconnlistener {int dummy; } ;
typedef  scalar_t__ evutil_socket_t ;
typedef  int /*<<< orphan*/  ev_socklen_t ;

/* Variables and functions */
 scalar_t__ evconnlistener_get_fd (struct evconnlistener*) ; 
 int getsockname (scalar_t__,struct sockaddr*,int /*<<< orphan*/ *) ; 

int
regress_get_listener_addr(struct evconnlistener *lev,
    struct sockaddr *sa, ev_socklen_t *socklen)
{
	evutil_socket_t s = evconnlistener_get_fd(lev);
	if (s <= 0)
		return -1;
	return getsockname(s, sa, socklen);
}