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
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* side; struct TYPE_13__* next; } ;
typedef  TYPE_3__ sideRef_t ;
struct TYPE_14__ {scalar_t__ outputNum; TYPE_2__* shaderInfo; TYPE_3__* sideRef; } ;
typedef  TYPE_4__ mapDrawSurface_t ;
struct TYPE_15__ {int firstDrawSurf; } ;
typedef  TYPE_5__ entity_t ;
struct TYPE_16__ {scalar_t__ surfaceNum; size_t shaderNum; } ;
typedef  TYPE_6__ bspBrushSide_t ;
struct TYPE_17__ {int /*<<< orphan*/  shader; } ;
struct TYPE_12__ {int /*<<< orphan*/  surfaceFlags; int /*<<< orphan*/  contentFlags; int /*<<< orphan*/  shader; } ;
struct TYPE_11__ {size_t outputNum; } ;

/* Variables and functions */
 size_t EmitShader (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_6__* bspBrushSides ; 
 TYPE_8__* bspShaders ; 
 TYPE_4__* mapDrawSurfs ; 
 int numMapDrawSurfs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void FixBrushSides( entity_t *e ){
	int i;
	mapDrawSurface_t    *ds;
	sideRef_t           *sideRef;
	bspBrushSide_t      *side;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- FixBrushSides ---\n" );

	/* walk list of drawsurfaces */
	for ( i = e->firstDrawSurf; i < numMapDrawSurfs; i++ )
	{
		/* get surface and try to early out */
		ds = &mapDrawSurfs[ i ];
		if ( ds->outputNum < 0 ) {
			continue;
		}

		/* walk sideref list */
		for ( sideRef = ds->sideRef; sideRef != NULL; sideRef = sideRef->next )
		{
			/* get bsp brush side */
			if ( sideRef->side == NULL || sideRef->side->outputNum < 0 ) {
				continue;
			}
			side = &bspBrushSides[ sideRef->side->outputNum ];

			/* set drawsurface */
			side->surfaceNum = ds->outputNum;
			//%	Sys_FPrintf( SYS_VRB, "DS: %7d Side: %7d     ", ds->outputNum, sideRef->side->outputNum );

			/* set shader */
			if ( strcmp( bspShaders[ side->shaderNum ].shader, ds->shaderInfo->shader ) ) {
				//%	Sys_FPrintf( SYS_VRB, "Remapping %s to %s\n", bspShaders[ side->shaderNum ].shader, ds->shaderInfo->shader );
				side->shaderNum = EmitShader( ds->shaderInfo->shader, &ds->shaderInfo->contentFlags, &ds->shaderInfo->surfaceFlags );
			}
		}
	}
}