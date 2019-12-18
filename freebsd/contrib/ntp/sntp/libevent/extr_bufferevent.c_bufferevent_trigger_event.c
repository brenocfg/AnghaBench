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
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int BEV_TRIG_ALL_OPTS ; 
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_incref_and_lock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (struct bufferevent*,short,int) ; 

void
bufferevent_trigger_event(struct bufferevent *bufev, short what, int options)
{
	bufferevent_incref_and_lock_(bufev);
	bufferevent_run_eventcb_(bufev, what, options&BEV_TRIG_ALL_OPTS);
	bufferevent_decref_and_unlock_(bufev);
}