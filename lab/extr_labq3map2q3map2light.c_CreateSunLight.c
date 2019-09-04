#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_7__ {int numSamples; float photons; int* direction; float deviance; int filterRadius; int* color; struct TYPE_7__* next; int /*<<< orphan*/  style; } ;
typedef  TYPE_1__ sun_t ;
struct TYPE_8__ {float fade; int filterRadius; int* color; float photons; int /*<<< orphan*/  normal; int /*<<< orphan*/  origin; int /*<<< orphan*/  dist; int /*<<< orphan*/  style; int /*<<< orphan*/  falloffTolerance; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; struct TYPE_8__* next; } ;
typedef  TYPE_2__ light_t ;

/* Variables and functions */
 int /*<<< orphan*/  DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT_SUN ; 
 int /*<<< orphan*/  LIGHT_SUN_DEFAULT ; 
 int /*<<< orphan*/  LS_NORMAL ; 
 float MAX_WORLD_COORD ; 
 float Random () ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int*,double,int /*<<< orphan*/ ) ; 
 float atan2 (int,float) ; 
 int cos (float) ; 
 int /*<<< orphan*/  falloffTolerance ; 
 TYPE_2__* lights ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ noStyles ; 
 int /*<<< orphan*/  numSunLights ; 
 TYPE_2__* safe_malloc (int) ; 
 int sin (float) ; 
 float skyScale ; 
 float sqrt (int) ; 
 int /*<<< orphan*/  vec3_origin ; 

__attribute__((used)) static void CreateSunLight( sun_t *sun ){
	int i;
	float photons, d, angle, elevation, da, de;
	vec3_t direction;
	light_t     *light;


	/* dummy check */
	if ( sun == NULL ) {
		return;
	}

	/* fixup */
	if ( sun->numSamples < 1 ) {
		sun->numSamples = 1;
	}

	/* set photons */
	photons = sun->photons / sun->numSamples;

	/* create the right number of suns */
	for ( i = 0; i < sun->numSamples; i++ )
	{
		/* calculate sun direction */
		if ( i == 0 ) {
			VectorCopy( sun->direction, direction );
		}
		else
		{
			/*
			    sun->direction[ 0 ] = cos( angle ) * cos( elevation );
			    sun->direction[ 1 ] = sin( angle ) * cos( elevation );
			    sun->direction[ 2 ] = sin( elevation );

			    xz_dist   = sqrt( x*x + z*z )
			    latitude  = atan2( xz_dist, y ) * RADIANS
			    longitude = atan2( x,       z ) * RADIANS
			 */

			d = sqrt( sun->direction[ 0 ] * sun->direction[ 0 ] + sun->direction[ 1 ] * sun->direction[ 1 ] );
			angle = atan2( sun->direction[ 1 ], sun->direction[ 0 ] );
			elevation = atan2( sun->direction[ 2 ], d );

			/* jitter the angles (loop to keep random sample within sun->deviance steridians) */
			do
			{
				da = ( Random() * 2.0f - 1.0f ) * sun->deviance;
				de = ( Random() * 2.0f - 1.0f ) * sun->deviance;
			}
			while ( ( da * da + de * de ) > ( sun->deviance * sun->deviance ) );
			angle += da;
			elevation += de;

			/* debug code */
			//%	Sys_Printf( "%d: Angle: %3.4f Elevation: %3.3f\n", sun->numSamples, (angle / Q_PI * 180.0f), (elevation / Q_PI * 180.0f) );

			/* create new vector */
			direction[ 0 ] = cos( angle ) * cos( elevation );
			direction[ 1 ] = sin( angle ) * cos( elevation );
			direction[ 2 ] = sin( elevation );
		}

		/* create a light */
		numSunLights++;
		light = safe_malloc( sizeof( *light ) );
		memset( light, 0, sizeof( *light ) );
		light->next = lights;
		lights = light;

		/* initialize the light */
		light->flags = LIGHT_SUN_DEFAULT;
		light->type = EMIT_SUN;
		light->fade = 1.0f;
		light->falloffTolerance = falloffTolerance;
		light->filterRadius = sun->filterRadius / sun->numSamples;
		light->style = noStyles ? LS_NORMAL : sun->style;

		/* set the light's position out to infinity */
		VectorMA( vec3_origin, ( MAX_WORLD_COORD * 8.0f ), direction, light->origin );    /* MAX_WORLD_COORD * 2.0f */

		/* set the facing to be the inverse of the sun direction */
		VectorScale( direction, -1.0, light->normal );
		light->dist = DotProduct( light->origin, light->normal );

		/* set color and photons */
		VectorCopy( sun->color, light->color );
		light->photons = photons * skyScale;
	}

	/* another sun? */
	if ( sun->next != NULL ) {
		CreateSunLight( sun->next );
	}
}