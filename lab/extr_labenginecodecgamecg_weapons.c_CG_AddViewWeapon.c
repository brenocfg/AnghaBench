#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_19__ ;
typedef  struct TYPE_30__   TYPE_18__ ;
typedef  struct TYPE_29__   TYPE_17__ ;
typedef  struct TYPE_28__   TYPE_16__ ;
typedef  struct TYPE_27__   TYPE_15__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_11__ ;

/* Type definitions */
struct TYPE_37__ {int /*<<< orphan*/  handsModel; } ;
typedef  TYPE_6__ weaponInfo_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_38__ {int renderfx; int /*<<< orphan*/  hModel; scalar_t__ backlerp; void* oldframe; void* frame; int /*<<< orphan*/  axis; int /*<<< orphan*/  origin; } ;
typedef  TYPE_7__ refEntity_t ;
struct TYPE_39__ {scalar_t__* persistant; scalar_t__ pm_type; size_t clientNum; size_t weapon; } ;
typedef  TYPE_8__ playerState_t ;
typedef  int /*<<< orphan*/  hand ;
typedef  int /*<<< orphan*/  clientInfo_t ;
struct TYPE_35__ {scalar_t__ backlerp; int /*<<< orphan*/  oldFrame; int /*<<< orphan*/  frame; } ;
struct TYPE_36__ {TYPE_4__ torso; } ;
struct TYPE_34__ {size_t clientNum; } ;
struct TYPE_40__ {TYPE_5__ pe; TYPE_3__ currentState; } ;
typedef  TYPE_9__ centity_t ;
struct TYPE_33__ {int /*<<< orphan*/ * viewaxis; int /*<<< orphan*/  vieworg; } ;
struct TYPE_32__ {int eFlags; } ;
struct TYPE_31__ {TYPE_9__ predictedPlayerEntity; TYPE_2__ refdef; scalar_t__ testGun; TYPE_1__ predictedPlayerState; scalar_t__ renderingThirdPerson; } ;
struct TYPE_30__ {int /*<<< orphan*/  integer; } ;
struct TYPE_29__ {int integer; } ;
struct TYPE_28__ {void* integer; } ;
struct TYPE_27__ {float value; } ;
struct TYPE_26__ {float value; } ;
struct TYPE_25__ {float value; } ;
struct TYPE_24__ {int /*<<< orphan*/ * clientinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_AddPlayerWeapon (TYPE_7__*,TYPE_8__*,TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  CG_CalculateWeaponPosition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_LightningBolt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* CG_MapTorsoToWeaponFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_RegisterWeapon (size_t) ; 
 int EF_FIRING ; 
 size_t PERS_TEAM ; 
 scalar_t__ PM_INTERMISSION ; 
 int RF_DEPTHHACK ; 
 int RF_FIRST_PERSON ; 
 int RF_MINLIGHT ; 
 scalar_t__ TEAM_SPECTATOR ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_19__ cg ; 
 TYPE_18__ cg_drawGun ; 
 int /*<<< orphan*/ * cg_entities ; 
 TYPE_17__ cg_fov ; 
 TYPE_16__ cg_gun_frame ; 
 TYPE_15__ cg_gun_x ; 
 TYPE_14__ cg_gun_y ; 
 TYPE_13__ cg_gun_z ; 
 TYPE_6__* cg_weapons ; 
 TYPE_11__ cgs ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

void CG_AddViewWeapon( playerState_t *ps ) {
	refEntity_t	hand;
	centity_t	*cent;
	clientInfo_t	*ci;
	float		fovOffset;
	vec3_t		angles;
	weaponInfo_t	*weapon;

	if ( ps->persistant[PERS_TEAM] == TEAM_SPECTATOR ) {
		return;
	}

	if ( ps->pm_type == PM_INTERMISSION ) {
		return;
	}

	// no gun if in third person view or a camera is active
	//if ( cg.renderingThirdPerson || cg.cameraMode) {
	if ( cg.renderingThirdPerson ) {
		return;
	}


	// allow the gun to be completely removed
	if ( !cg_drawGun.integer ) {
		vec3_t		origin;

		if ( cg.predictedPlayerState.eFlags & EF_FIRING ) {
			// special hack for lightning gun...
			VectorCopy( cg.refdef.vieworg, origin );
			VectorMA( origin, -8, cg.refdef.viewaxis[2], origin );
			CG_LightningBolt( &cg_entities[ps->clientNum], origin );
		}
		return;
	}

	// don't draw if testing a gun model
	if ( cg.testGun ) {
		return;
	}

	// drop gun lower at higher fov
	if ( cg_fov.integer > 90 ) {
		fovOffset = -0.2 * ( cg_fov.integer - 90 );
	} else {
		fovOffset = 0;
	}

	cent = &cg.predictedPlayerEntity;	// &cg_entities[cg.snap->ps.clientNum];
	CG_RegisterWeapon( ps->weapon );
	weapon = &cg_weapons[ ps->weapon ];

	memset (&hand, 0, sizeof(hand));

	// set up gun position
	CG_CalculateWeaponPosition( hand.origin, angles );

	VectorMA( hand.origin, cg_gun_x.value, cg.refdef.viewaxis[0], hand.origin );
	VectorMA( hand.origin, cg_gun_y.value, cg.refdef.viewaxis[1], hand.origin );
	VectorMA( hand.origin, (cg_gun_z.value+fovOffset), cg.refdef.viewaxis[2], hand.origin );

	AnglesToAxis( angles, hand.axis );

	// map torso animations to weapon animations
	if ( cg_gun_frame.integer ) {
		// development tool
		hand.frame = hand.oldframe = cg_gun_frame.integer;
		hand.backlerp = 0;
	} else {
		// get clientinfo for animation map
		ci = &cgs.clientinfo[ cent->currentState.clientNum ];
		hand.frame = CG_MapTorsoToWeaponFrame( ci, cent->pe.torso.frame );
		hand.oldframe = CG_MapTorsoToWeaponFrame( ci, cent->pe.torso.oldFrame );
		hand.backlerp = cent->pe.torso.backlerp;
	}

	hand.hModel = weapon->handsModel;
	hand.renderfx = RF_DEPTHHACK | RF_FIRST_PERSON | RF_MINLIGHT;

	// add everything onto the hand
	CG_AddPlayerWeapon( &hand, ps, &cg.predictedPlayerEntity, ps->persistant[PERS_TEAM] );
}