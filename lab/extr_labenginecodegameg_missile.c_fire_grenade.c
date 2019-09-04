#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_11__ {int /*<<< orphan*/  currentOrigin; int /*<<< orphan*/  ownerNum; int /*<<< orphan*/  svFlags; } ;
struct TYPE_9__ {int /*<<< orphan*/  trDelta; int /*<<< orphan*/  trBase; scalar_t__ trTime; int /*<<< orphan*/  trType; } ;
struct TYPE_10__ {TYPE_1__ pos; int /*<<< orphan*/  number; int /*<<< orphan*/  eFlags; int /*<<< orphan*/  weapon; int /*<<< orphan*/  eType; } ;
struct TYPE_12__ {char* classname; int damage; int splashDamage; int splashRadius; TYPE_3__ r; TYPE_2__ s; int /*<<< orphan*/ * target_ent; int /*<<< orphan*/  clipmask; int /*<<< orphan*/  splashMethodOfDeath; int /*<<< orphan*/  methodOfDeath; struct TYPE_12__* parent; int /*<<< orphan*/  think; scalar_t__ nextthink; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_13__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF_BOUNCE_HALF ; 
 int /*<<< orphan*/  ET_MISSILE ; 
 int /*<<< orphan*/  G_ExplodeMissile ; 
 TYPE_4__* G_Spawn () ; 
 int /*<<< orphan*/  MASK_SHOT ; 
 scalar_t__ MISSILE_PRESTEP_TIME ; 
 int /*<<< orphan*/  MOD_GRENADE ; 
 int /*<<< orphan*/  MOD_GRENADE_SPLASH ; 
 int /*<<< orphan*/  SVF_USE_CURRENT_ORIGIN ; 
 int /*<<< orphan*/  SnapVector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TR_GRAVITY ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WP_GRENADE_LAUNCHER ; 
 TYPE_5__ level ; 

gentity_t *fire_grenade (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "grenade";
	bolt->nextthink = level.time + 2500;
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_GRENADE_LAUNCHER;
	bolt->s.eFlags = EF_BOUNCE_HALF;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = 100;
	bolt->splashDamage = 100;
	bolt->splashRadius = 150;
	bolt->methodOfDeath = MOD_GRENADE;
	bolt->splashMethodOfDeath = MOD_GRENADE_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_GRAVITY;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
	VectorScale( dir, 700, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth

	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}