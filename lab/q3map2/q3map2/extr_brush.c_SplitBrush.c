#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  double vec_t ;
struct TYPE_29__ {int planenum; TYPE_1__* winding; int /*<<< orphan*/ * shaderInfo; } ;
typedef  TYPE_2__ side_t ;
struct TYPE_30__ {float dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ plane_t ;
struct TYPE_31__ {int numsides; TYPE_2__* sides; int /*<<< orphan*/  original; int /*<<< orphan*/ * next; } ;
typedef  TYPE_4__ brush_t ;

/* Variables and functions */
 TYPE_4__* AllocBrush (int) ; 
 TYPE_1__* BaseWindingForPlane (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  BoundBrush (TYPE_4__*) ; 
 int BrushMostlyOnSide (TYPE_4__*,TYPE_3__*) ; 
 double BrushVolume (TYPE_4__*) ; 
 int /*<<< orphan*/  ChopWindingInPlace (TYPE_1__**,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClipWindingEpsilon (TYPE_1__*,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,TYPE_1__**,TYPE_1__**) ; 
 TYPE_4__* CopyBrush (TYPE_4__*) ; 
 TYPE_1__* CopyWinding (TYPE_1__*) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBrush (TYPE_4__*) ; 
 int PSIDE_BACK ; 
 int PSIDE_FRONT ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ WindingIsHuge (TYPE_1__*) ; 
 scalar_t__ WindingIsTiny (TYPE_1__*) ; 
 TYPE_3__* mapplanes ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 

void SplitBrush( brush_t *brush, int planenum, brush_t **front, brush_t **back ){
	brush_t     *b[2];
	int i, j;
	winding_t   *w, *cw[2], *midwinding;
	plane_t     *plane, *plane2;
	side_t      *s, *cs;
	float d, d_front, d_back;


	*front = NULL;
	*back = NULL;
	plane = &mapplanes[planenum];

	// check all points
	d_front = d_back = 0;
	for ( i = 0 ; i < brush->numsides ; i++ )
	{
		w = brush->sides[i].winding;
		if ( !w ) {
			continue;
		}
		for ( j = 0 ; j < w->numpoints ; j++ )
		{
			d = DotProduct( w->p[j], plane->normal ) - plane->dist;
			if ( d > 0 && d > d_front ) {
				d_front = d;
			}
			if ( d < 0 && d < d_back ) {
				d_back = d;
			}
		}
	}

	if ( d_front < 0.1 ) { // PLANESIDE_EPSILON)
		// only on back
		*back = CopyBrush( brush );
		return;
	}

	if ( d_back > -0.1 ) { // PLANESIDE_EPSILON)
		// only on front
		*front = CopyBrush( brush );
		return;
	}

	// create a new winding from the split plane
	w = BaseWindingForPlane( plane->normal, plane->dist );
	for ( i = 0 ; i < brush->numsides && w ; i++ )
	{
		plane2 = &mapplanes[brush->sides[i].planenum ^ 1];
		ChopWindingInPlace( &w, plane2->normal, plane2->dist, 0 ); // PLANESIDE_EPSILON);
	}

	if ( !w || WindingIsTiny( w ) ) { // the brush isn't really split
		int side;

		side = BrushMostlyOnSide( brush, plane );
		if ( side == PSIDE_FRONT ) {
			*front = CopyBrush( brush );
		}
		if ( side == PSIDE_BACK ) {
			*back = CopyBrush( brush );
		}
		return;
	}

	if ( WindingIsHuge( w ) ) {
		Sys_FPrintf( SYS_VRB,"WARNING: huge winding\n" );
	}

	midwinding = w;

	// split it for real

	for ( i = 0 ; i < 2 ; i++ )
	{
		b[i] = AllocBrush( brush->numsides + 1 );
		memcpy( b[i], brush, sizeof( brush_t ) );
		b[i]->numsides = 0;
		b[i]->next = NULL;
		b[i]->original = brush->original;
	}

	// split all the current windings

	for ( i = 0 ; i < brush->numsides ; i++ )
	{
		s = &brush->sides[i];
		w = s->winding;
		if ( !w ) {
			continue;
		}
		ClipWindingEpsilon( w, plane->normal, plane->dist,
							0 /*PLANESIDE_EPSILON*/, &cw[0], &cw[1] );
		for ( j = 0 ; j < 2 ; j++ )
		{
			if ( !cw[j] ) {
				continue;
			}
			cs = &b[j]->sides[b[j]->numsides];
			b[j]->numsides++;
			*cs = *s;
			cs->winding = cw[j];
		}
	}


	// see if we have valid polygons on both sides
	for ( i = 0 ; i < 2 ; i++ )
	{
		if ( b[i]->numsides < 3 || !BoundBrush( b[i] ) ) {
			if ( b[i]->numsides >= 3 ) {
				Sys_FPrintf( SYS_VRB,"bogus brush after clip\n" );
			}
			FreeBrush( b[i] );
			b[i] = NULL;
		}
	}

	if ( !( b[0] && b[1] ) ) {
		if ( !b[0] && !b[1] ) {
			Sys_FPrintf( SYS_VRB,"split removed brush\n" );
		}
		else{
			Sys_FPrintf( SYS_VRB,"split not on both sides\n" );
		}
		if ( b[0] ) {
			FreeBrush( b[0] );
			*front = CopyBrush( brush );
		}
		if ( b[1] ) {
			FreeBrush( b[1] );
			*back = CopyBrush( brush );
		}
		return;
	}

	// add the midwinding to both sides
	for ( i = 0 ; i < 2 ; i++ )
	{
		cs = &b[i]->sides[b[i]->numsides];
		b[i]->numsides++;

		cs->planenum = planenum ^ i ^ 1;
		cs->shaderInfo = NULL;
		if ( i == 0 ) {
			cs->winding = CopyWinding( midwinding );
		}
		else{
			cs->winding = midwinding;
		}
	}

	{
		vec_t v1;
		int i;


		for ( i = 0 ; i < 2 ; i++ )
		{
			v1 = BrushVolume( b[i] );
			if ( v1 < 1.0 ) {
				FreeBrush( b[i] );
				b[i] = NULL;
				//			Sys_FPrintf (SYS_VRB,"tiny volume after clip\n");
			}
		}
	}

	*front = b[0];
	*back = b[1];
}