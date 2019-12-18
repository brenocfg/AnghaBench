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
struct bufferevent_openssl {scalar_t__ underlying; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_DEL_GENERIC_READ_TIMEOUT (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_DEL_GENERIC_WRITE_TIMEOUT (struct bufferevent*) ; 
 short EV_READ ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  stop_reading (struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  stop_writing (struct bufferevent_openssl*) ; 
 struct bufferevent_openssl* upcast (struct bufferevent*) ; 

__attribute__((used)) static int
be_openssl_disable(struct bufferevent *bev, short events)
{
	struct bufferevent_openssl *bev_ssl = upcast(bev);

	if (events & EV_READ)
		stop_reading(bev_ssl);
	if (events & EV_WRITE)
		stop_writing(bev_ssl);

	if (bev_ssl->underlying) {
		if (events & EV_READ)
			BEV_DEL_GENERIC_READ_TIMEOUT(bev);
		if (events & EV_WRITE)
			BEV_DEL_GENERIC_WRITE_TIMEOUT(bev);
	}
	return 0;
}