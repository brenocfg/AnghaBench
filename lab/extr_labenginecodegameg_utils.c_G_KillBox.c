#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_10__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
struct TYPE_13__ {TYPE_3__* client; TYPE_1__ r; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_11__ {int /*<<< orphan*/  origin; } ;
struct TYPE_12__ {TYPE_2__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAMAGE_NO_PROTECTION ; 
 int /*<<< orphan*/  G_Damage (TYPE_4__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_GENTITIES ; 
 int /*<<< orphan*/  MOD_TELEFRAG ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* g_entities ; 
 int trap_EntitiesInBox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

void G_KillBox (gentity_t *ent) {
	int			i, num;
	int			touch[MAX_GENTITIES];
	gentity_t	*hit;
	vec3_t		mins, maxs;

	VectorAdd( ent->client->ps.origin, ent->r.mins, mins );
	VectorAdd( ent->client->ps.origin, ent->r.maxs, maxs );
	num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

	for (i=0 ; i<num ; i++) {
		hit = &g_entities[touch[i]];
		if ( !hit->client ) {
			continue;
		}

		// nail it
		G_Damage ( hit, ent, ent, NULL, NULL,
			100000, DAMAGE_NO_PROTECTION, MOD_TELEFRAG);
	}

}