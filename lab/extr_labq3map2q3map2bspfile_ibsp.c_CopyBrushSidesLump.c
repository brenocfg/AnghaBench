#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ibspHeader_t ;
struct TYPE_5__ {int /*<<< orphan*/  shaderNum; int /*<<< orphan*/  planeNum; } ;
typedef  TYPE_1__ ibspBrushSide_t ;
typedef  int /*<<< orphan*/  bspHeader_t ;
struct TYPE_6__ {int surfaceNum; int /*<<< orphan*/  shaderNum; int /*<<< orphan*/  planeNum; } ;
typedef  TYPE_2__ bspBrushSide_t ;

/* Variables and functions */
 TYPE_1__* GetLump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetLumpElements (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LUMP_BRUSHSIDES ; 
 TYPE_2__* bspBrushSides ; 
 int numBSPBrushSides ; 

__attribute__((used)) static void CopyBrushSidesLump( ibspHeader_t *header ){
	int i;
	ibspBrushSide_t *in;
	bspBrushSide_t  *out;


	/* get count */
	numBSPBrushSides = GetLumpElements( (bspHeader_t*) header, LUMP_BRUSHSIDES, sizeof( *in ) );

	/* copy */
	in = GetLump( (bspHeader_t*) header, LUMP_BRUSHSIDES );
	out = bspBrushSides;
	for ( i = 0; i < numBSPBrushSides; i++ )
	{
		out->planeNum = in->planeNum;
		out->shaderNum = in->shaderNum;
		out->surfaceNum = -1;
		in++;
		out++;
	}
}