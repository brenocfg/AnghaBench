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
struct comm_timer {void (* callback ) (void*) ;void* cb_arg; struct internal_timer* ev_timer; } ;
struct internal_timer {struct comm_timer super; int /*<<< orphan*/ * ev; struct comm_base* base; } ;
struct comm_base {TYPE_1__* eb; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  UB_EV_TIMEOUT ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  comm_timer_callback ; 
 int /*<<< orphan*/  free (struct internal_timer*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/ * ub_event_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_timer*) ; 

struct comm_timer* 
comm_timer_create(struct comm_base* base, void (*cb)(void*), void* cb_arg)
{
	struct internal_timer *tm = (struct internal_timer*)calloc(1,
		sizeof(struct internal_timer));
	if(!tm) {
		log_err("malloc failed");
		return NULL;
	}
	tm->super.ev_timer = tm;
	tm->base = base;
	tm->super.callback = cb;
	tm->super.cb_arg = cb_arg;
	tm->ev = ub_event_new(base->eb->base, -1, UB_EV_TIMEOUT, 
		comm_timer_callback, &tm->super);
	if(tm->ev == NULL) {
		log_err("timer_create: event_base_set failed.");
		free(tm);
		return NULL;
	}
	return &tm->super;
}