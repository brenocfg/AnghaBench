#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_11__ {int numBSPBrushes; int firstBSPBrush; int numBSPSurfaces; int firstBSPSurface; } ;
typedef  TYPE_1__ bspModel_t ;
struct TYPE_12__ {scalar_t__ surfaceType; } ;
typedef  TYPE_2__ bspDrawSurface_t ;
typedef  int /*<<< orphan*/  bspBrush_t ;
struct TYPE_15__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
struct TYPE_14__ {struct TYPE_14__* original; scalar_t__ entityNum; } ;
struct TYPE_13__ {int /*<<< orphan*/ * hash_chain; int /*<<< orphan*/  normal; int /*<<< orphan*/  type; int /*<<< orphan*/  dist; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_4__* AllocBrush (int) ; 
 int /*<<< orphan*/  ConvertBrush (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConvertPatch (int /*<<< orphan*/ *,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MST_PATCH ; 
 int /*<<< orphan*/  PlaneTypeForNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bspBrushes ; 
 TYPE_2__* bspDrawSurfaces ; 
 TYPE_6__* bspPlanes ; 
 TYPE_4__* buildBrush ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_3__* mapplanes ; 
 int numBSPPlanes ; 
 int nummapplanes ; 

__attribute__((used)) static void ConvertModel( FILE *f, bspModel_t *model, int modelNum, vec3_t origin ){
	int i, num;
	bspBrush_t          *brush;
	bspDrawSurface_t    *ds;


	/* convert bsp planes to map planes */
	nummapplanes = numBSPPlanes;
	for ( i = 0; i < numBSPPlanes; i++ )
	{
		VectorCopy( bspPlanes[ i ].normal, mapplanes[ i ].normal );
		mapplanes[ i ].dist = bspPlanes[ i ].dist;
		mapplanes[ i ].type = PlaneTypeForNormal( mapplanes[ i ].normal );
		mapplanes[ i ].hash_chain = NULL;
	}

	/* allocate a build brush */
	buildBrush = AllocBrush( 512 );
	buildBrush->entityNum = 0;
	buildBrush->original = buildBrush;

	/* go through each brush in the model */
	for ( i = 0; i < model->numBSPBrushes; i++ )
	{
		num = i + model->firstBSPBrush;
		brush = &bspBrushes[ num ];
		ConvertBrush( f, num, brush, origin );
	}

	/* free the build brush */
	free( buildBrush );

	/* go through each drawsurf in the model */
	for ( i = 0; i < model->numBSPSurfaces; i++ )
	{
		num = i + model->firstBSPSurface;
		ds = &bspDrawSurfaces[ num ];

		/* we only love patches */
		if ( ds->surfaceType == MST_PATCH ) {
			ConvertPatch( f, num, ds, origin );
		}
	}
}