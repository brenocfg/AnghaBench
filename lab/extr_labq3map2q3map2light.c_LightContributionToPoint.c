#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_6__ {scalar_t__* origin; scalar_t__* displacement; int testAll; int compileFlags; int /*<<< orphan*/  color; scalar_t__ passSolid; scalar_t__ opaque; int /*<<< orphan*/  forceSunlight; scalar_t__ testOcclusion; int /*<<< orphan*/  direction; int /*<<< orphan*/  end; int /*<<< orphan*/  cluster; TYPE_2__* light; } ;
typedef  TYPE_1__ trace_t ;
struct TYPE_7__ {int flags; float envelope; scalar_t__ type; scalar_t__* maxs; scalar_t__* mins; scalar_t__* origin; float photons; float dist; float add; float fade; float radiusByDist; float falloffTolerance; int /*<<< orphan*/  color; int /*<<< orphan*/  normal; int /*<<< orphan*/  w; int /*<<< orphan*/  cluster; } ;
typedef  TYPE_2__ light_t ;

/* Variables and functions */
 int C_SKY ; 
 int /*<<< orphan*/  ClusterVisible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float DotProduct (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EMIT_AREA ; 
 scalar_t__ EMIT_POINT ; 
 scalar_t__ EMIT_SPOT ; 
 scalar_t__ EMIT_SUN ; 
 int LIGHT_ATTEN_LINEAR ; 
 int LIGHT_FAST_ACTUAL ; 
 int LIGHT_GRID ; 
 int LIGHT_TWOSIDED ; 
 float PointToPolygonFormFactor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float SetupTrace (TYPE_1__*) ; 
 int /*<<< orphan*/  TraceLine (TYPE_1__*) ; 
 int /*<<< orphan*/  VectorAdd (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (scalar_t__*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ faster ; 
 int /*<<< orphan*/  gridBoundsCulled ; 
 int /*<<< orphan*/  gridEnvelopeCulled ; 
 float linearScale ; 
 int /*<<< orphan*/  master_mutex ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int qfalse ; 
 int qtrue ; 
 scalar_t__ sunOnly ; 

int LightContributionToPoint( trace_t *trace ){
	light_t     *light;
	float add, dist;


	/* get light */
	light = trace->light;

	/* clear color */
	VectorClear( trace->color );

	/* ydnar: early out */
	if ( !( light->flags & LIGHT_GRID ) || light->envelope <= 0.0f ) {
		return qfalse;
	}

	/* is this a sun? */
	if ( light->type != EMIT_SUN ) {
		/* sun only? */
		if ( sunOnly ) {
			return qfalse;
		}

		/* test pvs */
		if ( !ClusterVisible( trace->cluster, light->cluster ) ) {
			return qfalse;
		}
	}

	/* ydnar: check origin against light's pvs envelope */
	if ( trace->origin[ 0 ] > light->maxs[ 0 ] || trace->origin[ 0 ] < light->mins[ 0 ] ||
		 trace->origin[ 1 ] > light->maxs[ 1 ] || trace->origin[ 1 ] < light->mins[ 1 ] ||
		 trace->origin[ 2 ] > light->maxs[ 2 ] || trace->origin[ 2 ] < light->mins[ 2 ] ) {
		pthread_mutex_lock( &master_mutex );
		gridBoundsCulled++;
		pthread_mutex_unlock( &master_mutex );
		return qfalse;
	}

	/* set light origin */
	if ( light->type == EMIT_SUN ) {
		VectorAdd( trace->origin, light->origin, trace->end );
	}
	else{
		VectorCopy( light->origin, trace->end );
	}

	/* set direction */
	dist = SetupTrace( trace );

	/* test envelope */
	if ( dist > light->envelope ) {
		pthread_mutex_lock( &master_mutex );
		gridEnvelopeCulled++;
		pthread_mutex_unlock( &master_mutex );
		return qfalse;
	}

	/* ptpff approximation */
	if ( light->type == EMIT_AREA && faster ) {
		/* clamp the distance to prevent super hot spots */
		if ( dist < 16.0f ) {
			dist = 16.0f;
		}

		/* attenuate */
		add = light->photons / ( dist * dist );
	}

	/* exact point to polygon form factor */
	else if ( light->type == EMIT_AREA ) {
		float factor, d;
		vec3_t pushedOrigin;


		/* see if the point is behind the light */
		d = DotProduct( trace->origin, light->normal ) - light->dist;
		if ( !( light->flags & LIGHT_TWOSIDED ) && d < -1.0f ) {
			return qfalse;
		}

		/* nudge the point so that it is clearly forward of the light */
		/* so that surfaces meeting a light emiter don't get black edges */
		if ( d > -8.0f && d < 8.0f ) {
			VectorMA( trace->origin, ( 8.0f - d ), light->normal, pushedOrigin );
		}
		else{
			VectorCopy( trace->origin, pushedOrigin );
		}

		/* calculate the contribution (ydnar 2002-10-21: [bug 642] bad normal calc) */
		factor = PointToPolygonFormFactor( pushedOrigin, trace->direction, light->w );
		if ( factor == 0.0f ) {
			return qfalse;
		}
		else if ( factor < 0.0f ) {
			if ( light->flags & LIGHT_TWOSIDED ) {
				factor = -factor;
			}
			else{
				return qfalse;
			}
		}

		/* ydnar: moved to here */
		add = factor * light->add;
	}

	/* point/spot lights */
	else if ( light->type == EMIT_POINT || light->type == EMIT_SPOT ) {
		/* clamp the distance to prevent super hot spots */
		if ( dist < 16.0f ) {
			dist = 16.0f;
		}

		/* attenuate */
		if ( light->flags & LIGHT_ATTEN_LINEAR ) {
			add = light->photons * linearScale - ( dist * light->fade );
			if ( add < 0.0f ) {
				add = 0.0f;
			}
		}
		else{
			add = light->photons / ( dist * dist );
		}

		/* handle spotlights */
		if ( light->type == EMIT_SPOT ) {
			float distByNormal, radiusAtDist, sampleRadius;
			vec3_t pointAtDist, distToSample;


			/* do cone calculation */
			distByNormal = -DotProduct( trace->displacement, light->normal );
			if ( distByNormal < 0.0f ) {
				return qfalse;
			}
			VectorMA( light->origin, distByNormal, light->normal, pointAtDist );
			radiusAtDist = light->radiusByDist * distByNormal;
			VectorSubtract( trace->origin, pointAtDist, distToSample );
			sampleRadius = VectorLength( distToSample );

			/* outside the cone */
			if ( sampleRadius >= radiusAtDist ) {
				return qfalse;
			}

			/* attenuate */
			if ( sampleRadius > ( radiusAtDist - 32.0f ) ) {
				add *= ( ( radiusAtDist - sampleRadius ) / 32.0f );
			}
		}
	}

	/* ydnar: sunlight */
	else if ( light->type == EMIT_SUN ) {
		/* attenuate */
		add = light->photons;
		if ( add <= 0.0f ) {
			return qfalse;
		}

		/* setup trace */
		trace->testAll = qtrue;
		VectorScale( light->color, add, trace->color );

		/* trace to point */
		if ( trace->testOcclusion && !trace->forceSunlight ) {
			/* trace */
			TraceLine( trace );
			if ( !( trace->compileFlags & C_SKY ) || trace->opaque ) {
				VectorClear( trace->color );
				return -1;
			}
		}

		/* return to sender */
		return qtrue;
	}

	/* unknown light type */
	else{
		return qfalse;
	}

	/* ydnar: changed to a variable number */
	if ( add <= 0.0f || ( add <= light->falloffTolerance && ( light->flags & LIGHT_FAST_ACTUAL ) ) ) {
		return qfalse;
	}

	/* setup trace */
	trace->testAll = qfalse;
	VectorScale( light->color, add, trace->color );

	/* trace */
	TraceLine( trace );
	if ( trace->passSolid ) {
		VectorClear( trace->color );
		return qfalse;
	}

	/* we have a valid sample */
	return qtrue;
}