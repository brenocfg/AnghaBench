#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int missileRenderfx; int /*<<< orphan*/  missileModel; scalar_t__ missileSound; } ;
typedef  TYPE_2__ weaponInfo_t ;
struct TYPE_15__ {int skinNum; int renderfx; int** axis; int /*<<< orphan*/  hModel; int /*<<< orphan*/  oldorigin; int /*<<< orphan*/  origin; } ;
typedef  TYPE_3__ refEntity_t ;
struct TYPE_13__ {int /*<<< orphan*/  trDelta; } ;
struct TYPE_16__ {size_t weapon; TYPE_1__ pos; int /*<<< orphan*/  number; int /*<<< orphan*/  angles; } ;
typedef  TYPE_4__ entityState_t ;
typedef  int /*<<< orphan*/  ent ;
struct TYPE_17__ {int /*<<< orphan*/  lerpOrigin; TYPE_4__ currentState; int /*<<< orphan*/  lerpAngles; } ;
typedef  TYPE_5__ centity_t ;
struct TYPE_18__ {int clientFrame; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_GrappleTrail (TYPE_5__*,TYPE_2__ const*) ; 
 int RF_NOSHADOW ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VectorNormalize2 (int /*<<< orphan*/ ,int*) ; 
 size_t WP_NUM_WEAPONS ; 
 TYPE_9__ cg ; 
 TYPE_2__* cg_weapons ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_3__*) ; 
 int /*<<< orphan*/  trap_S_AddLoopingSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vec3_origin ; 

__attribute__((used)) static void CG_Grapple( centity_t *cent ) {
	refEntity_t			ent;
	entityState_t		*s1;
	const weaponInfo_t		*weapon;

	s1 = &cent->currentState;
	if ( s1->weapon >= WP_NUM_WEAPONS ) {
		s1->weapon = 0;
	}
	weapon = &cg_weapons[s1->weapon];

	// calculate the axis
	VectorCopy( s1->angles, cent->lerpAngles);

#if 0 // FIXME add grapple pull sound here..?
	// add missile sound
	if ( weapon->missileSound ) {
		trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin, weapon->missileSound );
	}
#endif

	// Will draw cable if needed
	CG_GrappleTrail ( cent, weapon );

	// create the render entity
	memset (&ent, 0, sizeof(ent));
	VectorCopy( cent->lerpOrigin, ent.origin);
	VectorCopy( cent->lerpOrigin, ent.oldorigin);

	// flicker between two skins
	ent.skinNum = cg.clientFrame & 1;
	ent.hModel = weapon->missileModel;
	ent.renderfx = weapon->missileRenderfx | RF_NOSHADOW;

	// convert direction of travel into axis
	if ( VectorNormalize2( s1->pos.trDelta, ent.axis[0] ) == 0 ) {
		ent.axis[0][2] = 1;
	}

	trap_R_AddRefEntityToScene( &ent );
}