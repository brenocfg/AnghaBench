#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {float* normal; } ;
struct TYPE_8__ {int numPoints; int numIndices; int dlightBits; int ofsIndices; float** points; TYPE_2__ plane; } ;
typedef  TYPE_3__ srfSurfaceFace_t ;
typedef  unsigned int glIndex_t ;
struct TYPE_9__ {int dlightBits; int numVertexes; unsigned int* indexes; int numIndexes; float*** texCoords; int* vertexDlightBits; int /*<<< orphan*/ * vertexColors; int /*<<< orphan*/ * xyz; int /*<<< orphan*/ * normal; TYPE_1__* shader; } ;
struct TYPE_6__ {scalar_t__ needsNormal; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CHECKOVERFLOW (int,int) ; 
 int /*<<< orphan*/  VERTEXSIZE ; 
 int /*<<< orphan*/  VectorCopy (float*,int /*<<< orphan*/ ) ; 
 TYPE_4__ tess ; 

__attribute__((used)) static void RB_SurfaceFace( srfSurfaceFace_t *surf ) {
	int			i;
	unsigned	*indices;
	glIndex_t	*tessIndexes;
	float		*v;
	float		*normal;
	int			ndx;
	int			Bob;
	int			numPoints;
	int			dlightBits;

	RB_CHECKOVERFLOW( surf->numPoints, surf->numIndices );

	dlightBits = surf->dlightBits;
	tess.dlightBits |= dlightBits;

	indices = ( unsigned * ) ( ( ( char  * ) surf ) + surf->ofsIndices );

	Bob = tess.numVertexes;
	tessIndexes = tess.indexes + tess.numIndexes;
	for ( i = surf->numIndices-1 ; i >= 0  ; i-- ) {
		tessIndexes[i] = indices[i] + Bob;
	}

	tess.numIndexes += surf->numIndices;

	numPoints = surf->numPoints;

	if ( tess.shader->needsNormal ) {
		normal = surf->plane.normal;
		for ( i = 0, ndx = tess.numVertexes; i < numPoints; i++, ndx++ ) {
			VectorCopy( normal, tess.normal[ndx] );
		}
	}

	for ( i = 0, v = surf->points[0], ndx = tess.numVertexes; i < numPoints; i++, v += VERTEXSIZE, ndx++ ) {
		VectorCopy( v, tess.xyz[ndx]);
		tess.texCoords[ndx][0][0] = v[3];
		tess.texCoords[ndx][0][1] = v[4];
		tess.texCoords[ndx][1][0] = v[5];
		tess.texCoords[ndx][1][1] = v[6];
		* ( unsigned int * ) &tess.vertexColors[ndx] = * ( unsigned int * ) &v[7];
		tess.vertexDlightBits[ndx] = dlightBits;
	}


	tess.numVertexes += surf->numPoints;
}