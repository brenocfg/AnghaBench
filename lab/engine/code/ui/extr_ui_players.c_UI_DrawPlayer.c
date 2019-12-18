#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  double* vec3_t ;
typedef  int /*<<< orphan*/  torso ;
struct TYPE_21__ {float x; float y; float width; float height; int fov_x; int fov_y; int time; double* origin; double* lightingOrigin; int renderfx; double* oldorigin; scalar_t__ hModel; int /*<<< orphan*/  axis; int /*<<< orphan*/  customSkin; int /*<<< orphan*/  backlerp; int /*<<< orphan*/  frame; int /*<<< orphan*/  oldframe; int /*<<< orphan*/  viewaxis; int /*<<< orphan*/  rdflags; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ refdef_t ;
typedef  int /*<<< orphan*/  refdef ;
typedef  TYPE_3__ refEntity_t ;
struct TYPE_22__ {scalar_t__ pendingWeapon; int weaponTimer; scalar_t__ weapon; scalar_t__ lastWeapon; scalar_t__ currentWeapon; scalar_t__ realWeapon; int muzzleFlashTime; double* flashDlightColor; scalar_t__ chat; scalar_t__ weaponModel; scalar_t__ flashModel; scalar_t__ barrelModel; scalar_t__ torsoModel; int /*<<< orphan*/  headSkin; scalar_t__ headModel; scalar_t__ legsModel; int /*<<< orphan*/  torsoSkin; int /*<<< orphan*/  legsSkin; TYPE_2__* animations; } ;
typedef  TYPE_5__ playerInfo_t ;
typedef  int /*<<< orphan*/  legs ;
typedef  int /*<<< orphan*/  head ;
typedef  int /*<<< orphan*/  gun ;
typedef  int /*<<< orphan*/  flash ;
typedef  int /*<<< orphan*/  barrel ;
struct TYPE_19__ {float xscale; int yscale; } ;
struct TYPE_23__ {TYPE_1__ uiDC; } ;
struct TYPE_20__ {int /*<<< orphan*/  numFrames; } ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AxisClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHAN_LOCAL ; 
 double DEG2RAD (int) ; 
 int M_PI ; 
 size_t PITCH ; 
 int /*<<< orphan*/  RDF_NOWORLDMODEL ; 
 int RF_LIGHTING_ORIGIN ; 
 int RF_NOSHADOW ; 
 size_t ROLL ; 
 int /*<<< orphan*/  UI_AdjustFrom640 (float*,float*,float*,float*) ; 
 double UI_MachinegunSpinAngle (TYPE_5__*) ; 
 int /*<<< orphan*/  UI_PlayerAngles (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_PlayerAnimation (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_PlayerFloatSprite (TYPE_5__*,double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_PositionEntityOnTag (TYPE_3__*,TYPE_3__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  UI_PositionRotatedEntityOnTag (TYPE_3__*,TYPE_3__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  VectorCopy (double*,double*) ; 
 scalar_t__ WP_BFG ; 
 scalar_t__ WP_GAUNTLET ; 
 scalar_t__ WP_MACHINEGUN ; 
 scalar_t__ WP_NONE ; 
 scalar_t__ WP_NUM_WEAPONS ; 
 size_t YAW ; 
 int atan2 (int,float) ; 
 int dp_realtime ; 
 scalar_t__ jumpHeight ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int rand () ; 
 float tan (double) ; 
 int /*<<< orphan*/  trap_R_AddLightToScene (double*,int,double,double,double) ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_3__*) ; 
 int /*<<< orphan*/  trap_R_ClearScene () ; 
 int /*<<< orphan*/  trap_R_RegisterShaderNoMip (char*) ; 
 int /*<<< orphan*/  trap_R_RenderScene (TYPE_3__*) ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ uiInfo ; 
 int /*<<< orphan*/  weaponChangeSound ; 

void UI_DrawPlayer( float x, float y, float w, float h, playerInfo_t *pi, int time ) {
	refdef_t		refdef;
	refEntity_t		legs = {0};
	refEntity_t		torso = {0};
	refEntity_t		head = {0};
	refEntity_t		gun = {0};
	refEntity_t		barrel = {0};
	refEntity_t		flash = {0};
	vec3_t			origin;
	int				renderfx;
	vec3_t			mins = {-16, -16, -24};
	vec3_t			maxs = {16, 16, 32};
	float			len;
	float			xx;

	if ( !pi->legsModel || !pi->torsoModel || !pi->headModel || !pi->animations[0].numFrames ) {
		return;
	}

	// this allows the ui to cache the player model on the main menu
	if (w == 0 || h == 0) {
		return;
	}

	dp_realtime = time;

	if ( pi->pendingWeapon != WP_NUM_WEAPONS && dp_realtime > pi->weaponTimer ) {
		pi->weapon = pi->pendingWeapon;
		pi->lastWeapon = pi->pendingWeapon;
		pi->pendingWeapon = WP_NUM_WEAPONS;
		pi->weaponTimer = 0;
		if( pi->currentWeapon != pi->weapon ) {
			trap_S_StartLocalSound( weaponChangeSound, CHAN_LOCAL );
		}
	}

	UI_AdjustFrom640( &x, &y, &w, &h );

	y -= jumpHeight;

	memset( &refdef, 0, sizeof( refdef ) );
	memset( &legs, 0, sizeof(legs) );
	memset( &torso, 0, sizeof(torso) );
	memset( &head, 0, sizeof(head) );

	refdef.rdflags = RDF_NOWORLDMODEL;

	AxisClear( refdef.viewaxis );

	refdef.x = x;
	refdef.y = y;
	refdef.width = w;
	refdef.height = h;

	refdef.fov_x = (int)((float)refdef.width / uiInfo.uiDC.xscale / 640.0f * 90.0f);
	xx = refdef.width / uiInfo.uiDC.xscale / tan( refdef.fov_x / 360 * M_PI );
	refdef.fov_y = atan2( refdef.height / uiInfo.uiDC.yscale, xx );
	refdef.fov_y *= ( 360 / (float)M_PI );

	// calculate distance so the player nearly fills the box
	len = 0.7 * ( maxs[2] - mins[2] );
	origin[0] = len / tan( DEG2RAD(refdef.fov_x) * 0.5 );
	origin[1] = 0.5 * ( mins[1] + maxs[1] );
	origin[2] = -0.5 * ( mins[2] + maxs[2] );

	refdef.time = dp_realtime;

	trap_R_ClearScene();

	// get the rotation information
	UI_PlayerAngles( pi, legs.axis, torso.axis, head.axis );
	
	// get the animation state (after rotation, to allow feet shuffle)
	UI_PlayerAnimation( pi, &legs.oldframe, &legs.frame, &legs.backlerp,
		 &torso.oldframe, &torso.frame, &torso.backlerp );

	renderfx = RF_LIGHTING_ORIGIN | RF_NOSHADOW;

	//
	// add the legs
	//
	legs.hModel = pi->legsModel;
	legs.customSkin = pi->legsSkin;

	VectorCopy( origin, legs.origin );

	VectorCopy( origin, legs.lightingOrigin );
	legs.renderfx = renderfx;
	VectorCopy (legs.origin, legs.oldorigin);

	trap_R_AddRefEntityToScene( &legs );

	if (!legs.hModel) {
		return;
	}

	//
	// add the torso
	//
	torso.hModel = pi->torsoModel;
	if (!torso.hModel) {
		return;
	}

	torso.customSkin = pi->torsoSkin;

	VectorCopy( origin, torso.lightingOrigin );

	UI_PositionRotatedEntityOnTag( &torso, &legs, pi->legsModel, "tag_torso");

	torso.renderfx = renderfx;

	trap_R_AddRefEntityToScene( &torso );

	//
	// add the head
	//
	head.hModel = pi->headModel;
	if (!head.hModel) {
		return;
	}
	head.customSkin = pi->headSkin;

	VectorCopy( origin, head.lightingOrigin );

	UI_PositionRotatedEntityOnTag( &head, &torso, pi->torsoModel, "tag_head");

	head.renderfx = renderfx;

	trap_R_AddRefEntityToScene( &head );

	//
	// add the gun
	//
	if ( pi->currentWeapon != WP_NONE ) {
		memset( &gun, 0, sizeof(gun) );
		gun.hModel = pi->weaponModel;
		VectorCopy( origin, gun.lightingOrigin );
		UI_PositionEntityOnTag( &gun, &torso, pi->torsoModel, "tag_weapon");
		gun.renderfx = renderfx;
		trap_R_AddRefEntityToScene( &gun );
	}

	//
	// add the spinning barrel
	//
	if ( pi->realWeapon == WP_MACHINEGUN || pi->realWeapon == WP_GAUNTLET || pi->realWeapon == WP_BFG ) {
		vec3_t	angles;

		memset( &barrel, 0, sizeof(barrel) );
		VectorCopy( origin, barrel.lightingOrigin );
		barrel.renderfx = renderfx;

		barrel.hModel = pi->barrelModel;
		angles[YAW] = 0;
		angles[PITCH] = 0;
		angles[ROLL] = UI_MachinegunSpinAngle( pi );
		AnglesToAxis( angles, barrel.axis );

		UI_PositionRotatedEntityOnTag( &barrel, &gun, pi->weaponModel, "tag_barrel");

		trap_R_AddRefEntityToScene( &barrel );
	}

	//
	// add muzzle flash
	//
	if ( dp_realtime <= pi->muzzleFlashTime ) {
		if ( pi->flashModel ) {
			memset( &flash, 0, sizeof(flash) );
			flash.hModel = pi->flashModel;
			VectorCopy( origin, flash.lightingOrigin );
			UI_PositionEntityOnTag( &flash, &gun, pi->weaponModel, "tag_flash");
			flash.renderfx = renderfx;
			trap_R_AddRefEntityToScene( &flash );
		}

		// make a dlight for the flash
		if ( pi->flashDlightColor[0] || pi->flashDlightColor[1] || pi->flashDlightColor[2] ) {
			trap_R_AddLightToScene( flash.origin, 200 + (rand()&31), pi->flashDlightColor[0],
				pi->flashDlightColor[1], pi->flashDlightColor[2] );
		}
	}

	//
	// add the chat icon
	//
	if ( pi->chat ) {
		UI_PlayerFloatSprite( pi, origin, trap_R_RegisterShaderNoMip( "sprites/balloon3" ) );
	}

	//
	// add an accent light
	//
	origin[0] -= 100;	// + = behind, - = in front
	origin[1] += 100;	// + = left, - = right
	origin[2] += 100;	// + = above, - = below
	trap_R_AddLightToScene( origin, 500, 1.0, 1.0, 1.0 );

	origin[0] -= 100;
	origin[1] -= 100;
	origin[2] -= 100;
	trap_R_AddLightToScene( origin, 500, 1.0, 0.0, 0.0 );

	trap_R_RenderScene( &refdef );
}