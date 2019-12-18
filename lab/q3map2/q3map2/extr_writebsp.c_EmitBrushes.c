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
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {size_t firstSide; scalar_t__ numSides; void* shaderNum; } ;
typedef  TYPE_4__ bspBrush_t ;
struct TYPE_14__ {void* shaderNum; int /*<<< orphan*/  planeNum; } ;
typedef  TYPE_5__ bspBrushSide_t ;
struct TYPE_15__ {size_t outputNum; int numsides; TYPE_3__* sides; TYPE_1__* contentShader; struct TYPE_15__* next; } ;
typedef  TYPE_6__ brush_t ;
struct TYPE_12__ {int outputNum; TYPE_2__* shaderInfo; int /*<<< orphan*/  planenum; } ;
struct TYPE_11__ {int /*<<< orphan*/  surfaceFlags; int /*<<< orphan*/  contentFlags; int /*<<< orphan*/ * shader; } ;
struct TYPE_10__ {int /*<<< orphan*/  surfaceFlags; int /*<<< orphan*/  contentFlags; int /*<<< orphan*/ * shader; } ;

/* Variables and functions */
 void* EmitShader (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Error (char*,...) ; 
 size_t MAX_MAP_BRUSHES ; 
 size_t MAX_MAP_BRUSHSIDES ; 
 TYPE_5__* bspBrushSides ; 
 TYPE_4__* bspBrushes ; 
 size_t numBSPBrushSides ; 
 size_t numBSPBrushes ; 

void EmitBrushes( brush_t *brushes, int *firstBrush, int *numBrushes ){
	int j;
	brush_t         *b;
	bspBrush_t      *db;
	bspBrushSide_t  *cp;


	/* set initial brush */
	if ( firstBrush != NULL ) {
		*firstBrush = numBSPBrushes;
	}
	if ( numBrushes != NULL ) {
		*numBrushes = 0;
	}

	/* walk list of brushes */
	for ( b = brushes; b != NULL; b = b->next )
	{
		/* check limits */
		if ( numBSPBrushes == MAX_MAP_BRUSHES ) {
			Error( "MAX_MAP_BRUSHES (%d)", numBSPBrushes );
		}

		/* get bsp brush */
		b->outputNum = numBSPBrushes;
		db = &bspBrushes[ numBSPBrushes ];
		numBSPBrushes++;
		if ( numBrushes != NULL ) {
			( *numBrushes )++;
		}

		db->shaderNum = EmitShader( b->contentShader->shader, &b->contentShader->contentFlags, &b->contentShader->surfaceFlags );
		db->firstSide = numBSPBrushSides;

		/* walk sides */
		db->numSides = 0;
		for ( j = 0; j < b->numsides; j++ )
		{
			/* set output number to bogus initially */
			b->sides[ j ].outputNum = -1;

			/* check count */
			if ( numBSPBrushSides == MAX_MAP_BRUSHSIDES ) {
				Error( "MAX_MAP_BRUSHSIDES " );
			}

			/* emit side */
			b->sides[ j ].outputNum = numBSPBrushSides;
			cp = &bspBrushSides[ numBSPBrushSides ];
			db->numSides++;
			numBSPBrushSides++;
			cp->planeNum = b->sides[ j ].planenum;

			/* emit shader */
			if ( b->sides[ j ].shaderInfo ) {
				cp->shaderNum = EmitShader( b->sides[ j ].shaderInfo->shader, &b->sides[ j ].shaderInfo->contentFlags, &b->sides[ j ].shaderInfo->surfaceFlags );
			}
			else{
				cp->shaderNum = EmitShader( NULL, NULL, NULL );
			}
		}
	}
}