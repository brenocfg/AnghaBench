#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  surfaceType_t ;
struct TYPE_11__ {void** normal; void** color; void** origin; int /*<<< orphan*/  surfaceType; } ;
typedef  TYPE_2__ srfFlare_t ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct TYPE_12__ {TYPE_1__ cullinfo; int /*<<< orphan*/ * data; TYPE_7__* shader; scalar_t__ fogIndex; } ;
typedef  TYPE_3__ msurface_t ;
struct TYPE_13__ {int /*<<< orphan*/ ** lightmapVecs; int /*<<< orphan*/ * lightmapOrigin; int /*<<< orphan*/  shaderNum; int /*<<< orphan*/  fogNum; } ;
typedef  TYPE_4__ dsurface_t ;
typedef  int /*<<< orphan*/  drawVert_t ;
struct TYPE_16__ {int /*<<< orphan*/  isSky; } ;
struct TYPE_15__ {scalar_t__ integer; } ;
struct TYPE_14__ {TYPE_7__* defaultShader; } ;

/* Variables and functions */
 int /*<<< orphan*/  CULLINFO_NONE ; 
 int /*<<< orphan*/  LIGHTMAP_BY_VERTEX ; 
 void* LittleFloat (int /*<<< orphan*/ ) ; 
 scalar_t__ LittleLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SF_FLARE ; 
 TYPE_7__* ShaderForShaderNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* r_singleShader ; 
 TYPE_5__ tr ; 

__attribute__((used)) static void ParseFlare( dsurface_t *ds, drawVert_t *verts, msurface_t *surf, int *indexes ) {
	srfFlare_t		*flare;
	int				i;

	// get fog volume
	surf->fogIndex = LittleLong( ds->fogNum ) + 1;

	// get shader
	surf->shader = ShaderForShaderNum( ds->shaderNum, LIGHTMAP_BY_VERTEX );
	if ( r_singleShader->integer && !surf->shader->isSky ) {
		surf->shader = tr.defaultShader;
	}

	//flare = ri.Hunk_Alloc( sizeof( *flare ), h_low );
	flare = (void *)surf->data;
	flare->surfaceType = SF_FLARE;

	surf->data = (surfaceType_t *)flare;

	for ( i = 0 ; i < 3 ; i++ ) {
		flare->origin[i] = LittleFloat( ds->lightmapOrigin[i] );
		flare->color[i] = LittleFloat( ds->lightmapVecs[0][i] );
		flare->normal[i] = LittleFloat( ds->lightmapVecs[2][i] );
	}

	surf->cullinfo.type = CULLINFO_NONE;
}