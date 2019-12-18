#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;
struct TYPE_10__ {scalar_t__ numbrushes; scalar_t__ firstbrush; } ;
typedef  TYPE_2__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_CreateAreaSettings () ; 
 int /*<<< orphan*/  AAS_CreateAreas (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAS_FlipSharedFaces () ; 
 int /*<<< orphan*/  AAS_FreeTmpAAS () ; 
 int /*<<< orphan*/  AAS_GravitationalSubdivision () ; 
 int /*<<< orphan*/  AAS_InitTmpAAS () ; 
 int /*<<< orphan*/  AAS_LadderSubdivision () ; 
 int /*<<< orphan*/  AAS_MeltAreaFaceWindings () ; 
 int /*<<< orphan*/  AAS_MergeAreaFaces () ; 
 int /*<<< orphan*/  AAS_MergeAreaPlaneFaces () ; 
 int /*<<< orphan*/  AAS_MergeAreas () ; 
 int /*<<< orphan*/  AAS_PruneNodes () ; 
 int /*<<< orphan*/  AAS_RemoveAreaFaceColinearPoints () ; 
 int /*<<< orphan*/  AAS_RemoveTinyFaces () ; 
 int /*<<< orphan*/  AAS_StoreFile (char*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  FillOutside (int /*<<< orphan*/ ) ; 
 scalar_t__ FloodEntities (TYPE_1__*) ; 
 double I_FloatTime () ; 
 int /*<<< orphan*/  LeakFile (TYPE_1__*) ; 
 int /*<<< orphan*/  Log_Print (char*,double) ; 
 int /*<<< orphan*/  MakeTreePortals (TYPE_1__*) ; 
 TYPE_1__* ProcessWorldBrushes (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  StripExtension (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ThreadSetDefault () ; 
 int /*<<< orphan*/  Tree_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  Tree_PruneNodes (int /*<<< orphan*/ ) ; 
 scalar_t__ cancelconversion ; 
 TYPE_2__* entities ; 
 size_t entity_num ; 
 scalar_t__ freetree ; 
 int /*<<< orphan*/  source ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void AAS_Create(char *aasfile)
{
	entity_t	*e;
	tree_t *tree;
	double start_time;

	//for a possible leak file
	strcpy(source, aasfile);
	StripExtension(source);
	//the time started
	start_time = I_FloatTime();
	//set the default number of threads (depends on number of processors)
	ThreadSetDefault();
	//set the global entity number to the world model
	entity_num = 0;
	//the world entity
	e = &entities[entity_num];
	//process the whole world
	tree = ProcessWorldBrushes(e->firstbrush, e->firstbrush + e->numbrushes);
	//if the conversion is cancelled
	if (cancelconversion)
	{
		Tree_Free(tree);
		return;
	} //end if
	//display BSP tree creation time
	Log_Print("BSP tree created in %5.0f seconds\n", I_FloatTime() - start_time);
	//prune the bsp tree
	Tree_PruneNodes(tree->headnode);
	//if the conversion is cancelled
	if (cancelconversion)
	{
		Tree_Free(tree);
		return;
	} //end if
	//create the tree portals
	MakeTreePortals(tree);
	//if the conversion is cancelled
	if (cancelconversion)
	{
		Tree_Free(tree);
		return;
	} //end if
	//Marks all nodes that can be reached by entites
	if (FloodEntities(tree))
	{
		//fill out nodes that can't be reached
		FillOutside(tree->headnode);
	} //end if
	else
	{
		LeakFile(tree);
		Error("**** leaked ****\n");
		return;
	} //end else
	//create AAS from the BSP tree
	//==========================================
	//initialize tmp aas
	AAS_InitTmpAAS();
	//create the convex areas from the leaves
	AAS_CreateAreas(tree->headnode);
	//free the BSP tree because it isn't used anymore
	if (freetree) Tree_Free(tree);
	//try to merge area faces
	AAS_MergeAreaFaces();
	//do gravitational subdivision
	AAS_GravitationalSubdivision();
	//merge faces if possible
	AAS_MergeAreaFaces();
	AAS_RemoveAreaFaceColinearPoints();
	//merge areas if possible
	AAS_MergeAreas();
	//NOTE: prune nodes directly after area merging
	AAS_PruneNodes();
	//flip shared faces so they are all facing to the same area
	AAS_FlipSharedFaces();
	AAS_RemoveAreaFaceColinearPoints();
	//merge faces if possible
	AAS_MergeAreaFaces();
	//merge area faces in the same plane
	AAS_MergeAreaPlaneFaces();
	//do ladder subdivision
	AAS_LadderSubdivision();
	//FIXME: melting is buggy
	AAS_MeltAreaFaceWindings();
	//remove tiny faces
	AAS_RemoveTinyFaces();
	//create area settings
	AAS_CreateAreaSettings();
	//check if the winding plane is equal to the face plane
	//AAS_CheckAreaWindingPlanes();
	//
	//AAS_CheckSharedFaces();
	//==========================================
	//if the conversion is cancelled
	if (cancelconversion)
	{
		Tree_Free(tree);
		AAS_FreeTmpAAS();
		return;
	} //end if
	//store the created AAS stuff in the AAS file format and write the file
	AAS_StoreFile(aasfile);
	//free the temporary AAS memory
	AAS_FreeTmpAAS();
	//display creation time
	Log_Print("\nAAS created in %5.0f seconds\n", I_FloatTime() - start_time);
}