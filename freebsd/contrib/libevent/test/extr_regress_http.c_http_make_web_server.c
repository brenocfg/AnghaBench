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
struct http_server {scalar_t__ ssl; int /*<<< orphan*/  port; int /*<<< orphan*/  http; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_BIND_SSL ; 
 int /*<<< orphan*/  http_make_web_server_base ; 
 int /*<<< orphan*/  http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
http_make_web_server(evutil_socket_t fd, short what, void *arg)
{
	struct http_server *hs = (struct http_server *)arg;
	hs->http = http_setup(&hs->port, http_make_web_server_base, hs->ssl ? HTTP_BIND_SSL : 0);
}