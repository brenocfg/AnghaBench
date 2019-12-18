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
struct TYPE_5__ {int flags; size_t planenum; int /*<<< orphan*/  winding; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_6__ {int numsides; int /*<<< orphan*/  brushnum; TYPE_1__* original_sides; } ;
typedef  TYPE_2__ mapbrush_t ;
struct TYPE_7__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  Log_Write (char*,int /*<<< orphan*/ ,...) ; 
 int SFL_BEVEL ; 
 int SFL_VISIBLE ; 
 int WE_NOTENOUGHPOINTS ; 
 int WE_POINTBOGUSRANGE ; 
 int WE_SMALLAREA ; 
 int WindingError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WindingErrorString () ; 
 scalar_t__ WindingIsTiny (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_boxbevels ; 
 int /*<<< orphan*/  c_edgebevels ; 
 TYPE_3__* mapplanes ; 
 size_t nummapplanes ; 

void MarkBrushBevels(mapbrush_t *brush)
{
	int i;
	int we;
	side_t *s;

	//check all the sides of the brush
	for (i = 0; i < brush->numsides; i++)
	{
		s = brush->original_sides + i;
		//if the side has no winding
		if (!s->winding)
		{
			Log_Write("MarkBrushBevels: brush %d no winding", brush->brushnum);
			s->flags |= SFL_BEVEL;
		} //end if
		//if the winding is tiny
		else if (WindingIsTiny(s->winding))
		{
			s->flags |= SFL_BEVEL;
			Log_Write("MarkBrushBevels: brush %d tiny winding", brush->brushnum);
		} //end else if
		//if the winding has errors
		else
		{
			we = WindingError(s->winding);
			if (we == WE_NOTENOUGHPOINTS
					|| we == WE_SMALLAREA
					|| we == WE_POINTBOGUSRANGE
//					|| we == WE_NONCONVEX
					)
			{
				Log_Write("MarkBrushBevels: brush %d %s", brush->brushnum, WindingErrorString());
				s->flags |= SFL_BEVEL;
			} //end else if
		} //end else
		if (s->flags & SFL_BEVEL)
		{
			s->flags &= ~SFL_VISIBLE;
			//if the side has a valid plane
			if (s->planenum > 0 && s->planenum < nummapplanes)
			{
				//if it is an axial plane
				if (mapplanes[s->planenum].type < 3) c_boxbevels++;
				else c_edgebevels++;
			} //end if
		} //end if
	} //end for
}