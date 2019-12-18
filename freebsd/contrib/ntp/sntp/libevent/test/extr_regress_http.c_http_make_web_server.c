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
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  http ; 
 int /*<<< orphan*/  http_make_web_server_base ; 
 int /*<<< orphan*/  http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
http_make_web_server(evutil_socket_t fd, short what, void *arg)
{
	ev_uint16_t port = *(ev_uint16_t*)arg;
	http = http_setup(&port, http_make_web_server_base, 0);
}