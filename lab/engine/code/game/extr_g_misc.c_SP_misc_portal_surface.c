#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  origin2; int /*<<< orphan*/  origin; int /*<<< orphan*/  eType; } ;
struct TYPE_7__ {int /*<<< orphan*/  svFlags; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
struct TYPE_9__ {scalar_t__ nextthink; int /*<<< orphan*/  think; TYPE_2__ s; int /*<<< orphan*/  target; TYPE_1__ r; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_10__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_PORTAL ; 
 int /*<<< orphan*/  SVF_PORTAL ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ level ; 
 int /*<<< orphan*/  locateCamera ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_3__*) ; 

void SP_misc_portal_surface(gentity_t *ent) {
	VectorClear( ent->r.mins );
	VectorClear( ent->r.maxs );
	trap_LinkEntity (ent);

	ent->r.svFlags = SVF_PORTAL;
	ent->s.eType = ET_PORTAL;

	if ( !ent->target ) {
		VectorCopy( ent->s.origin, ent->s.origin2 );
	} else {
		ent->think = locateCamera;
		ent->nextthink = level.time + 100;
	}
}