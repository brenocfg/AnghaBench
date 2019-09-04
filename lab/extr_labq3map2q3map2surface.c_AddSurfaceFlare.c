#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_7__ {int numVerts; TYPE_2__* shaderInfo; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  entityNum; TYPE_1__* verts; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_6__ {int /*<<< orphan*/  lightStyle; int /*<<< orphan*/  flareShader; int /*<<< orphan*/  color; } ;
struct TYPE_5__ {int /*<<< orphan*/ * xyz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DrawSurfaceForFlare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ *,float,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ *,float,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AddSurfaceFlare( mapDrawSurface_t *ds, vec3_t entityOrigin ){
	vec3_t origin;
	int i;


	/* find centroid */
	VectorClear( origin );
	for ( i = 0; i < ds->numVerts; i++ )
		VectorAdd( origin, ds->verts[ i ].xyz, origin );
	VectorScale( origin, ( 1.0f / ds->numVerts ), origin );
	if ( entityOrigin != NULL ) {
		VectorAdd( origin, entityOrigin, origin );
	}

	/* push origin off surface a bit */
	VectorMA( origin, 2.0f,  ds->lightmapVecs[ 2 ], origin );

	/* create the drawsurface */
	DrawSurfaceForFlare( ds->entityNum, origin, ds->lightmapVecs[ 2 ], ds->shaderInfo->color, ds->shaderInfo->flareShader, ds->shaderInfo->lightStyle );
}