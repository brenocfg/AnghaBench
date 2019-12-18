#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* sc_p ;
struct TYPE_7__ {int /*<<< orphan*/  nd_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  startTime; int /*<<< orphan*/  elapsedTime; int /*<<< orphan*/  endTime; } ;
struct TYPE_6__ {TYPE_1__ stats; TYPE_3__* node; int /*<<< orphan*/  intr_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_SOURCE_ACTIVE ; 
 int /*<<< orphan*/  getmicrotime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_uncallout (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  timevalsub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ng_source_stop(sc_p sc)
{
	ng_uncallout(&sc->intr_ch, sc->node);
	sc->node->nd_flags &= ~NG_SOURCE_ACTIVE;
	getmicrotime(&sc->stats.endTime);
	sc->stats.elapsedTime = sc->stats.endTime;
	timevalsub(&sc->stats.elapsedTime, &sc->stats.startTime);
}