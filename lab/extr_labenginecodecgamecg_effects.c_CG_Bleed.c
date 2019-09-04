#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_13__ {int rotation; int radius; int /*<<< orphan*/  renderfx; int /*<<< orphan*/  customShader; int /*<<< orphan*/  reType; int /*<<< orphan*/  origin; } ;
struct TYPE_14__ {TYPE_4__ refEntity; scalar_t__ startTime; scalar_t__ endTime; int /*<<< orphan*/  leType; } ;
typedef  TYPE_5__ localEntity_t ;
struct TYPE_17__ {TYPE_3__* snap; scalar_t__ time; } ;
struct TYPE_16__ {int /*<<< orphan*/  integer; } ;
struct TYPE_10__ {int /*<<< orphan*/  bloodExplosionShader; } ;
struct TYPE_15__ {TYPE_1__ media; } ;
struct TYPE_11__ {int clientNum; } ;
struct TYPE_12__ {TYPE_2__ ps; } ;

/* Variables and functions */
 TYPE_5__* CG_AllocLocalEntity () ; 
 int /*<<< orphan*/  LE_EXPLOSION ; 
 int /*<<< orphan*/  RF_THIRD_PERSON ; 
 int /*<<< orphan*/  RT_SPRITE ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__ cg ; 
 TYPE_7__ cg_blood ; 
 TYPE_6__ cgs ; 
 int rand () ; 

void CG_Bleed( vec3_t origin, int entityNum ) {
	localEntity_t	*ex;

	if ( !cg_blood.integer ) {
		return;
	}

	ex = CG_AllocLocalEntity();
	ex->leType = LE_EXPLOSION;

	ex->startTime = cg.time;
	ex->endTime = ex->startTime + 500;
	
	VectorCopy ( origin, ex->refEntity.origin);
	ex->refEntity.reType = RT_SPRITE;
	ex->refEntity.rotation = rand() % 360;
	ex->refEntity.radius = 24;

	ex->refEntity.customShader = cgs.media.bloodExplosionShader;

	// don't show player's own blood in view
	if ( entityNum == cg.snap->ps.clientNum ) {
		ex->refEntity.renderfx |= RF_THIRD_PERSON;
	}
}