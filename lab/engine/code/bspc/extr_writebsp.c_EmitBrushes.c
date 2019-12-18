#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec_t ;
typedef  int* vec3_t ;
struct TYPE_9__ {int numsides; TYPE_1__* original_sides; int /*<<< orphan*/ * maxs; int /*<<< orphan*/ * mins; int /*<<< orphan*/  contents; } ;
typedef  TYPE_2__ mapbrush_t ;
struct TYPE_10__ {int planenum; int /*<<< orphan*/  texinfo; } ;
typedef  TYPE_3__ dbrushside_t ;
struct TYPE_11__ {size_t firstside; int numsides; int /*<<< orphan*/  contents; } ;
typedef  TYPE_4__ dbrush_t ;
struct TYPE_8__ {int planenum; int /*<<< orphan*/  texinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int FindFloatPlane (int*,int /*<<< orphan*/ ) ; 
 size_t MAX_MAP_BRUSHSIDES ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int*) ; 
 TYPE_4__* dbrushes ; 
 TYPE_3__* dbrushsides ; 
 TYPE_2__* mapbrushes ; 
 int numbrushes ; 
 size_t numbrushsides ; 
 int nummapbrushes ; 
 int /*<<< orphan*/  vec3_origin ; 

void EmitBrushes (void)
{
	int			i, j, bnum, s, x;
	dbrush_t	*db;
	mapbrush_t		*b;
	dbrushside_t	*cp;
	vec3_t		normal;
	vec_t		dist;
	int			planenum;

	numbrushsides = 0;
	numbrushes = nummapbrushes;

	for (bnum=0 ; bnum<nummapbrushes ; bnum++)
	{
		b = &mapbrushes[bnum];
		db = &dbrushes[bnum];

		db->contents = b->contents;
		db->firstside = numbrushsides;
		db->numsides = b->numsides;
		for (j=0 ; j<b->numsides ; j++)
		{
			if (numbrushsides == MAX_MAP_BRUSHSIDES)
				Error ("MAX_MAP_BRUSHSIDES");
			cp = &dbrushsides[numbrushsides];
			numbrushsides++;
			cp->planenum = b->original_sides[j].planenum;
			cp->texinfo = b->original_sides[j].texinfo;
		}

#ifdef ME
	//for collision detection, bounding boxes are axial :)
	//brushes are convex so just add dot or line touching planes on the sides of
	//the brush parallell to the axis planes
#endif
		// add any axis planes not contained in the brush to bevel off corners
		for (x=0 ; x<3 ; x++)
			for (s=-1 ; s<=1 ; s+=2)
			{
			// add the plane
				VectorCopy (vec3_origin, normal);
				normal[x] = s;
				if (s == -1)
					dist = -b->mins[x];
				else
					dist = b->maxs[x];
				planenum = FindFloatPlane (normal, dist);
				for (i=0 ; i<b->numsides ; i++)
					if (b->original_sides[i].planenum == planenum)
						break;
				if (i == b->numsides)
				{
					if (numbrushsides >= MAX_MAP_BRUSHSIDES)
						Error ("MAX_MAP_BRUSHSIDES");

					dbrushsides[numbrushsides].planenum = planenum;
					dbrushsides[numbrushsides].texinfo =
						dbrushsides[numbrushsides-1].texinfo;
					numbrushsides++;
					db->numsides++;
				}
			}

	}

}