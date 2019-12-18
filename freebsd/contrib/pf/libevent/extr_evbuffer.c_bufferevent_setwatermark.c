#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t low; size_t high; } ;
struct TYPE_3__ {size_t low; size_t high; } ;
struct bufferevent {int /*<<< orphan*/  input; TYPE_2__ wm_write; TYPE_1__ wm_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LENGTH (int /*<<< orphan*/ ) ; 
 short EV_READ ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_read_pressure_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent*) ; 

void
bufferevent_setwatermark(struct bufferevent *bufev, short events,
    size_t lowmark, size_t highmark)
{
	if (events & EV_READ) {
		bufev->wm_read.low = lowmark;
		bufev->wm_read.high = highmark;
	}

	if (events & EV_WRITE) {
		bufev->wm_write.low = lowmark;
		bufev->wm_write.high = highmark;
	}

	/* If the watermarks changed then see if we should call read again */
	bufferevent_read_pressure_cb(bufev->input,
	    0, EVBUFFER_LENGTH(bufev->input), bufev);
}