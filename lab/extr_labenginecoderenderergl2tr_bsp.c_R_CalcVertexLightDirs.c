#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_7__ {int surfaceType; int numVerts; TYPE_1__* verts; } ;
typedef  TYPE_2__ srfBspSurface_t ;
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_3__ msurface_t ;
struct TYPE_9__ {int numsurfaces; TYPE_3__* surfaces; } ;
struct TYPE_6__ {int /*<<< orphan*/  lightdir; int /*<<< orphan*/  xyz; int /*<<< orphan*/  normal; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_LightDirForPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  R_VaoPackNormal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_VaoUnpackNormal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SF_FACE 130 
#define  SF_GRID 129 
#define  SF_TRIANGLES 128 
 TYPE_4__ s_worldData ; 

void R_CalcVertexLightDirs( void )
{
	int i, k;
	msurface_t *surface;

	for(k = 0, surface = &s_worldData.surfaces[0]; k < s_worldData.numsurfaces /* s_worldData.numWorldSurfaces */; k++, surface++)
	{
		srfBspSurface_t *bspSurf = (srfBspSurface_t *) surface->data;

		switch(bspSurf->surfaceType)
		{
			case SF_FACE:
			case SF_GRID:
			case SF_TRIANGLES:
				for(i = 0; i < bspSurf->numVerts; i++)
				{
					vec3_t lightDir;
					vec3_t normal;

					R_VaoUnpackNormal(normal, bspSurf->verts[i].normal);
					R_LightDirForPoint( bspSurf->verts[i].xyz, lightDir, normal, &s_worldData );
					R_VaoPackNormal(bspSurf->verts[i].lightdir, lightDir);
				}

				break;

			default:
				break;
		}
	}
}