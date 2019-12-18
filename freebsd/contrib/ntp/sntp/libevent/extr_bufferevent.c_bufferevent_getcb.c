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
struct bufferevent {void* cbarg; int /*<<< orphan*/  errorcb; int /*<<< orphan*/  writecb; int /*<<< orphan*/  readcb; } ;
typedef  int /*<<< orphan*/  bufferevent_event_cb ;
typedef  int /*<<< orphan*/  bufferevent_data_cb ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_LOCK (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_UNLOCK (struct bufferevent*) ; 

void
bufferevent_getcb(struct bufferevent *bufev,
    bufferevent_data_cb *readcb_ptr,
    bufferevent_data_cb *writecb_ptr,
    bufferevent_event_cb *eventcb_ptr,
    void **cbarg_ptr)
{
	BEV_LOCK(bufev);
	if (readcb_ptr)
		*readcb_ptr = bufev->readcb;
	if (writecb_ptr)
		*writecb_ptr = bufev->writecb;
	if (eventcb_ptr)
		*eventcb_ptr = bufev->errorcb;
	if (cbarg_ptr)
		*cbarg_ptr = bufev->cbarg;

	BEV_UNLOCK(bufev);
}