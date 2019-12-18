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
struct bufferevent_private {size_t max_single_read; } ;
struct bufferevent {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 size_t EV_SSIZE_MAX ; 
 size_t MAX_SINGLE_READ_DEFAULT ; 
 int evbuffer_set_max_read (int /*<<< orphan*/ ,size_t) ; 

int
bufferevent_set_max_single_read(struct bufferevent *bev, size_t size)
{
	struct bufferevent_private *bevp;
	int ret = 0;
	BEV_LOCK(bev);
	bevp = BEV_UPCAST(bev);
	if (size == 0 || size > EV_SSIZE_MAX)
		bevp->max_single_read = MAX_SINGLE_READ_DEFAULT;
	else
		bevp->max_single_read = size;
	ret = evbuffer_set_max_read(bev->input, bevp->max_single_read);
	BEV_UNLOCK(bev);
	return ret;
}