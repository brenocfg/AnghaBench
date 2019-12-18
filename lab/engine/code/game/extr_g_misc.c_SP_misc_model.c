#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  trBase; } ;
struct TYPE_9__ {TYPE_1__ apos; int /*<<< orphan*/  angles; int /*<<< orphan*/  origin; int /*<<< orphan*/  modelindex; } ;
struct TYPE_10__ {TYPE_2__ s; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  model; } ;
typedef  TYPE_3__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_FreeEntity (TYPE_3__*) ; 
 int /*<<< orphan*/  G_ModelIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_SetOrigin (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_3__*) ; 

void SP_misc_model( gentity_t *ent ) {

#if 0
	ent->s.modelindex = G_ModelIndex( ent->model );
	VectorSet (ent->mins, -16, -16, -16);
	VectorSet (ent->maxs, 16, 16, 16);
	trap_LinkEntity (ent);

	G_SetOrigin( ent, ent->s.origin );
	VectorCopy( ent->s.angles, ent->s.apos.trBase );
#else
	G_FreeEntity( ent );
#endif
}