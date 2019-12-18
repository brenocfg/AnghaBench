#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trace_t ;
struct TYPE_9__ {scalar_t__ timestamp; int spawnflags; int /*<<< orphan*/  damage; int /*<<< orphan*/  noise_index; int /*<<< orphan*/  takedamage; } ;
typedef  TYPE_1__ gentity_t ;
struct TYPE_10__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_AUTO ; 
 int DAMAGE_NO_PROTECTION ; 
 scalar_t__ FRAMETIME ; 
 int /*<<< orphan*/  G_Damage (TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_Sound (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_TRIGGER_HURT ; 
 TYPE_2__ level ; 

void hurt_touch( gentity_t *self, gentity_t *other, trace_t *trace ) {
	int		dflags;

	if ( !other->takedamage ) {
		return;
	}

	if ( self->timestamp > level.time ) {
		return;
	}

	if ( self->spawnflags & 16 ) {
		self->timestamp = level.time + 1000;
	} else {
		self->timestamp = level.time + FRAMETIME;
	}

	// play sound
	if ( !(self->spawnflags & 4) ) {
		G_Sound( other, CHAN_AUTO, self->noise_index );
	}

	if (self->spawnflags & 8)
		dflags = DAMAGE_NO_PROTECTION;
	else
		dflags = 0;
	G_Damage (other, self, self, NULL, NULL, self->damage, dflags, MOD_TRIGGER_HURT);
}