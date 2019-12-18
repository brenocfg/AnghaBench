#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  idle_timer ;
struct TYPE_5__ {TYPE_2__* opaque; } ;
typedef  TYPE_1__ evTimerID ;
struct TYPE_6__ {int /*<<< orphan*/ * uap; } ;
typedef  TYPE_2__ evTimer ;
typedef  int /*<<< orphan*/  evContext ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 int evClearTimer (int /*<<< orphan*/ ,TYPE_1__) ; 

int
evClearIdleTimer(evContext opaqueCtx, evTimerID id) {
	evTimer *del = id.opaque;
	idle_timer *tt = del->uap;

	FREE(tt);
	return (evClearTimer(opaqueCtx, id));
}