#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_12__ {int /*<<< orphan*/  currentOrigin; } ;
struct TYPE_16__ {TYPE_6__* parent; TYPE_3__ r; TYPE_2__* enemy; } ;
typedef  TYPE_7__ gentity_t ;
struct TYPE_15__ {TYPE_5__* client; } ;
struct TYPE_13__ {scalar_t__* grapplePoint; } ;
struct TYPE_14__ {TYPE_4__ ps; } ;
struct TYPE_10__ {double* mins; double* maxs; scalar_t__* currentOrigin; } ;
struct TYPE_11__ {TYPE_1__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_SetOrigin (TYPE_7__*,scalar_t__*) ; 
 int /*<<< orphan*/  SnapVectorTowards (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,scalar_t__*) ; 

void Weapon_HookThink (gentity_t *ent)
{
	if (ent->enemy) {
		vec3_t v, oldorigin;

		VectorCopy(ent->r.currentOrigin, oldorigin);
		v[0] = ent->enemy->r.currentOrigin[0] + (ent->enemy->r.mins[0] + ent->enemy->r.maxs[0]) * 0.5;
		v[1] = ent->enemy->r.currentOrigin[1] + (ent->enemy->r.mins[1] + ent->enemy->r.maxs[1]) * 0.5;
		v[2] = ent->enemy->r.currentOrigin[2] + (ent->enemy->r.mins[2] + ent->enemy->r.maxs[2]) * 0.5;
		SnapVectorTowards( v, oldorigin );	// save net bandwidth

		G_SetOrigin( ent, v );
	}

	VectorCopy( ent->r.currentOrigin, ent->parent->client->ps.grapplePoint);
}