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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_14__ {int weapon; int /*<<< orphan*/  origin; } ;
struct TYPE_15__ {float random; TYPE_3__ s; int /*<<< orphan*/  movedir; TYPE_2__* enemy; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_12__ {int /*<<< orphan*/  currentOrigin; } ;
struct TYPE_13__ {TYPE_1__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_FIRE_WEAPON ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PerpendicularVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  WP_GRENADE_LAUNCHER 130 
#define  WP_PLASMAGUN 129 
#define  WP_ROCKET_LAUNCHER 128 
 float crandom () ; 
 int /*<<< orphan*/  fire_grenade (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fire_plasma (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fire_rocket (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Use_Shooter( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	vec3_t		dir;
	float		deg;
	vec3_t		up, right;

	// see if we have a target
	if ( ent->enemy ) {
		VectorSubtract( ent->enemy->r.currentOrigin, ent->s.origin, dir );
		VectorNormalize( dir );
	} else {
		VectorCopy( ent->movedir, dir );
	}

	// randomize a bit
	PerpendicularVector( up, dir );
	CrossProduct( up, dir, right );

	deg = crandom() * ent->random;
	VectorMA( dir, deg, up, dir );

	deg = crandom() * ent->random;
	VectorMA( dir, deg, right, dir );

	VectorNormalize( dir );

	switch ( ent->s.weapon ) {
	case WP_GRENADE_LAUNCHER:
		fire_grenade( ent, ent->s.origin, dir );
		break;
	case WP_ROCKET_LAUNCHER:
		fire_rocket( ent, ent->s.origin, dir );
		break;
	case WP_PLASMAGUN:
		fire_plasma( ent, ent->s.origin, dir );
		break;
	}

	G_AddEvent( ent, EV_FIRE_WEAPON, 0 );
}