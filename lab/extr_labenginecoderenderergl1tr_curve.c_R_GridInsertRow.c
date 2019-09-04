#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_12__ {int width; int height; float* heightLodError; float* widthLodError; float lodRadius; int /*<<< orphan*/  lodOrigin; TYPE_2__* verts; } ;
typedef  TYPE_1__ srfGridMesh_t ;
struct TYPE_13__ {int /*<<< orphan*/  xyz; } ;
typedef  TYPE_2__ drawVert_t ;

/* Variables and functions */
 int /*<<< orphan*/  LerpDrawVert (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int MAX_GRID_SIZE ; 
 int /*<<< orphan*/  MakeMeshNormals (int,int,TYPE_2__**) ; 
 TYPE_1__* R_CreateSurfaceGridMesh (int,int,TYPE_2__**,float**) ; 
 int /*<<< orphan*/  R_FreeSurfaceGridMesh (TYPE_1__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

srfGridMesh_t *R_GridInsertRow( srfGridMesh_t *grid, int row, int column, vec3_t point, float loderror ) {
	int i, j;
	int width, height, oldheight;
	drawVert_t ctrl[MAX_GRID_SIZE][MAX_GRID_SIZE];
	float errorTable[2][MAX_GRID_SIZE];
	float lodRadius;
	vec3_t lodOrigin;

	oldheight = 0;
	width = grid->width;
	height = grid->height + 1;
	if (height > MAX_GRID_SIZE)
		return NULL;
	for (i = 0; i < height; i++) {
		if (i == row) {
			//insert new row
			for (j = 0; j < grid->width; j++) {
				LerpDrawVert( &grid->verts[(i-1) * grid->width + j], &grid->verts[i * grid->width + j], &ctrl[i][j] );
				if (j == column)
					VectorCopy(point, ctrl[i][j].xyz);
			}
			errorTable[1][i] = loderror;
			continue;
		}
		errorTable[1][i] = grid->heightLodError[oldheight];
		for (j = 0; j < grid->width; j++) {
			ctrl[i][j] = grid->verts[oldheight * grid->width + j];
		}
		oldheight++;
	}
	for (j = 0; j < grid->width; j++) {
		errorTable[0][j] = grid->widthLodError[j];
	}
	// put all the aproximating points on the curve
	//PutPointsOnCurve( ctrl, width, height );
	// calculate normals
	MakeMeshNormals( width, height, ctrl );

	VectorCopy(grid->lodOrigin, lodOrigin);
	lodRadius = grid->lodRadius;
	// free the old grid
	R_FreeSurfaceGridMesh(grid);
	// create a new grid
	grid = R_CreateSurfaceGridMesh( width, height, ctrl, errorTable );
	grid->lodRadius = lodRadius;
	VectorCopy(lodOrigin, grid->lodOrigin);
	return grid;
}