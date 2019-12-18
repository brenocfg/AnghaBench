#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_4__ {int numBSPSurfaces; int firstBSPSurface; } ;
typedef  TYPE_1__ bspModel_t ;
typedef  int /*<<< orphan*/  bspDrawSurface_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertSurface (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bspDrawSurfaces ; 

__attribute__((used)) static void ConvertModel( FILE *f, bspModel_t *model, int modelNum, vec3_t origin ){
	int i, s;
	bspDrawSurface_t    *ds;


	/* go through each drawsurf in the model */
	for ( i = 0; i < model->numBSPSurfaces; i++ )
	{
		s = i + model->firstBSPSurface;
		ds = &bspDrawSurfaces[ s ];
		ConvertSurface( f, model, modelNum, ds, s, origin );
	}
}