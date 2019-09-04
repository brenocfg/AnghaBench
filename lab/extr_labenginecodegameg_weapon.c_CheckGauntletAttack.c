#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_17__ {int /*<<< orphan*/  normal; } ;
struct TYPE_21__ {int surfaceFlags; size_t entityNum; int /*<<< orphan*/  endpos; TYPE_1__ plane; } ;
typedef  TYPE_5__ trace_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_18__ {int /*<<< orphan*/  weapon; int /*<<< orphan*/  eventParm; int /*<<< orphan*/  number; int /*<<< orphan*/  otherEntityNum; } ;
struct TYPE_22__ {TYPE_4__* client; scalar_t__ takedamage; TYPE_2__ s; } ;
typedef  TYPE_6__ gentity_t ;
struct TYPE_23__ {int value; } ;
struct TYPE_19__ {scalar_t__* powerups; int /*<<< orphan*/  viewangles; } ;
struct TYPE_20__ {TYPE_3__ ps; scalar_t__ noclip; } ;

/* Variables and functions */
 int /*<<< orphan*/  AngleVectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CalcMuzzlePoint (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirToByte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_MISSILE_HIT ; 
 int /*<<< orphan*/  EV_POWERUP_QUAD ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_Damage (TYPE_6__*,TYPE_6__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* G_TempEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASK_SHOT ; 
 int /*<<< orphan*/  MOD_GAUNTLET ; 
 size_t PW_QUAD ; 
 int SURF_NOIMPACT ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forward ; 
 TYPE_6__* g_entities ; 
 TYPE_8__ g_quadfactor ; 
 int /*<<< orphan*/  muzzle ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  right ; 
 int s_quadFactor ; 
 int /*<<< orphan*/  trap_Trace (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up ; 

qboolean CheckGauntletAttack( gentity_t *ent ) {
	trace_t		tr;
	vec3_t		end;
	gentity_t	*tent;
	gentity_t	*traceEnt;
	int			damage;

	// set aiming directions
	AngleVectors (ent->client->ps.viewangles, forward, right, up);

	CalcMuzzlePoint ( ent, forward, right, up, muzzle );

	VectorMA (muzzle, 32, forward, end);

	trap_Trace (&tr, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
	if ( tr.surfaceFlags & SURF_NOIMPACT ) {
		return qfalse;
	}

	if ( ent->client->noclip ) {
		return qfalse;
	}

	traceEnt = &g_entities[ tr.entityNum ];

	// send blood impact
	if ( traceEnt->takedamage && traceEnt->client ) {
		tent = G_TempEntity( tr.endpos, EV_MISSILE_HIT );
		tent->s.otherEntityNum = traceEnt->s.number;
		tent->s.eventParm = DirToByte( tr.plane.normal );
		tent->s.weapon = ent->s.weapon;
	}

	if ( !traceEnt->takedamage) {
		return qfalse;
	}

	if (ent->client->ps.powerups[PW_QUAD] ) {
		G_AddEvent( ent, EV_POWERUP_QUAD, 0 );
		s_quadFactor = g_quadfactor.value;
	} else {
		s_quadFactor = 1;
	}
#ifdef MISSIONPACK
	if( ent->client->persistantPowerup && ent->client->persistantPowerup->item && ent->client->persistantPowerup->item->giTag == PW_DOUBLER ) {
		s_quadFactor *= 2;
	}
#endif

	damage = 50 * s_quadFactor;
	G_Damage( traceEnt, ent, ent, forward, tr.endpos,
		damage, 0, MOD_GAUNTLET );

	return qtrue;
}