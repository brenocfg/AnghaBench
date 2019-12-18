#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  origin2; } ;
struct TYPE_13__ {scalar_t__ fly_sound_debounce_time; int /*<<< orphan*/  noise_index; TYPE_3__* client; TYPE_1__ s; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_14__ {scalar_t__ time; } ;
struct TYPE_11__ {scalar_t__ pm_type; int /*<<< orphan*/  velocity; scalar_t__* powerups; } ;
struct TYPE_12__ {TYPE_2__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_AUTO ; 
 int /*<<< orphan*/  G_Sound (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PM_NORMAL ; 
 size_t PW_FLIGHT ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ level ; 

void Use_target_push( gentity_t *self, gentity_t *other, gentity_t *activator ) {
	if ( !activator->client ) {
		return;
	}

	if ( activator->client->ps.pm_type != PM_NORMAL ) {
		return;
	}
	if ( activator->client->ps.powerups[PW_FLIGHT] ) {
		return;
	}

	VectorCopy (self->s.origin2, activator->client->ps.velocity);

	// play fly sound every 1.5 seconds
	if ( activator->fly_sound_debounce_time < level.time ) {
		activator->fly_sound_debounce_time = level.time + 1500;
		G_Sound( activator, CHAN_AUTO, self->noise_index );
	}
}