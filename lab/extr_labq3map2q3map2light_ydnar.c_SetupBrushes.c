#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int compileFlags; } ;
typedef  TYPE_1__ shaderInfo_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_11__ {int /*<<< orphan*/  shader; } ;
typedef  TYPE_2__ bspShader_t ;
struct TYPE_12__ {int numSides; int firstSide; } ;
typedef  TYPE_3__ bspBrush_t ;
struct TYPE_13__ {size_t shaderNum; } ;
typedef  TYPE_4__ bspBrushSide_t ;
struct TYPE_14__ {int numBSPBrushes; int firstBSPBrush; } ;

/* Variables and functions */
 int C_TRANSLUCENT ; 
 int /*<<< orphan*/  SYS_VRB ; 
 TYPE_1__* ShaderInfoForShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_4__* bspBrushSides ; 
 TYPE_3__* bspBrushes ; 
 TYPE_6__* bspModels ; 
 TYPE_2__* bspShaders ; 
 int maxOpaqueBrush ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int numBSPBrushes ; 
 scalar_t__ numOpaqueBrushes ; 
 int* opaqueBrushes ; 
 scalar_t__ qtrue ; 
 int* safe_malloc (int) ; 

void SetupBrushes( void ){
	int i, j, b, compileFlags;
	qboolean inside;
	bspBrush_t      *brush;
	bspBrushSide_t  *side;
	bspShader_t     *shader;
	shaderInfo_t    *si;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- SetupBrushes ---\n" );

	/* allocate */
	if ( opaqueBrushes == NULL ) {
		opaqueBrushes = safe_malloc( numBSPBrushes / 8 + 1 );
	}

	/* clear */
	memset( opaqueBrushes, 0, numBSPBrushes / 8 + 1 );
	numOpaqueBrushes = 0;

	/* walk the list of worldspawn brushes */
	for ( i = 0; i < bspModels[ 0 ].numBSPBrushes; i++ )
	{
		/* get brush */
		b = bspModels[ 0 ].firstBSPBrush + i;
		brush = &bspBrushes[ b ];

		/* check all sides */
		inside = qtrue;
		compileFlags = 0;
		for ( j = 0; j < brush->numSides && inside; j++ )
		{
			/* do bsp shader calculations */
			side = &bspBrushSides[ brush->firstSide + j ];
			shader = &bspShaders[ side->shaderNum ];

			/* get shader info */
			si = ShaderInfoForShader( shader->shader );
			if ( si == NULL ) {
				continue;
			}

			/* or together compile flags */
			compileFlags |= si->compileFlags;
		}

		/* determine if this brush is opaque to light */
		if ( !( compileFlags & C_TRANSLUCENT ) ) {
			opaqueBrushes[ b >> 3 ] |= ( 1 << ( b & 7 ) );
			numOpaqueBrushes++;
			maxOpaqueBrush = i;
		}
	}

	/* emit some statistics */
	Sys_FPrintf( SYS_VRB, "%9d opaque brushes\n", numOpaqueBrushes );
}