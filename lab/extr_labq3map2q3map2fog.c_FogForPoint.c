#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_7__ {scalar_t__ dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_8__ {int numsides; TYPE_1__* sides; } ;
typedef  TYPE_3__ brush_t ;
struct TYPE_9__ {TYPE_3__* brush; } ;
struct TYPE_6__ {size_t planenum; } ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int defaultFogNum ; 
 TYPE_5__* mapFogs ; 
 TYPE_2__* mapplanes ; 
 int numMapFogs ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

int FogForPoint( vec3_t point, float epsilon ){
	int fogNum, i, j;
	float dot;
	qboolean inside;
	brush_t         *brush;
	plane_t         *plane;


	/* start with bogus fog num */
	fogNum = defaultFogNum;

	/* walk the list of fog volumes */
	for ( i = 0; i < numMapFogs; i++ )
	{
		/* sof2: global fog doesn't reference a brush */
		if ( mapFogs[ i ].brush == NULL ) {
			fogNum = i;
			continue;
		}

		/* get fog brush */
		brush = mapFogs[ i ].brush;

		/* check point against all planes */
		inside = qtrue;
		for ( j = 0; j < brush->numsides && inside; j++ )
		{
			plane = &mapplanes[ brush->sides[ j ].planenum ];   /* note usage of map planes here */
			dot = DotProduct( point, plane->normal );
			dot -= plane->dist;
			if ( dot > epsilon ) {
				inside = qfalse;
			}
		}

		/* if inside, return the fog num */
		if ( inside ) {
			//%	Sys_Printf( "FogForPoint: %f, %f, %f in fog %d\n", point[ 0 ], point[ 1 ], point[ 2 ], i );
			return i;
		}
	}

	/* if the point made it this far, it's not inside any fog volumes (or inside global fog) */
	return fogNum;
}