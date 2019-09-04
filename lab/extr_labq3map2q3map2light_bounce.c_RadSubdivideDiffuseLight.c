#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int numpoints; float** p; } ;
typedef  TYPE_2__ winding_t ;
typedef  float* vec3_t ;
struct TYPE_22__ {float value; float* color; int lightStyle; int backsplashFraction; float backsplashDistance; float bounceScale; int compileFlags; scalar_t__ twoSided; } ;
typedef  TYPE_3__ shaderInfo_t ;
typedef  int /*<<< orphan*/  rawLightmap_t ;
struct TYPE_23__ {int numVerts; TYPE_1__* verts; } ;
typedef  TYPE_4__ radWinding_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_24__ {float fade; float photons; float add; float* color; float* emitColor; int style; float* origin; float* normal; int /*<<< orphan*/  flags; void* dist; void* falloffTolerance; TYPE_3__* si; int /*<<< orphan*/  type; void* next; TYPE_2__* w; } ;
typedef  TYPE_5__ light_t ;
typedef  int /*<<< orphan*/  clipWork_t ;
struct TYPE_25__ {int surfaceType; } ;
typedef  TYPE_6__ bspDrawSurface_t ;
struct TYPE_20__ {float* xyz; float* normal; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (float*,float*,float*) ; 
 TYPE_2__* AllocWinding (int) ; 
 int C_FOG ; 
 int /*<<< orphan*/  ClearBounds (float*,float*) ; 
 int /*<<< orphan*/  CrossProduct (float*,float*,float*) ; 
 void* DotProduct (float*,float*) ; 
 int /*<<< orphan*/  EMIT_AREA ; 
 int /*<<< orphan*/  EMIT_POINT ; 
 int /*<<< orphan*/  LIGHT_AREA_DEFAULT ; 
 int /*<<< orphan*/  LIGHT_Q3A_DEFAULT ; 
 int /*<<< orphan*/  LIGHT_TWOSIDED ; 
 int LS_NONE ; 
 int LS_NORMAL ; 
#define  MST_PATCH 130 
#define  MST_PLANAR 129 
#define  MST_TRIANGLE_SOUP 128 
 int /*<<< orphan*/  RADIOSITY_CLIP_EPSILON ; 
 float RADIOSITY_MAX_GRADIENT ; 
 float RADIOSITY_MIN ; 
 float RADIOSITY_VALUE ; 
 int /*<<< orphan*/  RadClipWindingEpsilon (TYPE_4__*,float*,float,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RadSample (int,TYPE_6__*,int /*<<< orphan*/ *,TYPE_3__*,TYPE_4__*,float*,float*,int*) ; 
 int /*<<< orphan*/  ThreadLock () ; 
 int /*<<< orphan*/  ThreadUnlock () ; 
 int /*<<< orphan*/  VectorAdd (float*,float*,float*) ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 float VectorLength (float*) ; 
 int /*<<< orphan*/  VectorMA (float*,float,float*,float*) ; 
 float VectorNormalize (float*,float*) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 int /*<<< orphan*/  WindingCenter (TYPE_2__*,float*) ; 
 float areaScale ; 
 float bounceScale ; 
 scalar_t__ bouncing ; 
 void* falloffTolerance ; 
 float formFactorValueScale ; 
 void* lights ; 
 int /*<<< orphan*/  master_mutex ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 float minDiffuseSubdivide ; 
 scalar_t__ noStyles ; 
 int /*<<< orphan*/  numBrushDiffuseLights ; 
 int /*<<< orphan*/  numDiffuseLights ; 
 int /*<<< orphan*/  numPatchDiffuseLights ; 
 int /*<<< orphan*/  numPointLights ; 
 int /*<<< orphan*/  numTriangleDiffuseLights ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ qfalse ; 
 TYPE_5__* safe_malloc (int) ; 

__attribute__((used)) static void RadSubdivideDiffuseLight( int lightmapNum, bspDrawSurface_t *ds, rawLightmap_t *lm, shaderInfo_t *si,
									  float scale, float subdivide, qboolean original, radWinding_t *rw, clipWork_t *cw ){
	int i, style;
	float dist, area, value;
	vec3_t mins, maxs, normal, d1, d2, cross, color, gradient;
	light_t         *light, *splash;
	winding_t       *w;


	/* dummy check */
	if ( rw == NULL || rw->numVerts < 3 ) {
		return;
	}

	/* get bounds for winding */
	ClearBounds( mins, maxs );
	for ( i = 0; i < rw->numVerts; i++ )
		AddPointToBounds( rw->verts[ i ].xyz, mins, maxs );

	/* subdivide if necessary */
	for ( i = 0; i < 3; i++ )
	{
		if ( maxs[ i ] - mins[ i ] > subdivide ) {
			radWinding_t front, back;


			/* make axial plane */
			VectorClear( normal );
			normal[ i ] = 1;
			dist = ( maxs[ i ] + mins[ i ] ) * 0.5f;

			/* clip the winding */
			RadClipWindingEpsilon( rw, normal, dist, RADIOSITY_CLIP_EPSILON, &front, &back, cw );

			/* recurse */
			RadSubdivideDiffuseLight( lightmapNum, ds, lm, si, scale, subdivide, qfalse, &front, cw );
			RadSubdivideDiffuseLight( lightmapNum, ds, lm, si, scale, subdivide, qfalse, &back, cw );
			return;
		}
	}

	/* check area */
	area = 0.0f;
	for ( i = 2; i < rw->numVerts; i++ )
	{
		VectorSubtract( rw->verts[ i - 1 ].xyz, rw->verts[ 0 ].xyz, d1 );
		VectorSubtract( rw->verts[ i ].xyz, rw->verts[ 0 ].xyz, d2 );
		CrossProduct( d1, d2, cross );
		area += 0.5f * VectorLength( cross );
	}
	if ( area < 1.0f || area > 20000000.0f ) {
		return;
	}

	/* more subdivision may be necessary */
	if ( bouncing ) {
		/* get color sample for the surface fragment */
		RadSample( lightmapNum, ds, lm, si, rw, color, gradient, &style );

		/* if color gradient is too high, subdivide again */
		if ( subdivide > minDiffuseSubdivide &&
			 ( gradient[ 0 ] > RADIOSITY_MAX_GRADIENT || gradient[ 1 ] > RADIOSITY_MAX_GRADIENT || gradient[ 2 ] > RADIOSITY_MAX_GRADIENT ) ) {
			RadSubdivideDiffuseLight( lightmapNum, ds, lm, si, scale, ( subdivide / 2.0f ), qfalse, rw, cw );
			return;
		}
	}

	/* create a regular winding and an average normal */
	w = AllocWinding( rw->numVerts );
	w->numpoints = rw->numVerts;
	VectorClear( normal );
	for ( i = 0; i < rw->numVerts; i++ )
	{
		VectorCopy( rw->verts[ i ].xyz, w->p[ i ] );
		VectorAdd( normal, rw->verts[ i ].normal, normal );
	}
	VectorScale( normal, ( 1.0f / rw->numVerts ), normal );
	if ( VectorNormalize( normal, normal ) == 0.0f ) {
		return;
	}

	/* early out? */
	if ( bouncing && VectorLength( color ) < RADIOSITY_MIN ) {
		return;
	}

	/* debug code */
	//%	Sys_Printf( "Size: %d %d %d\n", (int) (maxs[ 0 ] - mins[ 0 ]), (int) (maxs[ 1 ] - mins[ 1 ]), (int) (maxs[ 2 ] - mins[ 2 ]) );
	//%	Sys_Printf( "Grad: %f %f %f\n", gradient[ 0 ], gradient[ 1 ], gradient[ 2 ] );

	/* increment counts */
	pthread_mutex_lock( &master_mutex );
	numDiffuseLights++;
	pthread_mutex_unlock( &master_mutex );
	switch ( ds->surfaceType )
	{
	case MST_PLANAR:
		pthread_mutex_lock( &master_mutex );
		numBrushDiffuseLights++;
		pthread_mutex_unlock( &master_mutex );
		break;

	case MST_TRIANGLE_SOUP:
		pthread_mutex_lock( &master_mutex );
		numTriangleDiffuseLights++;
		pthread_mutex_unlock( &master_mutex );
		break;

	case MST_PATCH:
		pthread_mutex_lock( &master_mutex );
		numPatchDiffuseLights++;
		pthread_mutex_unlock( &master_mutex );
		break;
	}

	/* create a light */
	light = safe_malloc( sizeof( *light ) );
	memset( light, 0, sizeof( *light ) );

	/* attach it */
	ThreadLock();
	light->next = lights;
	lights = light;
	ThreadUnlock();

	/* initialize the light */
	light->flags = LIGHT_AREA_DEFAULT;
	light->type = EMIT_AREA;
	light->si = si;
	light->fade = 1.0f;
	light->w = w;

	/* set falloff threshold */
	light->falloffTolerance = falloffTolerance;

	/* bouncing light? */
	if ( bouncing == qfalse ) {
		/* handle first-pass lights in normal q3a style */
		value = si->value;
		light->photons = value * area * areaScale;
		light->add = value * formFactorValueScale * areaScale;
		VectorCopy( si->color, light->color );
		VectorScale( light->color, light->add, light->emitColor );
		light->style = noStyles ? LS_NORMAL : si->lightStyle;
		if ( light->style < LS_NORMAL || light->style >= LS_NONE ) {
			light->style = LS_NORMAL;
		}

		/* set origin */
		VectorAdd( mins, maxs, light->origin );
		VectorScale( light->origin, 0.5f, light->origin );

		/* nudge it off the plane a bit */
		VectorCopy( normal, light->normal );
		VectorMA( light->origin, 1.0f, light->normal, light->origin );
		light->dist = DotProduct( light->origin, normal );

		/* optionally create a point splashsplash light for first pass */
		if ( original && si->backsplashFraction > 0 ) {
			/* allocate a new point light */
			splash = safe_malloc( sizeof( *splash ) );
			memset( splash, 0, sizeof( *splash ) );
			splash->next = lights;
			lights = splash;

			/* set it up */
			splash->flags = LIGHT_Q3A_DEFAULT;
			splash->type = EMIT_POINT;
			splash->photons = light->photons * si->backsplashFraction;
			splash->fade = 1.0f;
			splash->si = si;
			VectorMA( light->origin, si->backsplashDistance, normal, splash->origin );
			VectorCopy( si->color, splash->color );
			splash->falloffTolerance = falloffTolerance;
			splash->style = noStyles ? LS_NORMAL : light->style;

			/* add to counts */
			numPointLights++;
		}
	}
	else
	{
		/* handle bounced light (radiosity) a little differently */
		value = RADIOSITY_VALUE * si->bounceScale * 0.375f;
		light->photons = value * area * bounceScale;
		light->add = value * formFactorValueScale * bounceScale;
		VectorCopy( color, light->color );
		VectorScale( light->color, light->add, light->emitColor );
		light->style = noStyles ? LS_NORMAL : style;
		if ( light->style < LS_NORMAL || light->style >= LS_NONE ) {
			light->style = LS_NORMAL;
		}

		/* set origin */
		WindingCenter( w, light->origin );

		/* nudge it off the plane a bit */
		VectorCopy( normal, light->normal );
		VectorMA( light->origin, 1.0f, light->normal, light->origin );
		light->dist = DotProduct( light->origin, normal );
	}

	/* emit light from both sides? */
	if ( si->compileFlags & C_FOG || si->twoSided ) {
		light->flags |= LIGHT_TWOSIDED;
	}

	//%	Sys_Printf( "\nAL: C: (%6f, %6f, %6f) [%6f] N: (%6f, %6f, %6f) %s\n",
	//%		light->color[ 0 ], light->color[ 1 ], light->color[ 2 ], light->add,
	//%		light->normal[ 0 ], light->normal[ 1 ], light->normal[ 2 ],
	//%		light->si->shader );
}