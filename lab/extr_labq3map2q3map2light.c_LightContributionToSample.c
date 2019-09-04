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
struct TYPE_6__ {scalar_t__ twoSided; int compileFlags; int /*<<< orphan*/  color; scalar_t__ opaque; scalar_t__ passSolid; scalar_t__ testAll; int /*<<< orphan*/  forceSunlight; scalar_t__ testOcclusion; int /*<<< orphan*/  direction; int /*<<< orphan*/  normal; int /*<<< orphan*/  end; int /*<<< orphan*/  origin; int /*<<< orphan*/  displacement; int /*<<< orphan*/  cluster; TYPE_2__* light; } ;
typedef  TYPE_1__ trace_t ;
struct TYPE_7__ {int flags; float envelope; scalar_t__ type; float dist; float photons; float add; float angleScale; float fade; float radiusByDist; float falloffTolerance; int /*<<< orphan*/  color; int /*<<< orphan*/  origin; int /*<<< orphan*/  normal; int /*<<< orphan*/  w; int /*<<< orphan*/  cluster; } ;
typedef  TYPE_2__ light_t ;

/* Variables and functions */
 int C_SKY ; 
 int /*<<< orphan*/  ClusterVisible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EMIT_AREA ; 
 scalar_t__ EMIT_POINT ; 
 scalar_t__ EMIT_SPOT ; 
 scalar_t__ EMIT_SUN ; 
 int LIGHT_ATTEN_ANGLE ; 
 int LIGHT_ATTEN_LINEAR ; 
 int LIGHT_FAST_ACTUAL ; 
 int LIGHT_SURFACES ; 
 int LIGHT_TWOSIDED ; 
 float PointToPolygonFormFactor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float SetupTrace (TYPE_1__*) ; 
 int /*<<< orphan*/  TraceLine (TYPE_1__*) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float fabs (float) ; 
 scalar_t__ faster ; 
 float linearScale ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

