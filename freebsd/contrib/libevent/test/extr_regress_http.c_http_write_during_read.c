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
struct timeval {int tv_sec; } ;
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  bufferevent_write (struct bufferevent*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  exit_base ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
http_write_during_read(evutil_socket_t fd, short what, void *arg)
{
	struct bufferevent *bev = arg;
	struct timeval tv;

	bufferevent_write(bev, "foobar", strlen("foobar"));

	evutil_timerclear(&tv);
	tv.tv_sec = 1;
	event_base_loopexit(exit_base, &tv);
}