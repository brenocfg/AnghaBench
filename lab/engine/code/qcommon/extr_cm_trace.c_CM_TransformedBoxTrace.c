#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  double* vec3_t ;
struct TYPE_7__ {double* normal; } ;
struct TYPE_8__ {double fraction; double* endpos; TYPE_1__ plane; } ;
typedef  TYPE_2__ trace_t ;
struct TYPE_9__ {int use; float radius; float halfheight; double* offset; } ;
typedef  TYPE_3__ sphere_t ;
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  clipHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BOX_MODEL_HANDLE ; 
 int /*<<< orphan*/  CM_Trace (TYPE_2__*,double*,double*,double*,double*,int /*<<< orphan*/ ,double* const,int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  CreateRotationMatrix (double* const,double**) ; 
 int /*<<< orphan*/  RotatePoint (double*,double**) ; 
 int /*<<< orphan*/  TransposeMatrix (double**,double**) ; 
 int /*<<< orphan*/  VectorSet (double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  VectorSubtract (double*,double* const,double*) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 double* vec3_origin ; 

void CM_TransformedBoxTrace( trace_t *results, const vec3_t start, const vec3_t end,
						  vec3_t mins, vec3_t maxs,
						  clipHandle_t model, int brushmask,
						  const vec3_t origin, const vec3_t angles, int capsule ) {
	trace_t		trace;
	vec3_t		start_l, end_l;
	qboolean	rotated;
	vec3_t		offset;
	vec3_t		symetricSize[2];
	vec3_t		matrix[3], transpose[3];
	int			i;
	float		halfwidth;
	float		halfheight;
	float		t;
	sphere_t	sphere;

	if ( !mins ) {
		mins = vec3_origin;
	}
	if ( !maxs ) {
		maxs = vec3_origin;
	}

	// adjust so that mins and maxs are always symetric, which
	// avoids some complications with plane expanding of rotated
	// bmodels
	for ( i = 0 ; i < 3 ; i++ ) {
		offset[i] = ( mins[i] + maxs[i] ) * 0.5;
		symetricSize[0][i] = mins[i] - offset[i];
		symetricSize[1][i] = maxs[i] - offset[i];
		start_l[i] = start[i] + offset[i];
		end_l[i] = end[i] + offset[i];
	}

	// subtract origin offset
	VectorSubtract( start_l, origin, start_l );
	VectorSubtract( end_l, origin, end_l );

	// rotate start and end into the models frame of reference
	if ( model != BOX_MODEL_HANDLE && 
		(angles[0] || angles[1] || angles[2]) ) {
		rotated = qtrue;
	} else {
		rotated = qfalse;
	}

	halfwidth = symetricSize[ 1 ][ 0 ];
	halfheight = symetricSize[ 1 ][ 2 ];

	sphere.use = capsule;
	sphere.radius = ( halfwidth > halfheight ) ? halfheight : halfwidth;
	sphere.halfheight = halfheight;
	t = halfheight - sphere.radius;

	if (rotated) {
		// rotation on trace line (start-end) instead of rotating the bmodel
		// NOTE: This is still incorrect for bounding boxes because the actual bounding
		//		 box that is swept through the model is not rotated. We cannot rotate
		//		 the bounding box or the bmodel because that would make all the brush
		//		 bevels invalid.
		//		 However this is correct for capsules since a capsule itself is rotated too.
		CreateRotationMatrix(angles, matrix);
		RotatePoint(start_l, matrix);
		RotatePoint(end_l, matrix);
		// rotated sphere offset for capsule
		sphere.offset[0] = matrix[0][ 2 ] * t;
		sphere.offset[1] = -matrix[1][ 2 ] * t;
		sphere.offset[2] = matrix[2][ 2 ] * t;
	}
	else {
		VectorSet( sphere.offset, 0, 0, t );
	}

	// sweep the box through the model
	CM_Trace( &trace, start_l, end_l, symetricSize[0], symetricSize[1], model, origin, brushmask, capsule, &sphere );

	// if the bmodel was rotated and there was a collision
	if ( rotated && trace.fraction != 1.0 ) {
		// rotation of bmodel collision plane
		TransposeMatrix(matrix, transpose);
		RotatePoint(trace.plane.normal, transpose);
	}

	// re-calculate the end position of the trace because the trace.endpos
	// calculated by CM_Trace could be rotated and have an offset
	trace.endpos[0] = start[0] + trace.fraction * (end[0] - start[0]);
	trace.endpos[1] = start[1] + trace.fraction * (end[1] - start[1]);
	trace.endpos[2] = start[2] + trace.fraction * (end[2] - start[2]);

	*results = trace;
}