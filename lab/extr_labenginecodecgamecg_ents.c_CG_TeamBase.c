#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  hModel; int /*<<< orphan*/  axis; int /*<<< orphan*/  origin; int /*<<< orphan*/  lightingOrigin; int /*<<< orphan*/  reType; } ;
typedef  TYPE_3__ refEntity_t ;
typedef  int /*<<< orphan*/  model ;
struct TYPE_9__ {scalar_t__ modelindex; int /*<<< orphan*/  angles; } ;
struct TYPE_12__ {TYPE_1__ currentState; int /*<<< orphan*/  lerpOrigin; } ;
typedef  TYPE_4__ centity_t ;
struct TYPE_10__ {int /*<<< orphan*/  neutralFlagBaseModel; int /*<<< orphan*/  blueFlagBaseModel; int /*<<< orphan*/  redFlagBaseModel; } ;
struct TYPE_13__ {scalar_t__ gametype; TYPE_2__ media; } ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GT_CTF ; 
 int /*<<< orphan*/  RT_MODEL ; 
 scalar_t__ TEAM_BLUE ; 
 scalar_t__ TEAM_RED ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ cgs ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_3__*) ; 

__attribute__((used)) static void CG_TeamBase( centity_t *cent ) {
	refEntity_t model;
#ifdef MISSIONPACK
	vec3_t angles;
	int t, h;
	float c;

	if ( cgs.gametype == GT_CTF || cgs.gametype == GT_1FCTF ) {
#else
	if ( cgs.gametype == GT_CTF) {
#endif
		// show the flag base
		memset(&model, 0, sizeof(model));
		model.reType = RT_MODEL;
		VectorCopy( cent->lerpOrigin, model.lightingOrigin );
		VectorCopy( cent->lerpOrigin, model.origin );
		AnglesToAxis( cent->currentState.angles, model.axis );
		if ( cent->currentState.modelindex == TEAM_RED ) {
			model.hModel = cgs.media.redFlagBaseModel;
		}
		else if ( cent->currentState.modelindex == TEAM_BLUE ) {
			model.hModel = cgs.media.blueFlagBaseModel;
		}
		else {
			model.hModel = cgs.media.neutralFlagBaseModel;
		}
		trap_R_AddRefEntityToScene( &model );
	}
#ifdef MISSIONPACK
	else if ( cgs.gametype == GT_OBELISK ) {
		// show the obelisk
		memset(&model, 0, sizeof(model));
		model.reType = RT_MODEL;
		VectorCopy( cent->lerpOrigin, model.lightingOrigin );
		VectorCopy( cent->lerpOrigin, model.origin );
		AnglesToAxis( cent->currentState.angles, model.axis );

		model.hModel = cgs.media.overloadBaseModel;
		trap_R_AddRefEntityToScene( &model );
		// if hit
		if ( cent->currentState.frame == 1) {
			// show hit model
			// modelindex2 is the health value of the obelisk
			c = cent->currentState.modelindex2;
			model.shaderRGBA[0] = 0xff;
			model.shaderRGBA[1] = c;
			model.shaderRGBA[2] = c;
			model.shaderRGBA[3] = 0xff;
			//
			model.hModel = cgs.media.overloadEnergyModel;
			trap_R_AddRefEntityToScene( &model );
		}
		// if respawning
		if ( cent->currentState.frame == 2) {
			if ( !cent->miscTime ) {
				cent->miscTime = cg.time;
			}
			t = cg.time - cent->miscTime;
			h = (cg_obeliskRespawnDelay.integer - 5) * 1000;
			//
			if (t > h) {
				c = (float) (t - h) / h;
				if (c > 1)
					c = 1;
			}
			else {
				c = 0;
			}
			// show the lights
			AnglesToAxis( cent->currentState.angles, model.axis );
			//
			model.shaderRGBA[0] = c * 0xff;
			model.shaderRGBA[1] = c * 0xff;
			model.shaderRGBA[2] = c * 0xff;
			model.shaderRGBA[3] = c * 0xff;

			model.hModel = cgs.media.overloadLightsModel;
			trap_R_AddRefEntityToScene( &model );
			// show the target
			if (t > h) {
				if ( !cent->muzzleFlashTime ) {
					trap_S_StartSound (cent->lerpOrigin, ENTITYNUM_NONE, CHAN_BODY,  cgs.media.obeliskRespawnSound);
					cent->muzzleFlashTime = 1;
				}
				VectorCopy(cent->currentState.angles, angles);
				angles[YAW] += (float) 16 * acos(1-c) * 180 / M_PI;
				AnglesToAxis( angles, model.axis );

				VectorScale( model.axis[0], c, model.axis[0]);
				VectorScale( model.axis[1], c, model.axis[1]);
				VectorScale( model.axis[2], c, model.axis[2]);

				model.shaderRGBA[0] = 0xff;
				model.shaderRGBA[1] = 0xff;
				model.shaderRGBA[2] = 0xff;
				model.shaderRGBA[3] = 0xff;
				//
				model.origin[2] += 56;
				model.hModel = cgs.media.overloadTargetModel;
				trap_R_AddRefEntityToScene( &model );
			}
			else {
				//FIXME: show animated smoke
			}
		}
		else {
			cent->miscTime = 0;
			cent->muzzleFlashTime = 0;
			// modelindex2 is the health value of the obelisk
			c = cent->currentState.modelindex2;
			model.shaderRGBA[0] = 0xff;
			model.shaderRGBA[1] = c;
			model.shaderRGBA[2] = c;
			model.shaderRGBA[3] = 0xff;
			// show the lights
			model.hModel = cgs.media.overloadLightsModel;
			trap_R_AddRefEntityToScene( &model );
			// show the target
			model.origin[2] += 56;
			model.hModel = cgs.media.overloadTargetModel;
			trap_R_AddRefEntityToScene( &model );
		}
	}
	else if ( cgs.gametype == GT_HARVESTER ) {
		// show harvester model
		memset(&model, 0, sizeof(model));
		model.reType = RT_MODEL;
		VectorCopy( cent->lerpOrigin, model.lightingOrigin );
		VectorCopy( cent->lerpOrigin, model.origin );
		AnglesToAxis( cent->currentState.angles, model.axis );

		if ( cent->currentState.modelindex == TEAM_RED ) {
			model.hModel = cgs.media.harvesterModel;
			model.customSkin = cgs.media.harvesterRedSkin;
		}
		else if ( cent->currentState.modelindex == TEAM_BLUE ) {
			model.hModel = cgs.media.harvesterModel;
			model.customSkin = cgs.media.harvesterBlueSkin;
		}
		else {
			model.hModel = cgs.media.harvesterNeutralModel;
			model.customSkin = 0;
		}
		trap_R_AddRefEntityToScene( &model );
	}
#endif
}