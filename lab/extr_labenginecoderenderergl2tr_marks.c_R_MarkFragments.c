#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
typedef  scalar_t__ surfaceType_t ;
struct TYPE_9__ {float* xyz; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ srfVert_t ;
struct TYPE_8__ {float* normal; } ;
struct TYPE_10__ {int height; int width; size_t* indexes; int numIndexes; TYPE_3__* verts; TYPE_2__ cullPlane; } ;
typedef  TYPE_4__ srfBspSurface_t ;
typedef  int /*<<< orphan*/  markFragment_t ;
typedef  size_t glIndex_t ;
struct TYPE_12__ {scalar_t__ integer; } ;
struct TYPE_11__ {TYPE_1__* world; int /*<<< orphan*/  viewCount; } ;
struct TYPE_7__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (float* const,float*,float*) ; 
 int /*<<< orphan*/  ClearBounds (float*,float*) ; 
 int /*<<< orphan*/  CrossProduct (float*,float*,float*) ; 
 double DotProduct (float*,float* const) ; 
 int MARKER_OFFSET ; 
 int MAX_VERTS_ON_POLY ; 
 int /*<<< orphan*/  R_AddMarkFragments (int,float***,int,float**,float*,int,float*,int,int /*<<< orphan*/ *,int*,int*,float*,float*) ; 
 int /*<<< orphan*/  R_BoxSurfaces_r (int /*<<< orphan*/ ,float*,float*,scalar_t__**,int,int*,float*) ; 
 int /*<<< orphan*/  R_VaoUnpackNormal (float*,int /*<<< orphan*/ ) ; 
 scalar_t__ SF_FACE ; 
 scalar_t__ SF_GRID ; 
 scalar_t__ SF_TRIANGLES ; 
 int /*<<< orphan*/  VectorAdd (float* const,float* const,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  VectorInverse (float*) ; 
 int /*<<< orphan*/  VectorMA (float* const,int,float*,float*) ; 
 int /*<<< orphan*/  VectorNormalize2 (float* const,float*) ; 
 int /*<<< orphan*/  VectorNormalizeFast (float*) ; 
 int /*<<< orphan*/  VectorSubtract (float* const,float* const,float*) ; 
 TYPE_6__* r_marksOnTriangleMeshes ; 
 TYPE_5__ tr ; 

int R_MarkFragments( int numPoints, const vec3_t *points, const vec3_t projection,
				   int maxPoints, vec3_t pointBuffer, int maxFragments, markFragment_t *fragmentBuffer ) {
	int				numsurfaces, numPlanes;
	int				i, j, k, m, n;
	surfaceType_t	*surfaces[64];
	vec3_t			mins, maxs;
	int				returnedFragments;
	int				returnedPoints;
	vec3_t			normals[MAX_VERTS_ON_POLY+2];
	float			dists[MAX_VERTS_ON_POLY+2];
	vec3_t			clipPoints[2][MAX_VERTS_ON_POLY];
	int				numClipPoints;
	float			*v;
	srfBspSurface_t	*cv;
	glIndex_t		*tri;
	srfVert_t		*dv;
	vec3_t			normal;
	vec3_t			projectionDir;
	vec3_t			v1, v2;

	if (numPoints <= 0) {
		return 0;
	}

	//increment view count for double check prevention
	tr.viewCount++;

	//
	VectorNormalize2( projection, projectionDir );
	// find all the brushes that are to be considered
	ClearBounds( mins, maxs );
	for ( i = 0 ; i < numPoints ; i++ ) {
		vec3_t	temp;

		AddPointToBounds( points[i], mins, maxs );
		VectorAdd( points[i], projection, temp );
		AddPointToBounds( temp, mins, maxs );
		// make sure we get all the leafs (also the one(s) in front of the hit surface)
		VectorMA( points[i], -20, projectionDir, temp );
		AddPointToBounds( temp, mins, maxs );
	}

	if (numPoints > MAX_VERTS_ON_POLY) numPoints = MAX_VERTS_ON_POLY;
	// create the bounding planes for the to be projected polygon
	for ( i = 0 ; i < numPoints ; i++ ) {
		VectorSubtract(points[(i+1)%numPoints], points[i], v1);
		VectorAdd(points[i], projection, v2);
		VectorSubtract(points[i], v2, v2);
		CrossProduct(v1, v2, normals[i]);
		VectorNormalizeFast(normals[i]);
		dists[i] = DotProduct(normals[i], points[i]);
	}
	// add near and far clipping planes for projection
	VectorCopy(projectionDir, normals[numPoints]);
	dists[numPoints] = DotProduct(normals[numPoints], points[0]) - 32;
	VectorCopy(projectionDir, normals[numPoints+1]);
	VectorInverse(normals[numPoints+1]);
	dists[numPoints+1] = DotProduct(normals[numPoints+1], points[0]) - 20;
	numPlanes = numPoints + 2;

	numsurfaces = 0;
	R_BoxSurfaces_r(tr.world->nodes, mins, maxs, surfaces, 64, &numsurfaces, projectionDir);
	//assert(numsurfaces <= 64);
	//assert(numsurfaces != 64);

	returnedPoints = 0;
	returnedFragments = 0;

	for ( i = 0 ; i < numsurfaces ; i++ ) {

		if (*surfaces[i] == SF_GRID) {

			cv = (srfBspSurface_t *) surfaces[i];
			for ( m = 0 ; m < cv->height - 1 ; m++ ) {
				for ( n = 0 ; n < cv->width - 1 ; n++ ) {
					// We triangulate the grid and chop all triangles within
					// the bounding planes of the to be projected polygon.
					// LOD is not taken into account, not such a big deal though.
					//
					// It's probably much nicer to chop the grid itself and deal
					// with this grid as a normal SF_GRID surface so LOD will
					// be applied. However the LOD of that chopped grid must
					// be synced with the LOD of the original curve.
					// One way to do this; the chopped grid shares vertices with
					// the original curve. When LOD is applied to the original
					// curve the unused vertices are flagged. Now the chopped curve
					// should skip the flagged vertices. This still leaves the
					// problems with the vertices at the chopped grid edges.
					//
					// To avoid issues when LOD applied to "hollow curves" (like
					// the ones around many jump pads) we now just add a 2 unit
					// offset to the triangle vertices.
					// The offset is added in the vertex normal vector direction
					// so all triangles will still fit together.
					// The 2 unit offset should avoid pretty much all LOD problems.
					vec3_t fNormal;

					numClipPoints = 3;

					dv = cv->verts + m * cv->width + n;

					VectorCopy(dv[0].xyz, clipPoints[0][0]);
					R_VaoUnpackNormal(fNormal, dv[0].normal);
					VectorMA(clipPoints[0][0], MARKER_OFFSET, fNormal, clipPoints[0][0]);
					VectorCopy(dv[cv->width].xyz, clipPoints[0][1]);
					R_VaoUnpackNormal(fNormal, dv[cv->width].normal);
					VectorMA(clipPoints[0][1], MARKER_OFFSET, fNormal, clipPoints[0][1]);
					VectorCopy(dv[1].xyz, clipPoints[0][2]);
					R_VaoUnpackNormal(fNormal, dv[1].normal);
					VectorMA(clipPoints[0][2], MARKER_OFFSET, fNormal, clipPoints[0][2]);
					// check the normal of this triangle
					VectorSubtract(clipPoints[0][0], clipPoints[0][1], v1);
					VectorSubtract(clipPoints[0][2], clipPoints[0][1], v2);
					CrossProduct(v1, v2, normal);
					VectorNormalizeFast(normal);
					if (DotProduct(normal, projectionDir) < -0.1) {
						// add the fragments of this triangle
						R_AddMarkFragments(numClipPoints, clipPoints,
										   numPlanes, normals, dists,
										   maxPoints, pointBuffer,
										   maxFragments, fragmentBuffer,
										   &returnedPoints, &returnedFragments, mins, maxs);

						if ( returnedFragments == maxFragments ) {
							return returnedFragments;	// not enough space for more fragments
						}
					}

					VectorCopy(dv[1].xyz, clipPoints[0][0]);
					R_VaoUnpackNormal(fNormal, dv[1].normal);
					VectorMA(clipPoints[0][0], MARKER_OFFSET, fNormal, clipPoints[0][0]);
					VectorCopy(dv[cv->width].xyz, clipPoints[0][1]);
					R_VaoUnpackNormal(fNormal, dv[cv->width].normal);
					VectorMA(clipPoints[0][1], MARKER_OFFSET, fNormal, clipPoints[0][1]);
					VectorCopy(dv[cv->width+1].xyz, clipPoints[0][2]);
					R_VaoUnpackNormal(fNormal, dv[cv->width + 1].normal);
					VectorMA(clipPoints[0][2], MARKER_OFFSET, fNormal, clipPoints[0][2]);
					// check the normal of this triangle
					VectorSubtract(clipPoints[0][0], clipPoints[0][1], v1);
					VectorSubtract(clipPoints[0][2], clipPoints[0][1], v2);
					CrossProduct(v1, v2, normal);
					VectorNormalizeFast(normal);
					if (DotProduct(normal, projectionDir) < -0.05) {
						// add the fragments of this triangle
						R_AddMarkFragments(numClipPoints, clipPoints,
										   numPlanes, normals, dists,
										   maxPoints, pointBuffer,
										   maxFragments, fragmentBuffer,
										   &returnedPoints, &returnedFragments, mins, maxs);

						if ( returnedFragments == maxFragments ) {
							return returnedFragments;	// not enough space for more fragments
						}
					}
				}
			}
		}
		else if (*surfaces[i] == SF_FACE) {

			srfBspSurface_t *surf = ( srfBspSurface_t * ) surfaces[i];

			// check the normal of this face
			if (DotProduct(surf->cullPlane.normal, projectionDir) > -0.5) {
				continue;
			}

			for(k = 0, tri = surf->indexes; k < surf->numIndexes; k += 3, tri += 3)
			{
				for(j = 0; j < 3; j++)
				{
					v = surf->verts[tri[j]].xyz;
					VectorMA(v, MARKER_OFFSET, surf->cullPlane.normal, clipPoints[0][j]);
				}

				// add the fragments of this face
				R_AddMarkFragments( 3 , clipPoints,
								   numPlanes, normals, dists,
								   maxPoints, pointBuffer,
								   maxFragments, fragmentBuffer,
								   &returnedPoints, &returnedFragments, mins, maxs);
				if ( returnedFragments == maxFragments ) {
					return returnedFragments;	// not enough space for more fragments
				}
			}
		}
		else if(*surfaces[i] == SF_TRIANGLES && r_marksOnTriangleMeshes->integer) {

			srfBspSurface_t *surf = (srfBspSurface_t *) surfaces[i];

			for(k = 0, tri = surf->indexes; k < surf->numIndexes; k += 3, tri += 3)
			{
				for(j = 0; j < 3; j++)
				{
					vec3_t fNormal;
					v = surf->verts[tri[j]].xyz;
					R_VaoUnpackNormal(fNormal, surf->verts[tri[j]].normal);
					VectorMA(v, MARKER_OFFSET, fNormal, clipPoints[0][j]);
				}

				// add the fragments of this face
				R_AddMarkFragments(3, clipPoints,
								   numPlanes, normals, dists,
								   maxPoints, pointBuffer,
								   maxFragments, fragmentBuffer, &returnedPoints, &returnedFragments, mins, maxs);
				if(returnedFragments == maxFragments)
				{
					return returnedFragments;	// not enough space for more fragments
				}
			}
		}
	}
	return returnedFragments;
}