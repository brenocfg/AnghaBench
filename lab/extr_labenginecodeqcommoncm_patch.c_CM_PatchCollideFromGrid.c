#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int numPlanes; size_t numFacets; void* planes; void* facets; } ;
typedef  TYPE_1__ patchCollide_t ;
struct TYPE_16__ {int surfacePlane; int numBorders; int* borderPlanes; int* borderNoAdjust; } ;
typedef  TYPE_2__ facet_t ;
struct TYPE_17__ {int width; int height; float*** points; scalar_t__ wrapWidth; scalar_t__ wrapHeight; } ;
typedef  TYPE_3__ cGrid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM_AddFacetBevels (TYPE_2__*) ; 
 void* CM_EdgePlaneNum (TYPE_3__*,int***,int,int,int) ; 
 int CM_FindPlane (float*,float*,float*) ; 
 int /*<<< orphan*/  CM_SetBorderInward (TYPE_2__*,TYPE_3__*,int***,int,int,int) ; 
 scalar_t__ CM_ValidateFacet (TYPE_2__*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Memcpy (void*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 size_t EN_BOTTOM ; 
 size_t EN_LEFT ; 
 size_t EN_RIGHT ; 
 size_t EN_TOP ; 
 int /*<<< orphan*/  ERR_DROP ; 
 void* Hunk_Alloc (int,int /*<<< orphan*/ ) ; 
 size_t MAX_FACETS ; 
 int MAX_GRID_SIZE ; 
 TYPE_2__* facets ; 
 int /*<<< orphan*/  h_high ; 
 size_t numFacets ; 
 int numPlanes ; 
 TYPE_2__* planes ; 

__attribute__((used)) static void CM_PatchCollideFromGrid( cGrid_t *grid, patchCollide_t *pf ) {
	int				i, j;
	float			*p1, *p2, *p3;
	int				gridPlanes[MAX_GRID_SIZE][MAX_GRID_SIZE][2];
	facet_t			*facet;
	int				borders[4];
	int				noAdjust[4];

	numPlanes = 0;
	numFacets = 0;

	// find the planes for each triangle of the grid
	for ( i = 0 ; i < grid->width - 1 ; i++ ) {
		for ( j = 0 ; j < grid->height - 1 ; j++ ) {
			p1 = grid->points[i][j];
			p2 = grid->points[i+1][j];
			p3 = grid->points[i+1][j+1];
			gridPlanes[i][j][0] = CM_FindPlane( p1, p2, p3 );

			p1 = grid->points[i+1][j+1];
			p2 = grid->points[i][j+1];
			p3 = grid->points[i][j];
			gridPlanes[i][j][1] = CM_FindPlane( p1, p2, p3 );
		}
	}

	// create the borders for each facet
	for ( i = 0 ; i < grid->width - 1 ; i++ ) {
		for ( j = 0 ; j < grid->height - 1 ; j++ ) {
			 
			borders[EN_TOP] = -1;
			if ( j > 0 ) {
				borders[EN_TOP] = gridPlanes[i][j-1][1];
			} else if ( grid->wrapHeight ) {
				borders[EN_TOP] = gridPlanes[i][grid->height-2][1];
			} 
			noAdjust[EN_TOP] = ( borders[EN_TOP] == gridPlanes[i][j][0] );
			if ( borders[EN_TOP] == -1 || noAdjust[EN_TOP] ) {
				borders[EN_TOP] = CM_EdgePlaneNum( grid, gridPlanes, i, j, 0 );
			}

			borders[EN_BOTTOM] = -1;
			if ( j < grid->height - 2 ) {
				borders[EN_BOTTOM] = gridPlanes[i][j+1][0];
			} else if ( grid->wrapHeight ) {
				borders[EN_BOTTOM] = gridPlanes[i][0][0];
			}
			noAdjust[EN_BOTTOM] = ( borders[EN_BOTTOM] == gridPlanes[i][j][1] );
			if ( borders[EN_BOTTOM] == -1 || noAdjust[EN_BOTTOM] ) {
				borders[EN_BOTTOM] = CM_EdgePlaneNum( grid, gridPlanes, i, j, 2 );
			}

			borders[EN_LEFT] = -1;
			if ( i > 0 ) {
				borders[EN_LEFT] = gridPlanes[i-1][j][0];
			} else if ( grid->wrapWidth ) {
				borders[EN_LEFT] = gridPlanes[grid->width-2][j][0];
			}
			noAdjust[EN_LEFT] = ( borders[EN_LEFT] == gridPlanes[i][j][1] );
			if ( borders[EN_LEFT] == -1 || noAdjust[EN_LEFT] ) {
				borders[EN_LEFT] = CM_EdgePlaneNum( grid, gridPlanes, i, j, 3 );
			}

			borders[EN_RIGHT] = -1;
			if ( i < grid->width - 2 ) {
				borders[EN_RIGHT] = gridPlanes[i+1][j][1];
			} else if ( grid->wrapWidth ) {
				borders[EN_RIGHT] = gridPlanes[0][j][1];
			}
			noAdjust[EN_RIGHT] = ( borders[EN_RIGHT] == gridPlanes[i][j][0] );
			if ( borders[EN_RIGHT] == -1 || noAdjust[EN_RIGHT] ) {
				borders[EN_RIGHT] = CM_EdgePlaneNum( grid, gridPlanes, i, j, 1 );
			}

			if ( numFacets == MAX_FACETS ) {
				Com_Error( ERR_DROP, "MAX_FACETS" );
			}
			facet = &facets[numFacets];
			Com_Memset( facet, 0, sizeof( *facet ) );

			if ( gridPlanes[i][j][0] == gridPlanes[i][j][1] ) {
				if ( gridPlanes[i][j][0] == -1 ) {
					continue;		// degenrate
				}
				facet->surfacePlane = gridPlanes[i][j][0];
				facet->numBorders = 4;
				facet->borderPlanes[0] = borders[EN_TOP];
				facet->borderNoAdjust[0] = noAdjust[EN_TOP];
				facet->borderPlanes[1] = borders[EN_RIGHT];
				facet->borderNoAdjust[1] = noAdjust[EN_RIGHT];
				facet->borderPlanes[2] = borders[EN_BOTTOM];
				facet->borderNoAdjust[2] = noAdjust[EN_BOTTOM];
				facet->borderPlanes[3] = borders[EN_LEFT];
				facet->borderNoAdjust[3] = noAdjust[EN_LEFT];
				CM_SetBorderInward( facet, grid, gridPlanes, i, j, -1 );
				if ( CM_ValidateFacet( facet ) ) {
					CM_AddFacetBevels( facet );
					numFacets++;
				}
			} else {
				// two separate triangles
				facet->surfacePlane = gridPlanes[i][j][0];
				facet->numBorders = 3;
				facet->borderPlanes[0] = borders[EN_TOP];
				facet->borderNoAdjust[0] = noAdjust[EN_TOP];
				facet->borderPlanes[1] = borders[EN_RIGHT];
				facet->borderNoAdjust[1] = noAdjust[EN_RIGHT];
				facet->borderPlanes[2] = gridPlanes[i][j][1];
				if ( facet->borderPlanes[2] == -1 ) {
					facet->borderPlanes[2] = borders[EN_BOTTOM];
					if ( facet->borderPlanes[2] == -1 ) {
						facet->borderPlanes[2] = CM_EdgePlaneNum( grid, gridPlanes, i, j, 4 );
					}
				}
 				CM_SetBorderInward( facet, grid, gridPlanes, i, j, 0 );
				if ( CM_ValidateFacet( facet ) ) {
					CM_AddFacetBevels( facet );
					numFacets++;
				}

				if ( numFacets == MAX_FACETS ) {
					Com_Error( ERR_DROP, "MAX_FACETS" );
				}
				facet = &facets[numFacets];
				Com_Memset( facet, 0, sizeof( *facet ) );

				facet->surfacePlane = gridPlanes[i][j][1];
				facet->numBorders = 3;
				facet->borderPlanes[0] = borders[EN_BOTTOM];
				facet->borderNoAdjust[0] = noAdjust[EN_BOTTOM];
				facet->borderPlanes[1] = borders[EN_LEFT];
				facet->borderNoAdjust[1] = noAdjust[EN_LEFT];
				facet->borderPlanes[2] = gridPlanes[i][j][0];
				if ( facet->borderPlanes[2] == -1 ) {
					facet->borderPlanes[2] = borders[EN_TOP];
					if ( facet->borderPlanes[2] == -1 ) {
						facet->borderPlanes[2] = CM_EdgePlaneNum( grid, gridPlanes, i, j, 5 );
					}
				}
				CM_SetBorderInward( facet, grid, gridPlanes, i, j, 1 );
				if ( CM_ValidateFacet( facet ) ) {
					CM_AddFacetBevels( facet );
					numFacets++;
				}
			}
		}
	}

	// copy the results out
	pf->numPlanes = numPlanes;
	pf->numFacets = numFacets;
	pf->facets = Hunk_Alloc( numFacets * sizeof( *pf->facets ), h_high );
	Com_Memcpy( pf->facets, facets, numFacets * sizeof( *pf->facets ) );
	pf->planes = Hunk_Alloc( numPlanes * sizeof( *pf->planes ), h_high );
	Com_Memcpy( pf->planes, planes, numPlanes * sizeof( *pf->planes ) );
}