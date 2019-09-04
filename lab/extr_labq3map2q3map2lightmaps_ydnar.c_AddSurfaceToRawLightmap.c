#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vecs ;
typedef  float* vec4_t ;
typedef  float* vec3_t ;
struct TYPE_12__ {float sampleSize; scalar_t__ entityNum; scalar_t__ recvShadows; float* mins; float* maxs; float* plane; TYPE_1__* si; int /*<<< orphan*/  axis; } ;
typedef  TYPE_2__ surfaceInfo_t ;
struct TYPE_13__ {int numLightSurfaces; float* axis; float sampleSize; scalar_t__ entityNum; scalar_t__ recvShadows; float customWidth; float customHeight; scalar_t__ brightness; scalar_t__ filterRadius; scalar_t__ splotchFix; float* maxs; float* mins; float* plane; float actualSampleSize; float w; float h; int axisNum; int firstLightSurface; float* origin; float** vecs; } ;
typedef  TYPE_3__ rawLightmap_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_14__ {float* xyz; float** lightmap; } ;
typedef  TYPE_4__ bspDrawVert_t ;
struct TYPE_15__ {scalar_t__ surfaceType; size_t firstVert; int numVerts; float** lightmapVecs; float* lightmapOrigin; } ;
typedef  TYPE_5__ bspDrawSurface_t ;
struct TYPE_11__ {float lmCustomWidth; float lmCustomHeight; scalar_t__ lmBrightness; scalar_t__ lmFilterRadius; scalar_t__ splotchFix; scalar_t__ lmMergable; } ;

