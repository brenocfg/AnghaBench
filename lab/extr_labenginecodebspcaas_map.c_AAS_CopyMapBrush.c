#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  texinfo; int /*<<< orphan*/  planenum; int /*<<< orphan*/  surf; int /*<<< orphan*/  flags; int /*<<< orphan*/  contents; int /*<<< orphan*/ * winding; int /*<<< orphan*/ * original; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_10__ {int numsides; TYPE_1__* original_sides; int /*<<< orphan*/  contents; scalar_t__ brushnum; int /*<<< orphan*/  entitynum; } ;
typedef  TYPE_2__ mapbrush_t ;
struct TYPE_11__ {int /*<<< orphan*/  numbrushes; scalar_t__ firstbrush; } ;
typedef  TYPE_3__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_MAPFILE_BRUSHES ; 
 size_t MAX_MAPFILE_BRUSHSIDES ; 
 TYPE_1__* brushsides ; 
 TYPE_2__* mapbrushes ; 
 size_t nummapbrushes ; 
 size_t nummapbrushsides ; 

mapbrush_t *AAS_CopyMapBrush(mapbrush_t *brush, entity_t *mapent)
{
	int n;
	mapbrush_t *newbrush;
	side_t *side, *newside;

	if (nummapbrushes >= MAX_MAPFILE_BRUSHES)
		Error ("MAX_MAPFILE_BRUSHES");

	newbrush = &mapbrushes[nummapbrushes];
	newbrush->original_sides = &brushsides[nummapbrushsides];
	newbrush->entitynum = brush->entitynum;
	newbrush->brushnum = nummapbrushes - mapent->firstbrush;
	newbrush->numsides = brush->numsides;
	newbrush->contents = brush->contents;

	//copy the sides
	for (n = 0; n < brush->numsides; n++)
	{
		if (nummapbrushsides >= MAX_MAPFILE_BRUSHSIDES)
			Error ("MAX_MAPFILE_BRUSHSIDES");
		side = brush->original_sides + n;

		newside = newbrush->original_sides + n;
		newside->original = NULL;
		newside->winding = NULL;
		newside->contents = side->contents;
		newside->flags = side->flags;
		newside->surf = side->surf;
		newside->planenum = side->planenum;
		newside->texinfo = side->texinfo;
		nummapbrushsides++;
	} //end for
	//
	nummapbrushes++;
	mapent->numbrushes++;
	return newbrush;
}