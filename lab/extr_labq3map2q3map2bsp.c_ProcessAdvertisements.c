#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numBSPSurfaces; size_t firstBSPSurface; } ;
typedef  TYPE_1__ bspModel_t ;
struct TYPE_8__ {size_t firstVert; scalar_t__ surfaceType; int patchHeight; int numVerts; int patchWidth; } ;
typedef  TYPE_2__ bspDrawSurface_t ;
struct TYPE_10__ {int /*<<< orphan*/  cellId; int /*<<< orphan*/ * rect; int /*<<< orphan*/  normal; int /*<<< orphan*/  model; } ;
struct TYPE_9__ {int /*<<< orphan*/  xyz; int /*<<< orphan*/  normal; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,...) ; 
 int /*<<< orphan*/  IntForKey (int /*<<< orphan*/ *,char*) ; 
 size_t MAX_MAP_ADVERTISEMENTS ; 
 int MAX_QPATH ; 
 scalar_t__ MST_PATCH ; 
 int /*<<< orphan*/  Q_stricmp (char*,char const*) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 char* ValueForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atoi (char const*) ; 
 TYPE_6__* bspAds ; 
 TYPE_2__* bspDrawSurfaces ; 
 TYPE_4__* bspDrawVerts ; 
 TYPE_1__* bspModels ; 
 int /*<<< orphan*/ * entities ; 
 size_t numBSPAds ; 
 int numEntities ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void ProcessAdvertisements( void ) {
	int i;
	const char*         className;
	const char*         modelKey;
	int modelNum;
	bspModel_t*         adModel;
	bspDrawSurface_t*   adSurface;

	Sys_FPrintf( SYS_VRB, "--- ProcessAdvertisements ---\n" );

	for ( i = 0; i < numEntities; i++ ) {

		/* is an advertisement? */
		className = ValueForKey( &entities[ i ], "classname" );

		if ( !Q_stricmp( "advertisement", className ) ) {

			modelKey = ValueForKey( &entities[ i ], "model" );

			if ( strlen( modelKey ) > MAX_QPATH - 1 ) {
				Error( "Model Key for entity exceeds ad struct string length." );
			}
			else {
				if ( numBSPAds < MAX_MAP_ADVERTISEMENTS ) {
					bspAds[numBSPAds].cellId = IntForKey( &entities[ i ], "cellId" );
					strncpy( bspAds[numBSPAds].model, modelKey, sizeof( bspAds[numBSPAds].model ) );

					modelKey++;
					modelNum = atoi( modelKey );
					adModel = &bspModels[modelNum];

					if ( adModel->numBSPSurfaces != 1 ) {
						Error( "Ad cell id %d has more than one surface.", bspAds[numBSPAds].cellId );
					}

					adSurface = &bspDrawSurfaces[adModel->firstBSPSurface];

					// store the normal for use at run time.. all ad verts are assumed to
					// have identical normals (because they should be a simple rectangle)
					// so just use the first vert's normal
					VectorCopy( bspDrawVerts[adSurface->firstVert].normal, bspAds[numBSPAds].normal );

					// store the ad quad for quick use at run time
					if ( adSurface->surfaceType == MST_PATCH ) {
						int v0 = adSurface->firstVert + adSurface->patchHeight - 1;
						int v1 = adSurface->firstVert + adSurface->numVerts - 1;
						int v2 = adSurface->firstVert + adSurface->numVerts - adSurface->patchWidth;
						int v3 = adSurface->firstVert;
						VectorCopy( bspDrawVerts[v0].xyz, bspAds[numBSPAds].rect[0] );
						VectorCopy( bspDrawVerts[v1].xyz, bspAds[numBSPAds].rect[1] );
						VectorCopy( bspDrawVerts[v2].xyz, bspAds[numBSPAds].rect[2] );
						VectorCopy( bspDrawVerts[v3].xyz, bspAds[numBSPAds].rect[3] );
					}
					else {
						Error( "Ad cell %d has an unsupported Ad Surface type.", bspAds[numBSPAds].cellId );
					}

					numBSPAds++;
				}
				else {
					Error( "Maximum number of map advertisements exceeded." );
				}
			}
		}
	}

	Sys_FPrintf( SYS_VRB, "%9d in-game advertisements\n", numBSPAds );
}