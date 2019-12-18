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
 int /*<<< orphan*/  bufferevent_write (struct bufferevent*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
http_complete_write(evutil_socket_t fd, short what, void *arg)
{
	struct bufferevent *bev = arg;
	const char *http_request = "host\r\n"
	    "Connection: close\r\n"
	    "\r\n";
	bufferevent_write(bev, http_request, strlen(http_request));
}