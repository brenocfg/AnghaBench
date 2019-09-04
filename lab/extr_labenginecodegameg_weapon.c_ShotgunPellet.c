#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_13__ {size_t entityNum; int surfaceFlags; int /*<<< orphan*/  endpos; } ;
typedef  TYPE_2__ trace_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_12__ {int number; } ;
struct TYPE_14__ {scalar_t__ takedamage; TYPE_1__ s; } ;
typedef  TYPE_3__ gentity_t ;

/* Variables and functions */
 int DEFAULT_SHOTGUN_DAMAGE ; 
 int /*<<< orphan*/  G_Damage (TYPE_3__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LogAccuracyHit (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  MASK_SHOT ; 
 int /*<<< orphan*/  MOD_SHOTGUN ; 
 int SURF_NOIMPACT ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forward ; 
 TYPE_3__* g_entities ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int s_quadFactor ; 
 int /*<<< orphan*/  trap_Trace (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

qboolean ShotgunPellet( vec3_t start, vec3_t end, gentity_t *ent ) {
	trace_t		tr;
	int			damage, i, passent;
	gentity_t	*traceEnt;
#ifdef MISSIONPACK
	vec3_t		impactpoint, bouncedir;
#endif
	vec3_t		tr_start, tr_end;
	qboolean	hitClient = qfalse;

	passent = ent->s.number;
	VectorCopy( start, tr_start );
	VectorCopy( end, tr_end );
	for (i = 0; i < 10; i++) {
		trap_Trace (&tr, tr_start, NULL, NULL, tr_end, passent, MASK_SHOT);
		traceEnt = &g_entities[ tr.entityNum ];

		// send bullet impact
		if (  tr.surfaceFlags & SURF_NOIMPACT ) {
			return qfalse;
		}

		if ( traceEnt->takedamage) {
			damage = DEFAULT_SHOTGUN_DAMAGE * s_quadFactor;
#ifdef MISSIONPACK
			if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
				if (G_InvulnerabilityEffect( traceEnt, forward, tr.endpos, impactpoint, bouncedir )) {
					G_BounceProjectile( tr_start, impactpoint, bouncedir, tr_end );
					VectorCopy( impactpoint, tr_start );
					// the player can hit him/herself with the bounced rail
					passent = ENTITYNUM_NONE;
				}
				else {
					VectorCopy( tr.endpos, tr_start );
					passent = traceEnt->s.number;
				}
				continue;
			}
#endif
			if( LogAccuracyHit( traceEnt, ent ) ) {
				hitClient = qtrue;
			}
			G_Damage( traceEnt, ent, ent, forward, tr.endpos, damage, 0, MOD_SHOTGUN);
			return hitClient;
		}
		return qfalse;
	}
	return qfalse;
}