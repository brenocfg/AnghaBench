#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  double* vec3_t ;
struct TYPE_8__ {scalar_t__ pain_debounce_time; int flags; int /*<<< orphan*/  health; TYPE_3__* client; } ;
typedef  TYPE_2__ gentity_t ;
struct TYPE_7__ {scalar_t__ pm_type; int damagePitch; int damageYaw; float damageCount; int /*<<< orphan*/  damageEvent; } ;
struct TYPE_9__ {float damage_blood; float damage_armor; scalar_t__ damage_knockback; TYPE_1__ ps; int /*<<< orphan*/  damage_from; scalar_t__ damage_fromWorld; } ;
typedef  TYPE_3__ gclient_t ;
struct TYPE_10__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_PAIN ; 
 int FL_GODMODE ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t PITCH ; 
 scalar_t__ PM_DEAD ; 
 size_t YAW ; 
 TYPE_4__ level ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  vectoangles (int /*<<< orphan*/ ,double*) ; 

void P_DamageFeedback( gentity_t *player ) {
	gclient_t	*client;
	float	count;
	vec3_t	angles;

	client = player->client;
	if ( client->ps.pm_type == PM_DEAD ) {
		return;
	}

	// total points of damage shot at the player this frame
	count = client->damage_blood + client->damage_armor;
	if ( count == 0 ) {
		return;		// didn't take any damage
	}

	if ( count > 255 ) {
		count = 255;
	}

	// send the information to the client

	// world damage (falling, slime, etc) uses a special code
	// to make the blend blob centered instead of positional
	if ( client->damage_fromWorld ) {
		client->ps.damagePitch = 255;
		client->ps.damageYaw = 255;

		client->damage_fromWorld = qfalse;
	} else {
		vectoangles( client->damage_from, angles );
		client->ps.damagePitch = angles[PITCH]/360.0 * 256;
		client->ps.damageYaw = angles[YAW]/360.0 * 256;
	}

	// play an appropriate pain sound
	if ( (level.time > player->pain_debounce_time) && !(player->flags & FL_GODMODE) ) {
		player->pain_debounce_time = level.time + 700;
		G_AddEvent( player, EV_PAIN, player->health );
		client->ps.damageEvent++;
	}


	client->ps.damageCount = count;

	//
	// clear totals
	//
	client->damage_blood = 0;
	client->damage_armor = 0;
	client->damage_knockback = 0;
}