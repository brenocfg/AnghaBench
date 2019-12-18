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
struct TYPE_4__ {scalar_t__ low; } ;
struct TYPE_3__ {scalar_t__ low; } ;
struct bufferevent {TYPE_2__ wm_write; int /*<<< orphan*/  output; TYPE_1__ wm_read; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int BEV_TRIG_IGNORE_WATERMARKS ; 
 short EV_READ ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_run_readcb_ (struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_run_writecb_ (struct bufferevent*,int) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
bufferevent_trigger_nolock_(struct bufferevent *bufev, short iotype, int options)
{
	if ((iotype & EV_READ) && ((options & BEV_TRIG_IGNORE_WATERMARKS) ||
	    evbuffer_get_length(bufev->input) >= bufev->wm_read.low))
		bufferevent_run_readcb_(bufev, options);
	if ((iotype & EV_WRITE) && ((options & BEV_TRIG_IGNORE_WATERMARKS) ||
	    evbuffer_get_length(bufev->output) <= bufev->wm_write.low))
		bufferevent_run_writecb_(bufev, options);
}