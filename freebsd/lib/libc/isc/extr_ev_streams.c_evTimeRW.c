#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  evTimerID ;
struct TYPE_4__ {TYPE_2__* opaque; } ;
typedef  TYPE_1__ evStreamID ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  timer; } ;
typedef  TYPE_2__ evStream ;
typedef  int /*<<< orphan*/  evContext ;

/* Variables and functions */
 int /*<<< orphan*/  EV_STR_TIMEROK ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 

int
evTimeRW(evContext opaqueCtx, evStreamID id, evTimerID timer) /*ARGSUSED*/ {
	evStream *str = id.opaque;

	UNUSED(opaqueCtx);

	str->timer = timer;
	str->flags |= EV_STR_TIMEROK;
	return (0);
}