int LightContributionToSample( trace_t *trace ){
	light_t         *light;
	float angle;
	float add;
	float dist;


	/* get light */
	light = trace->light;

	/* clear color */
	VectorClear( trace->color );

	/* ydnar: early out */
	if ( !( light->flags & LIGHT_SURFACES ) || light->envelope <= 0.0f ) {
		return 0;
	}

	/* do some culling checks */
	if ( light->type != EMIT_SUN ) {
		/* MrE: if the light is behind the surface */
		if ( trace->twoSided == qfalse ) {
			if ( DotProduct( light->origin, trace->normal ) - DotProduct( trace->origin, trace->normal ) < 0.0f ) {
				return 0;
			}
		}

		/* ydnar: test pvs */
		if ( !ClusterVisible( trace->cluster, light->cluster ) ) {
			return 0;
		}
	}

	/* exact point to polygon form factor */
	if ( light->type == EMIT_AREA ) {
		float factor;
		float d;
		vec3_t pushedOrigin;


		/* project sample point into light plane */
		d = DotProduct( trace->origin, light->normal ) - light->dist;
		if ( d < 3.0f ) {
			/* sample point behind plane? */
			if ( !( light->flags & LIGHT_TWOSIDED ) && d < -1.0f ) {
				return 0;
			}

			/* sample plane coincident? */
			if ( d > -3.0f && DotProduct( trace->normal, light->normal ) > 0.9f ) {
				return 0;
			}
		}

		/* nudge the point so that it is clearly forward of the light */
		/* so that surfaces meeting a light emiter don't get black edges */
		if ( d > -8.0f && d < 8.0f ) {
			VectorMA( trace->origin, ( 8.0f - d ), light->normal, pushedOrigin );
		}
		else{
			VectorCopy( trace->origin, pushedOrigin );
		}

		/* get direction and distance */
		VectorCopy( light->origin, trace->end );
		dist = SetupTrace( trace );
		if ( dist >= light->envelope ) {
			return 0;
		}

		/* ptpff approximation */
		if ( faster ) {
			/* angle attenuation */
			angle = DotProduct( trace->normal, trace->direction );

			/* twosided lighting */
			if ( trace->twoSided ) {
				angle = fabs( angle );
			}

			/* attenuate */
			angle *= -DotProduct( light->normal, trace->direction );
			if ( angle == 0.0f ) {
				return 0;
			}
			else if ( angle < 0.0f &&
					  ( trace->twoSided || ( light->flags & LIGHT_TWOSIDED ) ) ) {
				angle = -angle;
			}
			add = light->photons / ( dist * dist ) * angle;
		}
		else
		{
			/* calculate the contribution */
			factor = PointToPolygonFormFactor( pushedOrigin, trace->normal, light->w );
			if ( factor == 0.0f ) {
				return 0;
			}
			else if ( factor < 0.0f ) {
				/* twosided lighting */
				if ( trace->twoSided || ( light->flags & LIGHT_TWOSIDED ) ) {
					factor = -factor;

					/* push light origin to other side of the plane */
					VectorMA( light->origin, -2.0f, light->normal, trace->end );
					dist = SetupTrace( trace );
					if ( dist >= light->envelope ) {
						return 0;
					}
				}
				else{
					return 0;
				}
			}

			/* ydnar: moved to here */
			add = factor * light->add;
		}
	}

	/* point/spot lights */
	else if ( light->type == EMIT_POINT || light->type == EMIT_SPOT ) {
		/* get direction and distance */
		VectorCopy( light->origin, trace->end );
		dist = SetupTrace( trace );
		if ( dist >= light->envelope ) {
			return 0;
		}

		/* clamp the distance to prevent super hot spots */
		if ( dist < 16.0f ) {
			dist = 16.0f;
		}

		/* angle attenuation */
		angle = ( light->flags & LIGHT_ATTEN_ANGLE ) ? DotProduct( trace->normal, trace->direction ) : 1.0f;
		if ( light->angleScale != 0.0f ) {
			angle /= light->angleScale;
			if ( angle > 1.0f ) {
				angle = 1.0f;
			}
		}

		/* twosided lighting */
		if ( trace->twoSided ) {
			angle = fabs( angle );
		}

		/* attenuate */
		if ( light->flags & LIGHT_ATTEN_LINEAR ) {
			add = angle * light->photons * linearScale - ( dist * light->fade );
			if ( add < 0.0f ) {
				add = 0.0f;
			}
		}
		else{
			add = light->photons / ( dist * dist ) * angle;
		}

		/* handle spotlights */
		if ( light->type == EMIT_SPOT ) {
			float distByNormal, radiusAtDist, sampleRadius;
			vec3_t pointAtDist, distToSample;


			/* do cone calculation */
			distByNormal = -DotProduct( trace->displacement, light->normal );
			if ( distByNormal < 0.0f ) {
				return 0;
			}
			VectorMA( light->origin, distByNormal, light->normal, pointAtDist );
			radiusAtDist = light->radiusByDist * distByNormal;
			VectorSubtract( trace->origin, pointAtDist, distToSample );
			sampleRadius = VectorLength( distToSample );

			/* outside the cone */
			if ( sampleRadius >= radiusAtDist ) {
				return 0;
			}

			/* attenuate */
			if ( sampleRadius > ( radiusAtDist - 32.0f ) ) {
				add *= ( ( radiusAtDist - sampleRadius ) / 32.0f );
			}
		}
	}

	/* ydnar: sunlight */
	else if ( light->type == EMIT_SUN ) {
		/* get origin and direction */
		VectorAdd( trace->origin, light->origin, trace->end );
		dist = SetupTrace( trace );

		/* angle attenuation */
		angle = ( light->flags & LIGHT_ATTEN_ANGLE )
				? DotProduct( trace->normal, trace->direction )
				: 1.0f;

		/* twosided lighting */
		if ( trace->twoSided ) {
			angle = fabs( angle );
		}

		/* attenuate */
		add = light->photons * angle;
		if ( add <= 0.0f ) {
			return 0;
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
		return 1;
	} 

	/* unknown light type */
	else {
		return -1;
	}

	/* ydnar: changed to a variable number */
	if ( add <= 0.0f || ( add <= light->falloffTolerance && ( light->flags & LIGHT_FAST_ACTUAL ) ) ) {
		return 0;
	}

	/* setup trace */
	trace->testAll = qfalse;
	VectorScale( light->color, add, trace->color );

	/* raytrace */
	TraceLine( trace );
	if ( trace->passSolid || trace->opaque ) {
		VectorClear( trace->color );
		return -1;
	}

	/* return to sender */
	return 1;
}