#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_11__ {int planenum; int /*<<< orphan*/  texinfo; } ;
typedef  TYPE_1__ sin_dface_t ;
struct TYPE_12__ {int planenum; int /*<<< orphan*/  texinfo; } ;
typedef  TYPE_2__ sin_dbrushside_t ;
struct TYPE_13__ {int numsides; int firstside; } ;
typedef  TYPE_3__ sin_dbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIN_MAX_MAP_BRUSHSIDES ; 
 int /*<<< orphan*/ * Sin_BrushSideWinding (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ Sin_FaceOnWinding (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ Sin_HintSkipBrush (TYPE_3__*) ; 
 int WE_NOTENOUGHPOINTS ; 
 int WE_POINTBOGUSRANGE ; 
 int WE_SMALLAREA ; 
 int WindingArea (int /*<<< orphan*/ *) ; 
 int WindingError (int /*<<< orphan*/ *) ; 
 scalar_t__ WindingIsTiny (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* sin_dbrushes ; 
 TYPE_2__* sin_dbrushsides ; 
 int* sin_dbrushsidetextured ; 
 TYPE_1__* sin_dfaces ; 
 int sin_numbrushes ; 
 int sin_numfaces ; 

void Sin_FixTextureReferences(void)
{
	int i, j, k, we;
	sin_dbrushside_t *brushside;
	sin_dbrush_t *brush;
	sin_dface_t *face;
	winding_t *w;

	memset(sin_dbrushsidetextured, false, SIN_MAX_MAP_BRUSHSIDES);
	//go over all the brushes
   for (i = 0; i < sin_numbrushes; i++)
   {
		brush = &sin_dbrushes[i];
		//hint brushes are not textured
		if (Sin_HintSkipBrush(brush)) continue;
		//go over all the sides of the brush
		for (j = 0; j < brush->numsides; j++)
		{
			brushside = &sin_dbrushsides[brush->firstside + j];
			//
			w = Sin_BrushSideWinding(brush, brushside);
			if (!w)
			{
				sin_dbrushsidetextured[brush->firstside + j] = true;
				continue;
			} //end if
			else
			{
				//RemoveEqualPoints(w, 0.2);
				if (WindingIsTiny(w))
				{
					FreeWinding(w);
					sin_dbrushsidetextured[brush->firstside + j] = true;
					continue;
				} //end if
				else
				{
					we = WindingError(w);
					if (we == WE_NOTENOUGHPOINTS
						|| we == WE_SMALLAREA
						|| we == WE_POINTBOGUSRANGE
//						|| we == WE_NONCONVEX
						)
					{
						FreeWinding(w);
						sin_dbrushsidetextured[brush->firstside + j] = true;
						continue;
					} //end if
				} //end else
			} //end else
			if (WindingArea(w) < 20)
			{
				sin_dbrushsidetextured[brush->firstside + j] = true;
			} //end if
			//find a face for texturing this brush
			for (k = 0; k < sin_numfaces; k++)
			{
				face = &sin_dfaces[k];
				//if the face is in the same plane as the brush side
				if ((face->planenum&~1) != (brushside->planenum&~1)) continue;
				//if the face is partly or totally on the brush side
				if (Sin_FaceOnWinding(face, w))
				{
					brushside->texinfo = face->texinfo;
					sin_dbrushsidetextured[brush->firstside + j] = true;
					break;
				} //end if
			} //end for
			FreeWinding(w);
		} //end for
	} //end for
}