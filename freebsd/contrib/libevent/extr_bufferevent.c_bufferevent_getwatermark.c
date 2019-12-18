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
struct TYPE_3__ {size_t low; size_t high; } ;
struct TYPE_4__ {size_t low; size_t high; } ;
struct bufferevent {TYPE_1__ wm_read; TYPE_2__ wm_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 short EV_READ ; 
 short EV_WRITE ; 

int
bufferevent_getwatermark(struct bufferevent *bufev, short events,
    size_t *lowmark, size_t *highmark)
{
	if (events == EV_WRITE) {
		BEV_LOCK(bufev);
		if (lowmark)
			*lowmark = bufev->wm_write.low;
		if (highmark)
			*highmark = bufev->wm_write.high;
		BEV_UNLOCK(bufev);
		return 0;
	}

	if (events == EV_READ) {
		BEV_LOCK(bufev);
		if (lowmark)
			*lowmark = bufev->wm_read.low;
		if (highmark)
			*highmark = bufev->wm_read.high;
		BEV_UNLOCK(bufev);
		return 0;
	}
	return -1;
}