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
struct evbuffer {int dummy; } ;
struct TYPE_2__ {size_t high; } ;
struct bufferevent {int enabled; int /*<<< orphan*/  timeout_read; int /*<<< orphan*/  ev_read; TYPE_1__ wm_read; } ;

/* Variables and functions */
 int EV_READ ; 
 int /*<<< orphan*/  bufferevent_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_setcb (struct evbuffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bufferevent_read_pressure_cb(struct evbuffer *buf, size_t old, size_t now,
    void *arg) {
	struct bufferevent *bufev = arg;
	/* 
	 * If we are below the watermark then reschedule reading if it's
	 * still enabled.
	 */
	if (bufev->wm_read.high == 0 || now < bufev->wm_read.high) {
		evbuffer_setcb(buf, NULL, NULL);

		if (bufev->enabled & EV_READ)
			bufferevent_add(&bufev->ev_read, bufev->timeout_read);
	}
}