/* Variables and functions */
 scalar_t__ AddPatchToRawLightmap (int,TYPE_3__*) ; 
 int /*<<< orphan*/  AddPointToBounds (float*,float*,float*) ; 
 float DotProduct (float*,float*) ; 
 scalar_t__ EQUAL_EPSILON ; 
 scalar_t__ MST_PATCH ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ VectorCompare (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 scalar_t__ VectorLength (float*) ; 
 float VectorNormalize (float*,float*) ; 
 int /*<<< orphan*/  VectorScale (float*,double,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 TYPE_5__* bspDrawSurfaces ; 
 float ceil (float) ; 
 scalar_t__ fabs (float) ; 
 float floor (float) ; 
 int* lightSurfaces ; 
 int /*<<< orphan*/  memset (float**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numLightSurfaces ; 
 int /*<<< orphan*/  numNonPlanarsLightmapped ; 
 int /*<<< orphan*/  numPatchesLightmapped ; 
 int /*<<< orphan*/  numPlanarPatchesLightmapped ; 
 int /*<<< orphan*/  numPlanarsLightmapped ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 float** safe_malloc (int) ; 
 float superSample ; 
 TYPE_2__* surfaceInfos ; 
 TYPE_4__* yDrawVerts ; 

qboolean AddSurfaceToRawLightmap( int num, rawLightmap_t *lm ){
	bspDrawSurface_t    *ds, *ds2;
	surfaceInfo_t       *info, *info2;
	int num2, n, i, axisNum;
	float s, t, d, len, sampleSize;
	vec3_t mins, maxs, origin, faxis, size, exactSize, delta, normalized, vecs[ 2 ];
	vec4_t plane;
	bspDrawVert_t       *verts;


	/* get surface and info  */
	ds = &bspDrawSurfaces[ num ];
	info = &surfaceInfos[ num ];

	/* add the surface to the raw lightmap */
	lightSurfaces[ numLightSurfaces++ ] = num;
	lm->numLightSurfaces++;

	/* does this raw lightmap already have any surfaces? */
	if ( lm->numLightSurfaces > 1 ) {
		/* surface and raw lightmap must have the same lightmap projection axis */
		if ( VectorCompare( info->axis, lm->axis ) == qfalse ) {
			return qfalse;
		}

		/* match identical attributes */
		if ( info->sampleSize != lm->sampleSize ||
			 info->entityNum != lm->entityNum ||
			 info->recvShadows != lm->recvShadows ||
			 info->si->lmCustomWidth != lm->customWidth ||
			 info->si->lmCustomHeight != lm->customHeight ||
			 info->si->lmBrightness != lm->brightness ||
			 info->si->lmFilterRadius != lm->filterRadius ||
			 info->si->splotchFix != lm->splotchFix ) {
			return qfalse;
		}

		/* surface bounds must intersect with raw lightmap bounds */
		for ( i = 0; i < 3; i++ )
		{
			if ( info->mins[ i ] > lm->maxs[ i ] ) {
				return qfalse;
			}
			if ( info->maxs[ i ] < lm->mins[ i ] ) {
				return qfalse;
			}
		}

		/* plane check (fixme: allow merging of nonplanars) */
		if ( info->si->lmMergable == qfalse ) {
			if ( info->plane == NULL || lm->plane == NULL ) {
				return qfalse;
			}

			/* compare planes */
			for ( i = 0; i < 4; i++ )
				if ( fabs( info->plane[ i ] - lm->plane[ i ] ) > EQUAL_EPSILON ) {
					return qfalse;
				}
		}

		/* debug code hacking */
		//%	if( lm->numLightSurfaces > 1 )
		//%		return qfalse;
	}

	/* set plane */
	if ( info->plane == NULL ) {
		lm->plane = NULL;
	}

	/* add surface to lightmap bounds */
	AddPointToBounds( info->mins, lm->mins, lm->maxs );
	AddPointToBounds( info->maxs, lm->mins, lm->maxs );

	/* check to see if this is a non-planar patch */
	if ( ds->surfaceType == MST_PATCH &&
		 lm->axis[ 0 ] == 0.0f && lm->axis[ 1 ] == 0.0f && lm->axis[ 2 ] == 0.0f ) {
		return AddPatchToRawLightmap( num, lm );
	}

	/* start with initially requested sample size */
	sampleSize = lm->sampleSize;

	/* round to the lightmap resolution */
	for ( i = 0; i < 3; i++ )
	{
		exactSize[ i ] = lm->maxs[ i ] - lm->mins[ i ];
		mins[ i ] = sampleSize * floor( lm->mins[ i ] / sampleSize );
		maxs[ i ] = sampleSize * ceil( lm->maxs[ i ] / sampleSize );
		size[ i ] = ( maxs[ i ] - mins[ i ] ) / sampleSize + 1.0f;

		/* hack (god this sucks) */
		if ( size[ i ] > lm->customWidth || size[ i ] > lm->customHeight ) {
			i = -1;
			sampleSize += 1.0f;
		}
	}

	/* set actual sample size */
	lm->actualSampleSize = sampleSize;

	/* fixme: copy rounded mins/maxes to lightmap record? */
	if ( lm->plane == NULL ) {
		VectorCopy( mins, lm->mins );
		VectorCopy( maxs, lm->maxs );
		VectorCopy( mins, origin );
	}

	/* set lightmap origin */
	VectorCopy( lm->mins, origin );

	/* make absolute axis */
	faxis[ 0 ] = fabs( lm->axis[ 0 ] );
	faxis[ 1 ] = fabs( lm->axis[ 1 ] );
	faxis[ 2 ] = fabs( lm->axis[ 2 ] );

	/* clear out lightmap vectors */
	memset( vecs, 0, sizeof( vecs ) );

	/* classify the plane (x y or z major) (ydnar: biased to z axis projection) */
	if ( faxis[ 2 ] >= faxis[ 0 ] && faxis[ 2 ] >= faxis[ 1 ] ) {
		axisNum = 2;
		lm->w = size[ 0 ];
		lm->h = size[ 1 ];
		vecs[ 0 ][ 0 ] = 1.0f / sampleSize;
		vecs[ 1 ][ 1 ] = 1.0f / sampleSize;
	}
	else if ( faxis[ 0 ] >= faxis[ 1 ] && faxis[ 0 ] >= faxis[ 2 ] ) {
		axisNum = 0;
		lm->w = size[ 1 ];
		lm->h = size[ 2 ];
		vecs[ 0 ][ 1 ] = 1.0f / sampleSize;
		vecs[ 1 ][ 2 ] = 1.0f / sampleSize;
	}
	else
	{
		axisNum = 1;
		lm->w = size[ 0 ];
		lm->h = size[ 2 ];
		vecs[ 0 ][ 0 ] = 1.0f / sampleSize;
		vecs[ 1 ][ 2 ] = 1.0f / sampleSize;
	}

	/* check for bogus axis */
	if ( faxis[ axisNum ] == 0.0f ) {
		Sys_FPrintf( SYS_WRN, "WARNING: ProjectSurfaceLightmap: Chose a 0 valued axis\n" );
		lm->w = lm->h = 0;
		return qfalse;
	}

	/* store the axis number in the lightmap */
	lm->axisNum = axisNum;

	/* walk the list of surfaces on this raw lightmap */
	for ( n = 0; n < lm->numLightSurfaces; n++ )
	{
		/* get surface */
		num2 = lightSurfaces[ lm->firstLightSurface + n ];
		ds2 = &bspDrawSurfaces[ num2 ];
		info2 = &surfaceInfos[ num2 ];
		verts = &yDrawVerts[ ds2->firstVert ];

		/* set the lightmap texture coordinates in yDrawVerts in [0, superSample * lm->customWidth] space */
		for ( i = 0; i < ds2->numVerts; i++ )
		{
			VectorSubtract( verts[ i ].xyz, origin, delta );
			s = DotProduct( delta, vecs[ 0 ] ) + 0.5f;
			t = DotProduct( delta, vecs[ 1 ] ) + 0.5f;
			verts[ i ].lightmap[ 0 ][ 0 ] = s * superSample;
			verts[ i ].lightmap[ 0 ][ 1 ] = t * superSample;

			if ( s > (float) lm->w || t > (float) lm->h ) {
				Sys_FPrintf( SYS_VRB, "WARNING: Lightmap texture coords out of range: S %1.4f > %3d || T %1.4f > %3d\n",
							 s, lm->w, t, lm->h );
			}
		}
	}

	/* get first drawsurface */
	num2 = lightSurfaces[ lm->firstLightSurface ];
	ds2 = &bspDrawSurfaces[ num2 ];
	info2 = &surfaceInfos[ num2 ];
	verts = &yDrawVerts[ ds2->firstVert ];

	/* calculate lightmap origin */
	if ( VectorLength( ds2->lightmapVecs[ 2 ] ) ) {
		VectorCopy( ds2->lightmapVecs[ 2 ], plane );
	}
	else{
		VectorCopy( lm->axis, plane );
	}
	plane[ 3 ] = DotProduct( verts[ 0 ].xyz, plane );

	VectorCopy( origin, lm->origin );
	d = DotProduct( lm->origin, plane ) - plane[ 3 ];
	d /= plane[ axisNum ];
	lm->origin[ axisNum ] -= d;

	/* legacy support */
	VectorCopy( lm->origin, ds->lightmapOrigin );

	/* for planar surfaces, create lightmap vectors for st->xyz conversion */
	if ( VectorLength( ds->lightmapVecs[ 2 ] ) || 1 ) {  /* ydnar: can't remember what exactly i was thinking here... */
		/* allocate space for the vectors */
		lm->vecs = safe_malloc( 3 * sizeof( vec3_t ) );
		memset( lm->vecs, 0, 3 * sizeof( vec3_t ) );
		VectorCopy( ds->lightmapVecs[ 2 ], lm->vecs[ 2 ] );

		/* project stepped lightmap blocks and subtract to get planevecs */
		for ( i = 0; i < 2; i++ )
		{
			len = VectorNormalize( vecs[ i ], normalized );
			VectorScale( normalized, ( 1.0 / len ), lm->vecs[ i ] );
			d = DotProduct( lm->vecs[ i ], plane );
			d /= plane[ axisNum ];
			lm->vecs[ i ][ axisNum ] -= d;
		}
	}
	else
	{
		/* lightmap vectors are useless on a non-planar surface */
		lm->vecs = NULL;
	}

	/* add to counts */
	if ( ds->surfaceType == MST_PATCH ) {
		numPatchesLightmapped++;
		if ( lm->plane != NULL ) {
			numPlanarPatchesLightmapped++;
		}
	}
	else
	{
		if ( lm->plane != NULL ) {
			numPlanarsLightmapped++;
		}
		else{
			numNonPlanarsLightmapped++;
		}
	}

	/* return */
	return qtrue;
}