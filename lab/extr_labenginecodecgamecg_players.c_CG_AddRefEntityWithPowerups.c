#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  customShader; } ;
typedef  TYPE_2__ refEntity_t ;
struct TYPE_11__ {int powerups; } ;
typedef  TYPE_3__ entityState_t ;
struct TYPE_13__ {int time; } ;
struct TYPE_9__ {int /*<<< orphan*/  battleSuitShader; int /*<<< orphan*/  regenShader; int /*<<< orphan*/  quadShader; int /*<<< orphan*/  redQuadShader; int /*<<< orphan*/  invisShader; } ;
struct TYPE_12__ {TYPE_1__ media; } ;

/* Variables and functions */
 int PW_BATTLESUIT ; 
 int PW_INVIS ; 
 int PW_QUAD ; 
 int PW_REGEN ; 
 int TEAM_RED ; 
 TYPE_6__ cg ; 
 TYPE_5__ cgs ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_2__*) ; 

void CG_AddRefEntityWithPowerups( refEntity_t *ent, entityState_t *state, int team ) {

	if ( state->powerups & ( 1 << PW_INVIS ) ) {
		ent->customShader = cgs.media.invisShader;
		trap_R_AddRefEntityToScene( ent );
	} else {
		/*
		if ( state->eFlags & EF_KAMIKAZE ) {
			if (team == TEAM_BLUE)
				ent->customShader = cgs.media.blueKamikazeShader;
			else
				ent->customShader = cgs.media.redKamikazeShader;
			trap_R_AddRefEntityToScene( ent );
		}
		else {*/
			trap_R_AddRefEntityToScene( ent );
		//}

		if ( state->powerups & ( 1 << PW_QUAD ) )
		{
			if (team == TEAM_RED)
				ent->customShader = cgs.media.redQuadShader;
			else
				ent->customShader = cgs.media.quadShader;
			trap_R_AddRefEntityToScene( ent );
		}
		if ( state->powerups & ( 1 << PW_REGEN ) ) {
			if ( ( ( cg.time / 100 ) % 10 ) == 1 ) {
				ent->customShader = cgs.media.regenShader;
				trap_R_AddRefEntityToScene( ent );
			}
		}
		if ( state->powerups & ( 1 << PW_BATTLESUIT ) ) {
			ent->customShader = cgs.media.battleSuitShader;
			trap_R_AddRefEntityToScene( ent );
		}
	}
}