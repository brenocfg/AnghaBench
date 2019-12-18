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
 int BEV_TRIG_DEFER_CALLBACKS ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (struct bufferevent*,short,int) ; 

__attribute__((used)) static inline void
be_async_run_eventcb(struct bufferevent *bev, short what, int options)
{ bufferevent_run_eventcb_(bev, what, options|BEV_TRIG_DEFER_CALLBACKS); }