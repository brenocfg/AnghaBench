#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ numbrushes; int /*<<< orphan*/  firstbrush; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HL_CreateMapBrushes (TYPE_1__*,int) ; 
 int /*<<< orphan*/  HL_LoadBSPFile (char*,int,int) ; 
 int /*<<< orphan*/  HL_ParseEntities () ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 int /*<<< orphan*/  MAPTYPE_HALFLIFE ; 
 char* ValueForKey (TYPE_1__*,char*) ; 
 int atoi (char*) ; 
 TYPE_1__* entities ; 
 int /*<<< orphan*/  hl_numclipbrushes ; 
 scalar_t__ lessbrushes ; 
 int /*<<< orphan*/  loadedmaptype ; 
 int /*<<< orphan*/  map_maxs ; 
 int /*<<< orphan*/  map_mins ; 
 int num_entities ; 
 int /*<<< orphan*/  nummapbrushes ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void HL_LoadMapFromBSP(char *filename, int offset, int length)
{
	int i, modelnum;
	char *model, *classname;

	Log_Print("-- HL_LoadMapFromBSP --\n");
	//loaded map type
	loadedmaptype = MAPTYPE_HALFLIFE;
	//
	qprintf("loading map from %s at %d\n", filename, offset);
	//load the Half-Life BSP file
	HL_LoadBSPFile(filename, offset, length);
	//
	hl_numclipbrushes = 0;
	//parse the entities from the BSP
	HL_ParseEntities();
	//clear the map mins and maxs
	ClearBounds(map_mins, map_maxs);
	//
	qprintf("creating Half-Life brushes\n");
	if (lessbrushes) qprintf("creating minimum number of brushes\n");
	else qprintf("placing textures correctly\n");
	//
	for (i = 0; i < num_entities; i++)
	{
		entities[i].firstbrush = nummapbrushes;
		entities[i].numbrushes = 0;
		//
		classname = ValueForKey(&entities[i], "classname");
		if (classname && !strcmp(classname, "worldspawn"))
		{
			modelnum = 0;
		} //end if
		else
		{
			//
			model = ValueForKey(&entities[i], "model");
			if (!model || *model != '*') continue;
			model++;
			modelnum = atoi(model);
		} //end else
		//create map brushes for the entity
		HL_CreateMapBrushes(&entities[i], modelnum);
	} //end for
	//
	qprintf("%5d map brushes\n", nummapbrushes);
	qprintf("%5d clip brushes\n", hl_numclipbrushes);
}