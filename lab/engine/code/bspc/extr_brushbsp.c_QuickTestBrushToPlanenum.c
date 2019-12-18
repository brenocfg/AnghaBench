#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; scalar_t__ dist; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_9__ {scalar_t__* mins; scalar_t__* maxs; int numsides; TYPE_1__* sides; } ;
typedef  TYPE_3__ bspbrush_t ;
struct TYPE_7__ {int planenum; } ;

/* Variables and functions */
 int BoxOnPlaneSide (scalar_t__*,scalar_t__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_MAPFILE_PLANES ; 
 scalar_t__ PLANESIDE_EPSILON ; 
 int PSIDE_BACK ; 
 int PSIDE_BOTH ; 
 int PSIDE_FACING ; 
 int PSIDE_FRONT ; 
 TYPE_2__* mapplanes ; 

int QuickTestBrushToPlanenum (bspbrush_t *brush, int planenum, int *numsplits)
{
	int i, num;
	plane_t *plane;
	int s;

	*numsplits = 0;

	plane = &mapplanes[planenum];

#ifdef ME
	//fast axial cases
	if (plane->type < 3)
	{
		if (plane->dist + PLANESIDE_EPSILON < brush->mins[plane->type])
			return PSIDE_FRONT;
		if (plane->dist - PLANESIDE_EPSILON > brush->maxs[plane->type])
			return PSIDE_BACK;
	} //end if
#endif //ME*/

	// if the brush actually uses the planenum,
	// we can tell the side for sure
	for (i = 0; i < brush->numsides; i++)
	{
		num = brush->sides[i].planenum;
		if (num >= MAX_MAPFILE_PLANES)
			Error ("bad planenum");
		if (num == planenum)
			return PSIDE_BACK|PSIDE_FACING;
		if (num == (planenum ^ 1) )
			return PSIDE_FRONT|PSIDE_FACING;

	}

	// box on plane side
	s = BoxOnPlaneSide (brush->mins, brush->maxs, plane);

	// if both sides, count the visible faces split
	if (s == PSIDE_BOTH)
	{
		*numsplits += 3;
	}

	return s;
}