#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {TYPE_2__* headnode; } ;
typedef  TYPE_1__ tree_t ;
struct TYPE_29__ {TYPE_4__* brushlist; int /*<<< orphan*/  planenum; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_30__ {TYPE_4__* brushes; int /*<<< orphan*/  numBrushes; int /*<<< orphan*/  firstBrush; int /*<<< orphan*/  firstDrawSurf; } ;
typedef  TYPE_3__ entity_t ;
struct TYPE_31__ {struct TYPE_31__* next; } ;
typedef  TYPE_4__ brush_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddEntitySurfaceModels (TYPE_3__*) ; 
 int /*<<< orphan*/  AddTriangleModels (TYPE_3__*) ; 
 TYPE_2__* AllocNode () ; 
 TYPE_1__* AllocTree () ; 
 int /*<<< orphan*/  BeginModel () ; 
 int /*<<< orphan*/  ClassifyEntitySurfaces (TYPE_3__*) ; 
 int /*<<< orphan*/  ClearMetaTriangles () ; 
 int /*<<< orphan*/  ClipSidesIntoTree (TYPE_3__*,TYPE_1__*) ; 
 TYPE_4__* CopyBrush (TYPE_4__*) ; 
 int /*<<< orphan*/  EmitBrushes (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndModel (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  FilterDrawsurfsIntoTree (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FixBrushSides (TYPE_3__*) ; 
 int /*<<< orphan*/  FixMetaTJunctions () ; 
 int /*<<< orphan*/  FixTJunctions (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeTree (TYPE_1__*) ; 
 int /*<<< orphan*/  MakeEntityDecals (TYPE_3__*) ; 
 int /*<<< orphan*/  MakeEntityMetaTriangles (TYPE_3__*) ; 
 int /*<<< orphan*/  MergeMetaTriangles () ; 
 int /*<<< orphan*/  PLANENUM_LEAF ; 
 int /*<<< orphan*/  PatchMapDrawSurfs (TYPE_3__*) ; 
 int /*<<< orphan*/  SmoothMetaTriangles () ; 
 int /*<<< orphan*/  SubdivideFaceSurfaces (TYPE_3__*,TYPE_1__*) ; 
 TYPE_3__* entities ; 
 size_t mapEntityNum ; 
 int /*<<< orphan*/  nosubdivide ; 
 int /*<<< orphan*/  notjunc ; 
 int /*<<< orphan*/  numMapDrawSurfs ; 

void ProcessSubModel( void ){
	entity_t    *e;
	tree_t      *tree;
	brush_t     *b, *bc;
	node_t      *node;


	/* start a brush model */
	BeginModel();
	e = &entities[ mapEntityNum ];
	e->firstDrawSurf = numMapDrawSurfs;

	/* ydnar: gs mods */
	ClearMetaTriangles();

	/* check for patches with adjacent edges that need to lod together */
	PatchMapDrawSurfs( e );

	/* allocate a tree */
	node = AllocNode();
	node->planenum = PLANENUM_LEAF;
	tree = AllocTree();
	tree->headnode = node;

	/* add the sides to the tree */
	ClipSidesIntoTree( e, tree );

	/* ydnar: create drawsurfs for triangle models */
	AddTriangleModels( e );

	/* create drawsurfs for surface models */
	AddEntitySurfaceModels( e );

	/* generate bsp brushes from map brushes */
	EmitBrushes( e->brushes, &e->firstBrush, &e->numBrushes );

	/* just put all the brushes in headnode */
	for ( b = e->brushes; b; b = b->next )
	{
		bc = CopyBrush( b );
		bc->next = node->brushlist;
		node->brushlist = bc;
	}

	/* subdivide each drawsurf as required by shader tesselation */
	if ( !nosubdivide ) {
		SubdivideFaceSurfaces( e, tree );
	}

	/* add in any vertexes required to fix t-junctions */
	if ( !notjunc ) {
		FixTJunctions( e );
	}

	/* ydnar: classify the surfaces and project lightmaps */
	ClassifyEntitySurfaces( e );

	/* ydnar: project decals */
	MakeEntityDecals( e );

	/* ydnar: meta surfaces */
	MakeEntityMetaTriangles( e );
	SmoothMetaTriangles();
	FixMetaTJunctions();
	MergeMetaTriangles();

	/* add references to the final drawsurfs in the apropriate clusters */
	FilterDrawsurfsIntoTree( e, tree );

	/* match drawsurfaces back to original brushsides (sof2) */
	FixBrushSides( e );

	/* finish */
	EndModel( e, node );
	FreeTree( tree );
}