#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; scalar_t__ backSide; TYPE_1__* shaderInfo; int /*<<< orphan*/ * celShader; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_7__ {char* cloneShader; char* backShader; } ;

/* Variables and functions */
 TYPE_2__* CloneSurface (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeCelSurface (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ NUM_SURFACE_TYPES ; 
 scalar_t__ SURFACE_BAD ; 
 int /*<<< orphan*/  ShaderInfoForShader (char*) ; 
 scalar_t__ qtrue ; 

void FinishSurface( mapDrawSurface_t *ds ){
	mapDrawSurface_t    *ds2;


	/* dummy check */
	if ( ds->type <= SURFACE_BAD || ds->type >= NUM_SURFACE_TYPES || ds == NULL || ds->shaderInfo == NULL ) {
		return;
	}

	/* ydnar: rocking tek-fu celshading */
	if ( ds->celShader != NULL ) {
		MakeCelSurface( ds, ds->celShader );
	}

	/* backsides stop here */
	if ( ds->backSide ) {
		return;
	}

	/* ydnar: rocking surface cloning (fur baby yeah!) */
	if ( ds->shaderInfo->cloneShader != NULL && ds->shaderInfo->cloneShader[ 0 ] != '\0' ) {
		CloneSurface( ds, ShaderInfoForShader( ds->shaderInfo->cloneShader ) );
	}

	/* ydnar: q3map_backShader support */
	if ( ds->shaderInfo->backShader != NULL && ds->shaderInfo->backShader[ 0 ] != '\0' ) {
		ds2 = CloneSurface( ds, ShaderInfoForShader( ds->shaderInfo->backShader ) );
		ds2->backSide = qtrue;
	}
}