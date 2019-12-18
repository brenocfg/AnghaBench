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
struct evbuffer_cb_info {int dummy; } ;
struct evbuffer {int dummy; } ;
struct TYPE_2__ {size_t high; } ;
struct bufferevent {TYPE_1__ wm_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  bufferevent_wm_suspend_read (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_wm_unsuspend_read (struct bufferevent*) ; 
 size_t evbuffer_get_length (struct evbuffer*) ; 

__attribute__((used)) static void
bufferevent_inbuf_wm_cb(struct evbuffer *buf,
    const struct evbuffer_cb_info *cbinfo,
    void *arg)
{
	struct bufferevent *bufev = arg;
	size_t size;

	size = evbuffer_get_length(buf);

	if (size >= bufev->wm_read.high)
		bufferevent_wm_suspend_read(bufev);
	else
		bufferevent_wm_unsuspend_read(bufev);
}