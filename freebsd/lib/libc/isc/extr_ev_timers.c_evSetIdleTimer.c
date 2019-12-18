#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  timer; struct timespec max_idle; int /*<<< orphan*/  lastTouched; void* uap; int /*<<< orphan*/  func; } ;
typedef  TYPE_1__ idle_timer ;
struct TYPE_13__ {int /*<<< orphan*/  opaque; } ;
typedef  TYPE_2__ evTimerID ;
typedef  int /*<<< orphan*/  evTimerFunc ;
struct TYPE_14__ {int /*<<< orphan*/  lastEventTime; } ;
typedef  TYPE_3__ evContext_p ;
struct TYPE_15__ {TYPE_3__* opaque; } ;
typedef  TYPE_4__ evContext ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  OKNEW (TYPE_1__*) ; 
 int /*<<< orphan*/  evAddTime (int /*<<< orphan*/ ,struct timespec) ; 
 scalar_t__ evSetTimer (TYPE_4__,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,struct timespec,TYPE_2__*) ; 
 int /*<<< orphan*/  idle_timeout ; 

int
evSetIdleTimer(evContext opaqueCtx,
		evTimerFunc func,
		void *uap,
		struct timespec max_idle,
		evTimerID *opaqueID
) {
	evContext_p *ctx = opaqueCtx.opaque;
	idle_timer *tt;

	/* Allocate and fill. */
	OKNEW(tt);
	tt->func = func;
	tt->uap = uap;
	tt->lastTouched = ctx->lastEventTime;
	tt->max_idle = max_idle;

	if (evSetTimer(opaqueCtx, idle_timeout, tt,
		       evAddTime(ctx->lastEventTime, max_idle),
		       max_idle, opaqueID) < 0) {
		FREE(tt);
		return (-1);
	}

	tt->timer = opaqueID->opaque;

	return (0);
}