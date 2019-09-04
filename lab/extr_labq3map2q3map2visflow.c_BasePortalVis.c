#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float dist; int /*<<< orphan*/  normal; } ;
struct TYPE_7__ {int* portalfront; int* portalflood; int* portalvis; float radius; scalar_t__ nummightsee; int /*<<< orphan*/  leaf; TYPE_1__ plane; TYPE_3__* winding; int /*<<< orphan*/  origin; scalar_t__ removed; } ;
typedef  TYPE_2__ vportal_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_8__ {int numpoints; int /*<<< orphan*/ * points; } ;
typedef  TYPE_3__ fixedWinding_t ;

/* Variables and functions */
 scalar_t__ CountBits (int*,int) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float ON_EPSILON ; 
 int /*<<< orphan*/  SimpleFlood (TYPE_2__*,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_flood ; 
 float farPlaneDist ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int numportals ; 
 int /*<<< orphan*/  portal_mutex ; 
 int /*<<< orphan*/  portalbytes ; 
 TYPE_2__* portals ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 void* safe_malloc (int /*<<< orphan*/ ) ; 

void BasePortalVis( int portalnum ){
	int j, k;
	vportal_t   *tp, *p;
	float d;
	fixedWinding_t  *w;
	vec3_t dir;


	p = portals + portalnum;

	if ( p->removed ) {
		return;
	}

	p->portalfront = safe_malloc( portalbytes );
	memset( p->portalfront, 0, portalbytes );

	p->portalflood = safe_malloc( portalbytes );
	memset( p->portalflood, 0, portalbytes );

	p->portalvis = safe_malloc( portalbytes );
	memset( p->portalvis, 0, portalbytes );

	for ( j = 0, tp = portals ; j < numportals * 2 ; j++, tp++ )
	{
		if ( j == portalnum ) {
			continue;
		}
		if ( tp->removed ) {
			continue;
		}

		/* ydnar: this is old farplane vis code from mre */
		/*
		   if (farplanedist >= 0)
		   {
		    vec3_t dir;
		    VectorSubtract(p->origin, tp->origin, dir);
		    if (VectorLength(dir) > farplanedist - p->radius - tp->radius)
		        continue;
		   }
		 */

		/* ydnar: this is known-to-be-working farplane code */
		if ( farPlaneDist > 0.0f ) {
			VectorSubtract( p->origin, tp->origin, dir );
			if ( VectorLength( dir ) - p->radius - tp->radius > farPlaneDist ) {
				continue;
			}
		}


		w = tp->winding;
		for ( k = 0 ; k < w->numpoints ; k++ )
		{
			d = DotProduct( w->points[k], p->plane.normal )
				- p->plane.dist;
			if ( d > ON_EPSILON ) {
				break;
			}
		}
		if ( k == w->numpoints ) {
			continue;   // no points on front

		}
		w = p->winding;
		for ( k = 0 ; k < w->numpoints ; k++ )
		{
			d = DotProduct( w->points[k], tp->plane.normal )
				- tp->plane.dist;
			if ( d < -ON_EPSILON ) {
				break;
			}
		}
		if ( k == w->numpoints ) {
			continue;   // no points on front

		}
		p->portalfront[j >> 3] |= ( 1 << ( j & 7 ) );
	}

	SimpleFlood( p, p->leaf );

	pthread_mutex_lock( &portal_mutex );
	p->nummightsee = CountBits( p->portalflood, numportals * 2 );
//	Sys_Printf ("portal %i: %i mightsee\n", portalnum, p->nummightsee);
	c_flood += p->nummightsee;
	pthread_mutex_unlock( &portal_mutex );
}