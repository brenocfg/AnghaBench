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
struct bufferevent_openssl {int allow_dirty_shutdown; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 struct bufferevent_openssl* upcast (struct bufferevent*) ; 

void
bufferevent_openssl_set_allow_dirty_shutdown(struct bufferevent *bev,
    int allow_dirty_shutdown)
{
	struct bufferevent_openssl *bev_ssl;
	BEV_LOCK(bev);
	bev_ssl = upcast(bev);
	if (bev_ssl)
		bev_ssl->allow_dirty_shutdown = !!allow_dirty_shutdown;
	BEV_UNLOCK(bev);
}