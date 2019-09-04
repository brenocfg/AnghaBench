#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ refEntity_t ;
struct TYPE_7__ {float light; float startTime; float endTime; int /*<<< orphan*/ * lightColor; TYPE_1__ refEntity; } ;
typedef  TYPE_2__ localEntity_t ;
struct TYPE_8__ {float time; } ;

/* Variables and functions */
 TYPE_4__ cg ; 
 int /*<<< orphan*/  trap_R_AddLightToScene (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_1__*) ; 

__attribute__((used)) static void CG_AddExplosion( localEntity_t *ex ) {
	refEntity_t	*ent;

	ent = &ex->refEntity;

	// add the entity
	trap_R_AddRefEntityToScene(ent);

	// add the dlight
	if ( ex->light ) {
		float		light;

		light = (float)( cg.time - ex->startTime ) / ( ex->endTime - ex->startTime );
		if ( light < 0.5 ) {
			light = 1.0;
		} else {
			light = 1.0 - ( light - 0.5 ) * 2;
		}
		light = ex->light * light;
		trap_R_AddLightToScene(ent->origin, light, ex->lightColor[0], ex->lightColor[1], ex->lightColor[2] );
	}
}