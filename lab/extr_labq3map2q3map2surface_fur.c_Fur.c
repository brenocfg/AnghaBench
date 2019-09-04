#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numVerts; TYPE_2__* verts; scalar_t__ fur; TYPE_6__* shaderInfo; } ;
typedef  TYPE_1__ mapDrawSurface_t ;
struct TYPE_8__ {int** color; int /*<<< orphan*/  xyz; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ bspDrawVert_t ;
struct TYPE_9__ {int furNumLayers; float furOffset; float furFade; } ;

/* Variables and functions */
 TYPE_1__* CloneSurface (TYPE_1__*,TYPE_6__*) ; 
 int MAX_LIGHTMAPS ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qtrue ; 

void Fur( mapDrawSurface_t *ds ){
	int i, j, k, numLayers;
	float offset, fade, a;
	mapDrawSurface_t    *fur;
	bspDrawVert_t       *dv;


	/* dummy check */
	if ( ds == NULL || ds->fur || ds->shaderInfo->furNumLayers < 1 ) {
		return;
	}

	/* get basic info */
	numLayers = ds->shaderInfo->furNumLayers;
	offset = ds->shaderInfo->furOffset;
	fade = ds->shaderInfo->furFade * 255.0f;

	/* debug code */
	//%	Sys_FPrintf( SYS_VRB, "Fur():  layers: %d  offset: %f   fade: %f  %s\n",
	//%		numLayers, offset, fade, ds->shaderInfo->shader );

	/* initial offset */
	for ( j = 0; j < ds->numVerts; j++ )
	{
		/* get surface vert */
		dv = &ds->verts[ j ];

		/* offset is scaled by original vertex alpha */
		a = (float) dv->color[ 0 ][ 3 ] / 255.0;

		/* offset it */
		VectorMA( dv->xyz, ( offset * a ), dv->normal, dv->xyz );
	}

	/* wash, rinse, repeat */
	for ( i = 1; i < numLayers; i++ )
	{
		/* clone the surface */
		fur = CloneSurface( ds, ds->shaderInfo );
		if ( fur == NULL ) {
			return;
		}

		/* set it to fur */
		fur->fur = qtrue;

		/* walk the verts */
		for ( j = 0; j < fur->numVerts; j++ )
		{
			/* get surface vert */
			dv = &ds->verts[ j ];

			/* offset is scaled by original vertex alpha */
			a = (float) dv->color[ 0 ][ 3 ] / 255.0;

			/* get fur vert */
			dv = &fur->verts[ j ];

			/* offset it */
			VectorMA( dv->xyz, ( offset * a * i ), dv->normal, dv->xyz );

			/* fade alpha */
			for ( k = 0; k < MAX_LIGHTMAPS; k++ )
			{
				a = (float) dv->color[ k ][ 3 ] - fade;
				if ( a > 255.0f ) {
					dv->color[ k ][ 3 ] = 255;
				}
				else if ( a < 0 ) {
					dv->color[ k ][ 3 ] = 0;
				}
				else{
					dv->color[ k ][ 3 ] = a;
				}
			}
		}
	}
}