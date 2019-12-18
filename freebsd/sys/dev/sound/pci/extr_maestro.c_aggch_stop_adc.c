#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct agg_rchinfo {TYPE_1__* parent; } ;
struct TYPE_8__ {int active; int playchns; } ;

/* Variables and functions */
 int /*<<< orphan*/  APUREG_APUTYPE ; 
 int APUTYPE_INACTIVE ; 
 int APU_APUTYPE_SHIFT ; 
 int /*<<< orphan*/  agg_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  agg_power (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  powerstate_idle ; 
 int /*<<< orphan*/  set_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  wp_starttimer (TYPE_1__*) ; 
 int /*<<< orphan*/  wp_stoptimer (TYPE_1__*) ; 
 int /*<<< orphan*/  wp_wrapu (TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
aggch_stop_adc(struct agg_rchinfo *ch)
{
	int apuch;

	agg_lock(ch->parent);

	/* to mark that this channel no longer needs further intrs. */
	ch->parent->active &= ~(1 << ch->parent->playchns);

	for (apuch = 0; apuch < 4; apuch++)
		wp_wrapu(ch->parent, apuch, APUREG_APUTYPE,
		    APUTYPE_INACTIVE << APU_APUTYPE_SHIFT);

	if (ch->parent->active) {
		set_timer(ch->parent);
		wp_starttimer(ch->parent);
	} else {
		wp_stoptimer(ch->parent);
		agg_power(ch->parent, powerstate_idle);
	}
	agg_unlock(ch->parent);
}