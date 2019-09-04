#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ texinfo; int flags; int planenum; int surf; int /*<<< orphan*/  winding; } ;
typedef  TYPE_1__ side_t ;
typedef  int qboolean ;
struct TYPE_12__ {int detail_seperator; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_13__ {int numsides; int testside; int side; TYPE_1__* sides; struct TYPE_13__* next; } ;
typedef  TYPE_3__ bspbrush_t ;
struct TYPE_14__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CheckPlaneAgainstParents (int,TYPE_2__*) ; 
 int /*<<< orphan*/  CheckPlaneAgainstVolume (int,TYPE_2__*) ; 
 int PSIDE_BACK ; 
 int PSIDE_BOTH ; 
 int PSIDE_FACING ; 
 int PSIDE_FRONT ; 
 int SFL_CURVE ; 
 int SFL_TESTED ; 
 int SURF_HINT ; 
 scalar_t__ TEXINFO_NODE ; 
 int TestBrushToPlanenum (TYPE_3__*,int,int*,int*,int*) ; 
 int abs (int) ; 
 int /*<<< orphan*/  c_nonvis ; 
 TYPE_4__* mapplanes ; 
 int numthreads ; 

side_t *SelectSplitSide (bspbrush_t *brushes, node_t *node)
{
	int			value, bestvalue;
	bspbrush_t	*brush, *test;
	side_t		*side, *bestside;
	int			i, pass, numpasses;
	int			pnum;
	int			s;
	int			front, back, both, facing, splits;
	int			bsplits;
	int			epsilonbrush;
	qboolean	hintsplit = false;

	bestside = NULL;
	bestvalue = -99999;

	// the search order goes: visible-structural, visible-detail,
	// nonvisible-structural, nonvisible-detail.
	// If any valid plane is available in a pass, no further
	// passes will be tried.
	numpasses = 2;
	for (pass = 0; pass < numpasses; pass++)
	{
		for (brush = brushes; brush; brush = brush->next)
		{
			// only check detail the second pass
//			if ( (pass & 1) && !(brush->original->contents & CONTENTS_DETAIL) )
//				continue;
//			if ( !(pass & 1) && (brush->original->contents & CONTENTS_DETAIL) )
//				continue;
			for (i = 0; i < brush->numsides; i++)
			{
				side = brush->sides + i;
//				if (side->flags & SFL_BEVEL)
//					continue;	// never use a bevel as a spliter
				if (!side->winding)
					continue;	// nothing visible, so it can't split
				if (side->texinfo == TEXINFO_NODE)
					continue;	// allready a node splitter
				if (side->flags & SFL_TESTED)
					continue;	// we allready have metrics for this plane
//				if (side->surf & SURF_SKIP)
//					continue;	// skip surfaces are never chosen

//				if (!(side->flags & SFL_VISIBLE) && (pass < 2))
//					continue;	// only check visible faces on first pass

				if ((side->flags & SFL_CURVE) && (pass < 1))
					continue;	// only check curves the second pass

				pnum = side->planenum;
				pnum &= ~1;	// allways use positive facing plane

				if (!CheckPlaneAgainstVolume (pnum, node))
					continue;	// would produce a tiny volume

				CheckPlaneAgainstParents (pnum, node);

				front = 0;
				back = 0;
				both = 0;
				facing = 0;
				splits = 0;
				epsilonbrush = 0;

				 //inner loop: optimize
				for (test = brushes; test; test = test->next)
				{
					s = TestBrushToPlanenum (test, pnum, &bsplits, &hintsplit, &epsilonbrush);

					splits += bsplits;
//					if (bsplits && (s&PSIDE_FACING) )
//						Error ("PSIDE_FACING with splits");

					test->testside = s;
					//
					if (s & PSIDE_FACING) facing++;
					if (s & PSIDE_FRONT) front++;
					if (s & PSIDE_BACK) back++;
					if (s == PSIDE_BOTH) both++;
				} //end for

				// give a value estimate for using this plane
				value =  5*facing - 5*splits - abs(front-back);
//					value =  -5*splits;
//					value =  5*facing - 5*splits;
				if (mapplanes[pnum].type < 3)
					value+=5;		// axial is better

				value -= epsilonbrush * 1000;	// avoid!

				// never split a hint side except with another hint
				if (hintsplit && !(side->surf & SURF_HINT) )
					value = -9999999;

				// save off the side test so we don't need
				// to recalculate it when we actually seperate
				// the brushes
				if (value > bestvalue)
				{
					bestvalue = value;
					bestside = side;
					for (test = brushes; test ; test = test->next)
						test->side = test->testside;
				} //end if
			} //end for
		} //end for (brush = brushes;

		// if we found a good plane, don't bother trying any
		// other passes
		if (bestside)
		{
			if (pass > 1)
			{
				if (numthreads == 1) c_nonvis++;
			}
			if (pass > 0) node->detail_seperator = true;	// not needed for vis
			break;
		} //end if
	} //end for (pass = 0;

	//
	// clear all the tested flags we set
	//
	for (brush = brushes ; brush ; brush=brush->next)
	{
		for (i = 0; i < brush->numsides; i++)
		{
			brush->sides[i].flags &= ~SFL_TESTED;
		} //end for
	} //end for

	return bestside;
}