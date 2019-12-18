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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  be_connect_hostname_base ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int total_connected_or_failed ; 
 int total_n_accepted ; 

__attribute__((used)) static void
nil_accept_cb(struct evconnlistener *l, evutil_socket_t fd, struct sockaddr *s,
    int socklen, void *arg)
{
	int *p = arg;
	(*p)++;
	++total_n_accepted;
	/* don't do anything with the socket; let it close when we exit() */
	if (total_n_accepted >= 3 && total_connected_or_failed >= 5)
		event_base_loopexit(be_connect_hostname_base,
		    NULL);
}