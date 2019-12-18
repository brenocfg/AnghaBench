#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_12__ ;

/* Type definitions */
typedef  size_t weapon_t ;
struct TYPE_30__ {scalar_t__* flashDlightColor; scalar_t__ weaponModel; scalar_t__ flashModel; scalar_t__ barrelModel; scalar_t__ readySound; scalar_t__ firingSound; } ;
typedef  TYPE_4__ weaponInfo_t ;
typedef  int* vec3_t ;
struct TYPE_31__ {int* shaderRGBA; int /*<<< orphan*/  origin; int /*<<< orphan*/ * axis; scalar_t__ hModel; int /*<<< orphan*/  renderfx; int /*<<< orphan*/  shadowPlane; int /*<<< orphan*/  lightingOrigin; scalar_t__ backlerp; int /*<<< orphan*/  frame; int /*<<< orphan*/  oldframe; } ;
typedef  TYPE_5__ refEntity_t ;
typedef  int /*<<< orphan*/  playerState_t ;
struct TYPE_32__ {int /*<<< orphan*/  axis; int /*<<< orphan*/ * origin; } ;
typedef  TYPE_6__ orientation_t ;
typedef  int /*<<< orphan*/  gun ;
typedef  int /*<<< orphan*/  flash ;
struct TYPE_33__ {int* c1RGBA; int* color1; } ;
typedef  TYPE_7__ clientInfo_t ;
struct TYPE_29__ {size_t weapon; size_t clientNum; int eFlags; scalar_t__ number; int /*<<< orphan*/  powerups; } ;
struct TYPE_28__ {scalar_t__ railFireTime; int /*<<< orphan*/  lightningFiring; } ;
struct TYPE_34__ {scalar_t__ muzzleFlashTime; TYPE_3__ currentState; int /*<<< orphan*/  lerpOrigin; TYPE_2__ pe; } ;
typedef  TYPE_8__ centity_t ;
typedef  int /*<<< orphan*/  barrel ;
struct TYPE_27__ {scalar_t__ clientNum; } ;
struct TYPE_26__ {scalar_t__ time; TYPE_1__ predictedPlayerState; scalar_t__ renderingThirdPerson; } ;
struct TYPE_25__ {int integer; } ;
struct TYPE_24__ {TYPE_7__* clientinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Byte4Copy (int*,int*) ; 
 int /*<<< orphan*/  CG_AddWeaponWithPowerups (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_LightningBolt (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int CG_MachinegunSpinAngle (TYPE_8__*) ; 
 int /*<<< orphan*/  CG_PositionRotatedEntityOnTag (TYPE_5__*,TYPE_5__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  CG_RegisterWeapon (size_t) ; 
 int EF_FIRING ; 
 scalar_t__ MUZZLE_FLASH_TIME ; 
 int /*<<< orphan*/  MatrixMultiply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t PITCH ; 
 size_t ROLL ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t WP_GAUNTLET ; 
 size_t WP_GRAPPLING_HOOK ; 
 size_t WP_LIGHTNING ; 
 size_t WP_RAILGUN ; 
 size_t YAW ; 
 TYPE_16__ cg ; 
 TYPE_15__ cg_drawGun ; 
 TYPE_8__* cg_entities ; 
 TYPE_4__* cg_weapons ; 
 TYPE_12__ cgs ; 
 int crandom () ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int rand () ; 
 int /*<<< orphan*/  trap_R_AddLightToScene (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_5__*) ; 
 int /*<<< orphan*/  trap_R_LerpTag (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  trap_S_AddLoopingSound (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vec3_origin ; 

void CG_AddPlayerWeapon( refEntity_t *parent, playerState_t *ps, centity_t *cent, int team ) {
	refEntity_t	gun;
	refEntity_t	barrel;
	refEntity_t	flash;
	vec3_t		angles;
	weapon_t	weaponNum;
	weaponInfo_t	*weapon;
	centity_t	*nonPredictedCent;
	orientation_t	lerped;

	weaponNum = cent->currentState.weapon;

	CG_RegisterWeapon( weaponNum );
	weapon = &cg_weapons[weaponNum];

	// add the weapon
	memset( &gun, 0, sizeof( gun ) );
	VectorCopy( parent->lightingOrigin, gun.lightingOrigin );
	gun.shadowPlane = parent->shadowPlane;
	gun.renderfx = parent->renderfx;

	// set custom shading for railgun refire rate
	if( weaponNum == WP_RAILGUN ) {
		clientInfo_t *ci = &cgs.clientinfo[cent->currentState.clientNum];
		if( cent->pe.railFireTime + 1500 > cg.time ) {
			int scale = 255 * ( cg.time - cent->pe.railFireTime ) / 1500;
			gun.shaderRGBA[0] = ( ci->c1RGBA[0] * scale ) >> 8;
			gun.shaderRGBA[1] = ( ci->c1RGBA[1] * scale ) >> 8;
			gun.shaderRGBA[2] = ( ci->c1RGBA[2] * scale ) >> 8;
			gun.shaderRGBA[3] = 255;
		}
		else {
			Byte4Copy( ci->c1RGBA, gun.shaderRGBA );
		}
	}

	gun.hModel = weapon->weaponModel;
	if (!gun.hModel) {
		return;
	}

	if ( !ps ) {
		// add weapon ready sound
		cent->pe.lightningFiring = qfalse;
		if ( ( cent->currentState.eFlags & EF_FIRING ) && weapon->firingSound ) {
			// lightning gun and guantlet make a different sound when fire is held down
			trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin, weapon->firingSound );
			cent->pe.lightningFiring = qtrue;
		} else if ( weapon->readySound ) {
			trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin, weapon->readySound );
		}
	}

	trap_R_LerpTag(&lerped, parent->hModel, parent->oldframe, parent->frame,
		1.0 - parent->backlerp, "tag_weapon");
	VectorCopy(parent->origin, gun.origin);

	VectorMA(gun.origin, lerped.origin[0], parent->axis[0], gun.origin);

	// Make weapon appear left-handed for 2 and centered for 3
	if(ps && cg_drawGun.integer == 2)
		VectorMA(gun.origin, -lerped.origin[1], parent->axis[1], gun.origin);
	else if(!ps || cg_drawGun.integer != 3)
	       	VectorMA(gun.origin, lerped.origin[1], parent->axis[1], gun.origin);

	VectorMA(gun.origin, lerped.origin[2], parent->axis[2], gun.origin);

	MatrixMultiply(lerped.axis, ((refEntity_t *)parent)->axis, gun.axis);
	gun.backlerp = parent->backlerp;

	CG_AddWeaponWithPowerups( &gun, cent->currentState.powerups );

	// add the spinning barrel
	if ( weapon->barrelModel ) {
		memset( &barrel, 0, sizeof( barrel ) );
		VectorCopy( parent->lightingOrigin, barrel.lightingOrigin );
		barrel.shadowPlane = parent->shadowPlane;
		barrel.renderfx = parent->renderfx;

		barrel.hModel = weapon->barrelModel;
		angles[YAW] = 0;
		angles[PITCH] = 0;
		angles[ROLL] = CG_MachinegunSpinAngle( cent );
		AnglesToAxis( angles, barrel.axis );

		CG_PositionRotatedEntityOnTag( &barrel, &gun, weapon->weaponModel, "tag_barrel" );

		CG_AddWeaponWithPowerups( &barrel, cent->currentState.powerups );
	}

	// make sure we aren't looking at cg.predictedPlayerEntity for LG
	nonPredictedCent = &cg_entities[cent->currentState.clientNum];

	// if the index of the nonPredictedCent is not the same as the clientNum
	// then this is a fake player (like on the single player podiums), so
	// go ahead and use the cent
	if( ( nonPredictedCent - cg_entities ) != cent->currentState.clientNum ) {
		nonPredictedCent = cent;
	}

	// add the flash
	if ( ( weaponNum == WP_LIGHTNING || weaponNum == WP_GAUNTLET || weaponNum == WP_GRAPPLING_HOOK )
		&& ( nonPredictedCent->currentState.eFlags & EF_FIRING ) ) 
	{
		// continuous flash
	} else {
		// impulse flash
		if ( cg.time - cent->muzzleFlashTime > MUZZLE_FLASH_TIME ) {
			return;
		}
	}

	memset( &flash, 0, sizeof( flash ) );
	VectorCopy( parent->lightingOrigin, flash.lightingOrigin );
	flash.shadowPlane = parent->shadowPlane;
	flash.renderfx = parent->renderfx;

	flash.hModel = weapon->flashModel;
	if (!flash.hModel) {
		return;
	}
	angles[YAW] = 0;
	angles[PITCH] = 0;
	angles[ROLL] = crandom() * 10;
	AnglesToAxis( angles, flash.axis );

	// colorize the railgun blast
	if ( weaponNum == WP_RAILGUN ) {
		clientInfo_t	*ci;

		ci = &cgs.clientinfo[ cent->currentState.clientNum ];
		flash.shaderRGBA[0] = 255 * ci->color1[0];
		flash.shaderRGBA[1] = 255 * ci->color1[1];
		flash.shaderRGBA[2] = 255 * ci->color1[2];
	}

	CG_PositionRotatedEntityOnTag( &flash, &gun, weapon->weaponModel, "tag_flash");
	trap_R_AddRefEntityToScene( &flash );

	if ( ps || cg.renderingThirdPerson ||
		cent->currentState.number != cg.predictedPlayerState.clientNum ) {
		// add lightning bolt
		CG_LightningBolt( nonPredictedCent, flash.origin );

		if ( weapon->flashDlightColor[0] || weapon->flashDlightColor[1] || weapon->flashDlightColor[2] ) {
			trap_R_AddLightToScene( flash.origin, 300 + (rand()&31), weapon->flashDlightColor[0],
				weapon->flashDlightColor[1], weapon->flashDlightColor[2] );
		}
	}
}