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
 int bufferevent_generic_adj_existing_timeouts_ (struct bufferevent*) ; 
 int bufferevent_generic_adj_timeouts_ (struct bufferevent*) ; 
 struct bufferevent_openssl* upcast (struct bufferevent*) ; 

__attribute__((used)) static int
be_openssl_adj_timeouts(struct bufferevent *bev)
{
	struct bufferevent_openssl *bev_ssl = upcast(bev);

	if (bev_ssl->underlying) {
		return bufferevent_generic_adj_timeouts_(bev);
	} else {
		return bufferevent_generic_adj_existing_timeouts_(bev);
	}
}