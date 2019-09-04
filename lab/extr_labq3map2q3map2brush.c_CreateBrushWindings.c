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
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_7__ {size_t planenum; int /*<<< orphan*/ * winding; scalar_t__ bevel; } ;
typedef  TYPE_1__ side_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_8__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_9__ {int numsides; TYPE_1__* sides; } ;
typedef  TYPE_3__ brush_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BaseWindingForPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BoundBrush (TYPE_3__*) ; 
 int /*<<< orphan*/  ChopWindingInPlace (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FixWinding (int /*<<< orphan*/ *) ; 
 TYPE_2__* mapplanes ; 

qboolean CreateBrushWindings( brush_t *brush ){
	int i, j;
#if Q3MAP2_EXPERIMENTAL_HIGH_PRECISION_MATH_FIXES
	winding_accu_t  *w;
#else
	winding_t   *w;
#endif
	side_t      *side;
	plane_t     *plane;


	/* walk the list of brush sides */
	for ( i = 0; i < brush->numsides; i++ )
	{
		/* get side and plane */
		side = &brush->sides[ i ];
		plane = &mapplanes[ side->planenum ];

		/* make huge winding */
#if Q3MAP2_EXPERIMENTAL_HIGH_PRECISION_MATH_FIXES
		w = BaseWindingForPlaneAccu( plane->normal, plane->dist );
#else
		w = BaseWindingForPlane( plane->normal, plane->dist );
#endif

		/* walk the list of brush sides */
		for ( j = 0; j < brush->numsides && w != NULL; j++ )
		{
			if ( i == j ) {
				continue;
			}
			if ( brush->sides[ j ].planenum == ( brush->sides[ i ].planenum ^ 1 ) ) {
				continue;       /* back side clipaway */
			}
			if ( brush->sides[ j ].bevel ) {
				continue;
			}
			plane = &mapplanes[ brush->sides[ j ].planenum ^ 1 ];
#if Q3MAP2_EXPERIMENTAL_HIGH_PRECISION_MATH_FIXES
			ChopWindingInPlaceAccu( &w, plane->normal, plane->dist, 0 );
#else
			ChopWindingInPlace( &w, plane->normal, plane->dist, 0 ); // CLIP_EPSILON );
#endif

			/* ydnar: fix broken windings that would generate trifans */
#if Q3MAP2_EXPERIMENTAL_HIGH_PRECISION_MATH_FIXES
			// I think it's better to FixWindingAccu() once after we chop with all planes
			// so that error isn't multiplied.  There is nothing natural about welding
			// the points unless they are the final endpoints.  ChopWindingInPlaceAccu()
			// is able to handle all kinds of degenerate windings.
#else
			FixWinding( w );
#endif
		}

		/* set side winding */
#if Q3MAP2_EXPERIMENTAL_HIGH_PRECISION_MATH_FIXES
		if ( w != NULL ) {
			FixWindingAccu( w );
			if ( w->numpoints < 3 ) {
				FreeWindingAccu( w );
				w = NULL;
			}
		}
		side->winding = ( w ? CopyWindingAccuToRegular( w ) : NULL );
		if ( w ) {
			FreeWindingAccu( w );
		}
#else
		side->winding = w;
#endif
	}

	/* find brush bounds */
	return BoundBrush( brush );
}