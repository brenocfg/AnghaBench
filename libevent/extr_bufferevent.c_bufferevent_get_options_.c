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
struct bufferevent_private {int options; } ;
struct bufferevent {int dummy; } ;
typedef  enum bufferevent_options { ____Placeholder_bufferevent_options } bufferevent_options ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 

enum bufferevent_options
bufferevent_get_options_(struct bufferevent *bev)
{
	struct bufferevent_private *bev_p = BEV_UPCAST(bev);
	enum bufferevent_options options;

	BEV_LOCK(bev);
	options = bev_p->options;
	BEV_UNLOCK(bev);
	return options;
}