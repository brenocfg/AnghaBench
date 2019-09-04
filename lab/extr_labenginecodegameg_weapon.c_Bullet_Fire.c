#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_16__ {int /*<<< orphan*/  normal; } ;
struct TYPE_18__ {int surfaceFlags; size_t entityNum; int /*<<< orphan*/  endpos; TYPE_2__ plane; } ;
typedef  TYPE_4__ trace_t ;
struct TYPE_17__ {int number; int eventParm; int otherEntityNum; } ;
struct TYPE_19__ {scalar_t__ takedamage; TYPE_3__ s; TYPE_1__* client; } ;
typedef  TYPE_5__ gentity_t ;
struct TYPE_15__ {int /*<<< orphan*/  accuracy_hits; } ;

/* Variables and functions */
 int DirToByte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_BULLET_HIT_FLESH ; 
 int /*<<< orphan*/  EV_BULLET_HIT_WALL ; 
 int /*<<< orphan*/  G_Damage (TYPE_5__*,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* G_TempEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LogAccuracyHit (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  MASK_SHOT ; 
 float M_PI ; 
 int SURF_NOIMPACT ; 
 int /*<<< orphan*/  SnapVectorTowards (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float cos (float) ; 
 float crandom () ; 
 int /*<<< orphan*/  forward ; 
 TYPE_5__* g_entities ; 
 int /*<<< orphan*/  muzzle ; 
 float random () ; 
 int /*<<< orphan*/  right ; 
 int s_quadFactor ; 
 float sin (float) ; 
 int /*<<< orphan*/  trap_Trace (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up ; 

void Bullet_Fire (gentity_t *ent, float spread, int damage, int mod ) {
	trace_t		tr;
	vec3_t		end;
#ifdef MISSIONPACK
	vec3_t		impactpoint, bouncedir;
#endif
	float		r;
	float		u;
	gentity_t	*tent;
	gentity_t	*traceEnt;
	int			i, passent;

	damage *= s_quadFactor;

	r = random() * M_PI * 2.0f;
	u = sin(r) * crandom() * spread * 16;
	r = cos(r) * crandom() * spread * 16;
	VectorMA (muzzle, 8192*16, forward, end);
	VectorMA (end, r, right, end);
	VectorMA (end, u, up, end);

	passent = ent->s.number;
	for (i = 0; i < 10; i++) {

		trap_Trace (&tr, muzzle, NULL, NULL, end, passent, MASK_SHOT);
		if ( tr.surfaceFlags & SURF_NOIMPACT ) {
			return;
		}

		traceEnt = &g_entities[ tr.entityNum ];

		// snap the endpos to integers, but nudged towards the line
		SnapVectorTowards( tr.endpos, muzzle );

		// send bullet impact
		if ( traceEnt->takedamage && traceEnt->client ) {
			tent = G_TempEntity( tr.endpos, EV_BULLET_HIT_FLESH );
			tent->s.eventParm = traceEnt->s.number;
			if( LogAccuracyHit( traceEnt, ent ) ) {
				ent->client->accuracy_hits++;
			}
		} else {
			tent = G_TempEntity( tr.endpos, EV_BULLET_HIT_WALL );
			tent->s.eventParm = DirToByte( tr.plane.normal );
		}
		tent->s.otherEntityNum = ent->s.number;

		if ( traceEnt->takedamage) {
#ifdef MISSIONPACK
			if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
				if (G_InvulnerabilityEffect( traceEnt, forward, tr.endpos, impactpoint, bouncedir )) {
					G_BounceProjectile( muzzle, impactpoint, bouncedir, end );
					VectorCopy( impactpoint, muzzle );
					// the player can hit him/herself with the bounced rail
					passent = ENTITYNUM_NONE;
				}
				else {
					VectorCopy( tr.endpos, muzzle );
					passent = traceEnt->s.number;
				}
				continue;
			}
			else {
#endif
				G_Damage( traceEnt, ent, ent, forward, tr.endpos,
					damage, 0, mod);
#ifdef MISSIONPACK
			}
#endif
		}
		break;
	}
}