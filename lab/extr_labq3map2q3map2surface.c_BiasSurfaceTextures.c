#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int numVerts; scalar_t__* bias; TYPE_2__* verts; TYPE_1__* shaderInfo; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_7__ {int /*<<< orphan*/ * st; } ;
struct TYPE_6__ {scalar_t__ globalTexture; } ;

/* Variables and functions */
 int /*<<< orphan*/  CalcSurfaceTextureRange (TYPE_3__*) ; 

void BiasSurfaceTextures( mapDrawSurface_t *ds ){
	int i;


	/* calculate the surface texture bias */
	CalcSurfaceTextureRange( ds );

	/* don't bias globaltextured shaders */
	if ( ds->shaderInfo->globalTexture ) {
		return;
	}

	/* bias the texture coordinates */
	for ( i = 0; i < ds->numVerts; i++ )
	{
		ds->verts[ i ].st[ 0 ] += ds->bias[ 0 ];
		ds->verts[ i ].st[ 1 ] += ds->bias[ 1 ];
	}
}