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
 int /*<<< orphan*/  Log_Print (char*) ; 
 int /*<<< orphan*/  MAPTYPE_QUAKE1 ; 
 int /*<<< orphan*/  Q1_CreateMapBrushes (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Q1_LoadBSPFile (char*,int,int) ; 
 int /*<<< orphan*/  Q1_ParseEntities () ; 
 char* ValueForKey (TYPE_1__*,char*) ; 
 int atoi (char*) ; 
 TYPE_1__* entities ; 
 scalar_t__ lessbrushes ; 
 int /*<<< orphan*/  loadedmaptype ; 
 int /*<<< orphan*/  map_maxs ; 
 int /*<<< orphan*/  map_mins ; 
 int num_entities ; 
 int /*<<< orphan*/  nummapbrushes ; 
 int /*<<< orphan*/  q1_numclipbrushes ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void Q1_LoadMapFromBSP(char *filename, int offset, int length)
{
	int i, modelnum;
	char *model, *classname;

	Log_Print("-- Q1_LoadMapFromBSP --\n");
	//the loaded map type
	loadedmaptype = MAPTYPE_QUAKE1;
	//
	qprintf("loading map from %s at %d\n", filename, offset);
	//load the Half-Life BSP file
	Q1_LoadBSPFile(filename, offset, length);
	//
	q1_numclipbrushes = 0;
	//CreatePath(path);
	//Q1_CreateQ2WALFiles(path);
	//parse the entities from the BSP
	Q1_ParseEntities();
	//clear the map mins and maxs
	ClearBounds(map_mins, map_maxs);
	//
	qprintf("creating Quake1 brushes\n");
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
		Q1_CreateMapBrushes(&entities[i], modelnum);
	} //end for
	//
	qprintf("%5d map brushes\n", nummapbrushes);
	qprintf("%5d clip brushes\n", q1_numclipbrushes);
}