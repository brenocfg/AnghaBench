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
struct TYPE_2__ {scalar_t__ high; } ;
struct bufferevent {int enabled; TYPE_1__ wm_read; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_OPT_DEFER_CALLBACKS ; 
 int EV_READ ; 
 int /*<<< orphan*/  bufferevent_trigger (struct bufferevent*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bufferevent_inbuf_wm_check(struct bufferevent *bev)
{
	if (!bev->wm_read.high)
		return;
	if (!(bev->enabled & EV_READ))
		return;
	if (evbuffer_get_length(bev->input) < bev->wm_read.high)
		return;

	bufferevent_trigger(bev, EV_READ, BEV_OPT_DEFER_CALLBACKS);
}