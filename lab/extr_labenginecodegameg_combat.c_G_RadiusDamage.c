#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_11__ {scalar_t__* absmin; scalar_t__* absmax; int /*<<< orphan*/  currentOrigin; } ;
struct TYPE_12__ {TYPE_1__ r; int /*<<< orphan*/  takedamage; } ;
typedef  TYPE_2__ gentity_t ;

/* Variables and functions */
 scalar_t__ CanDamage (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  DAMAGE_RADIUS ; 
 int /*<<< orphan*/  G_Damage (TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*,scalar_t__*,scalar_t__*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ LogAccuracyHit (TYPE_2__*,TYPE_2__*) ; 
 int MAX_GENTITIES ; 
 float VectorLength (scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 TYPE_2__* g_entities ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int trap_EntitiesInBox (scalar_t__*,scalar_t__*,int*,int) ; 

qboolean G_RadiusDamage ( vec3_t origin, gentity_t *attacker, float damage, float radius,
					 gentity_t *ignore, int mod) {
	float		points, dist;
	gentity_t	*ent;
	int			entityList[MAX_GENTITIES];
	int			numListedEntities;
	vec3_t		mins, maxs;
	vec3_t		v;
	vec3_t		dir;
	int			i, e;
	qboolean	hitClient = qfalse;

	if ( radius < 1 ) {
		radius = 1;
	}

	for ( i = 0 ; i < 3 ; i++ ) {
		mins[i] = origin[i] - radius;
		maxs[i] = origin[i] + radius;
	}

	numListedEntities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

	for ( e = 0 ; e < numListedEntities ; e++ ) {
		ent = &g_entities[entityList[ e ]];

		if (ent == ignore)
			continue;
		if (!ent->takedamage)
			continue;

		// find the distance from the edge of the bounding box
		for ( i = 0 ; i < 3 ; i++ ) {
			if ( origin[i] < ent->r.absmin[i] ) {
				v[i] = ent->r.absmin[i] - origin[i];
			} else if ( origin[i] > ent->r.absmax[i] ) {
				v[i] = origin[i] - ent->r.absmax[i];
			} else {
				v[i] = 0;
			}
		}

		dist = VectorLength( v );
		if ( dist >= radius ) {
			continue;
		}

		points = damage * ( 1.0 - dist / radius );

		if( CanDamage (ent, origin) ) {
			if( LogAccuracyHit( ent, attacker ) ) {
				hitClient = qtrue;
			}
			VectorSubtract (ent->r.currentOrigin, origin, dir);
			// push the center of mass higher than the origin so players
			// get knocked into the air more
			dir[2] += 24;
			G_Damage (ent, NULL, attacker, dir, origin, (int)points, DAMAGE_RADIUS, mod);
		}
	}

	return hitClient;
}