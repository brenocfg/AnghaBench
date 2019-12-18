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
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  evconnlistener_disable (struct evconnlistener*) ; 
 int /*<<< orphan*/  evutil_closesocket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acceptcb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *addr, int socklen, void *arg)
{
	int *ptr = arg;
	--*ptr;
	TT_BLATHER(("Got one for %p", ptr));
	evutil_closesocket(fd);

	if (! *ptr)
		evconnlistener_disable(listener);
}