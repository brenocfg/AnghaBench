#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bufferevent {int /*<<< orphan*/  ev_read; } ;
struct TYPE_2__ {struct bufferevent bev; } ;
struct bufferevent_openssl {TYPE_1__ bev; int /*<<< orphan*/  underlying; } ;
typedef  scalar_t__ evutil_socket_t ;

/* Variables and functions */
 scalar_t__ event_get_fd (int /*<<< orphan*/ *) ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 

__attribute__((used)) static evutil_socket_t
be_openssl_auto_fd(struct bufferevent_openssl *bev_ssl, evutil_socket_t fd)
{
	if (!bev_ssl->underlying) {
		struct bufferevent *bev = &bev_ssl->bev.bev;
		if (event_initialized(&bev->ev_read) && fd < 0) {
			fd = event_get_fd(&bev->ev_read);
		}
	}
	return fd;
}