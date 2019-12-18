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
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_getfd (struct bufferevent*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_free(struct bufferevent **bevp)
{
	evutil_socket_t fd;
	struct bufferevent *bev = *bevp;

	if (!bev)
		return;

	fd = bufferevent_getfd(bev);
	info("Freeing bufferevent with fd=%d\n", fd);

	bufferevent_free(bev);
	*bevp = NULL;
}