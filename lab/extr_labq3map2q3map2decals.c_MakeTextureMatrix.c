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
typedef  double* vec4_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  double* dvec3_t ;
struct TYPE_7__ {double** texMat; } ;
typedef  TYPE_1__ decalProjector_t ;
struct TYPE_8__ {double* xyz; double* st; } ;
typedef  TYPE_2__ bspDrawVert_t ;

/* Variables and functions */
 double DVectorNormalize (double*,double*) ; 
 double DotProduct (double*,double*) ; 
 int /*<<< orphan*/  RAD2DEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sys_Printf (char*,double,double,double,double,...) ; 
 int /*<<< orphan*/  VectorMA (double*,double,double*,double*) ; 
 int /*<<< orphan*/  VectorScale (double*,double,double*) ; 
 int /*<<< orphan*/  VectorSubtract (double*,double*,double*) ; 
 int /*<<< orphan*/  acos (double) ; 
 double fabs (double) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean MakeTextureMatrix( decalProjector_t *dp, vec4_t projection, bspDrawVert_t *a, bspDrawVert_t *b, bspDrawVert_t *c ){
	int i, j;
	double bb, s, t, d;
	dvec3_t pa, pb, pc;
	dvec3_t bary, xyz;
	dvec3_t vecs[ 3 ], axis[ 3 ], lengths;


	/* project triangle onto plane of projection */
	d = DotProduct( a->xyz, projection ) - projection[ 3 ];
	VectorMA( a->xyz, -d, projection, pa );
	d = DotProduct( b->xyz, projection ) - projection[ 3 ];
	VectorMA( b->xyz, -d, projection, pb );
	d = DotProduct( c->xyz, projection ) - projection[ 3 ];
	VectorMA( c->xyz, -d, projection, pc );

	/* two methods */
	#if 1
	{
		/* old code */

		/* calculate barycentric basis for the triangle */
		bb = ( b->st[ 0 ] - a->st[ 0 ] ) * ( c->st[ 1 ] - a->st[ 1 ] ) - ( c->st[ 0 ] - a->st[ 0 ] ) * ( b->st[ 1 ] - a->st[ 1 ] );
		if ( fabs( bb ) < 0.00000001 ) {
			return qfalse;
		}

		/* calculate texture origin */
		#if 0
		s = 0.0;
		t = 0.0;
		bary[ 0 ] = ( ( b->st[ 0 ] - s ) * ( c->st[ 1 ] - t ) - ( c->st[ 0 ] - s ) * ( b->st[ 1 ] - t ) ) / bb;
		bary[ 1 ] = ( ( c->st[ 0 ] - s ) * ( a->st[ 1 ] - t ) - ( a->st[ 0 ] - s ) * ( c->st[ 1 ] - t ) ) / bb;
		bary[ 2 ] = ( ( a->st[ 0 ] - s ) * ( b->st[ 1 ] - t ) - ( b->st[ 0 ] - s ) * ( a->st[ 1 ] - t ) ) / bb;

		origin[ 0 ] = bary[ 0 ] * pa[ 0 ] + bary[ 1 ] * pb[ 0 ] + bary[ 2 ] * pc[ 0 ];
		origin[ 1 ] = bary[ 0 ] * pa[ 1 ] + bary[ 1 ] * pb[ 1 ] + bary[ 2 ] * pc[ 1 ];
		origin[ 2 ] = bary[ 0 ] * pa[ 2 ] + bary[ 1 ] * pb[ 2 ] + bary[ 2 ] * pc[ 2 ];
		#endif

		/* calculate s vector */
		s = a->st[ 0 ] + 1.0;
		t = a->st[ 1 ] + 0.0;
		bary[ 0 ] = ( ( b->st[ 0 ] - s ) * ( c->st[ 1 ] - t ) - ( c->st[ 0 ] - s ) * ( b->st[ 1 ] - t ) ) / bb;
		bary[ 1 ] = ( ( c->st[ 0 ] - s ) * ( a->st[ 1 ] - t ) - ( a->st[ 0 ] - s ) * ( c->st[ 1 ] - t ) ) / bb;
		bary[ 2 ] = ( ( a->st[ 0 ] - s ) * ( b->st[ 1 ] - t ) - ( b->st[ 0 ] - s ) * ( a->st[ 1 ] - t ) ) / bb;

		xyz[ 0 ] = bary[ 0 ] * pa[ 0 ] + bary[ 1 ] * pb[ 0 ] + bary[ 2 ] * pc[ 0 ];
		xyz[ 1 ] = bary[ 0 ] * pa[ 1 ] + bary[ 1 ] * pb[ 1 ] + bary[ 2 ] * pc[ 1 ];
		xyz[ 2 ] = bary[ 0 ] * pa[ 2 ] + bary[ 1 ] * pb[ 2 ] + bary[ 2 ] * pc[ 2 ];

		//%	VectorSubtract( xyz, origin, vecs[ 0 ] );
		VectorSubtract( xyz, pa, vecs[ 0 ] );

		/* calculate t vector */
		s = a->st[ 0 ] + 0.0;
		t = a->st[ 1 ] + 1.0;
		bary[ 0 ] = ( ( b->st[ 0 ] - s ) * ( c->st[ 1 ] - t ) - ( c->st[ 0 ] - s ) * ( b->st[ 1 ] - t ) ) / bb;
		bary[ 1 ] = ( ( c->st[ 0 ] - s ) * ( a->st[ 1 ] - t ) - ( a->st[ 0 ] - s ) * ( c->st[ 1 ] - t ) ) / bb;
		bary[ 2 ] = ( ( a->st[ 0 ] - s ) * ( b->st[ 1 ] - t ) - ( b->st[ 0 ] - s ) * ( a->st[ 1 ] - t ) ) / bb;

		xyz[ 0 ] = bary[ 0 ] * pa[ 0 ] + bary[ 1 ] * pb[ 0 ] + bary[ 2 ] * pc[ 0 ];
		xyz[ 1 ] = bary[ 0 ] * pa[ 1 ] + bary[ 1 ] * pb[ 1 ] + bary[ 2 ] * pc[ 1 ];
		xyz[ 2 ] = bary[ 0 ] * pa[ 2 ] + bary[ 1 ] * pb[ 2 ] + bary[ 2 ] * pc[ 2 ];

		//%	VectorSubtract( xyz, origin, vecs[ 1 ] );
		VectorSubtract( xyz, pa, vecs[ 1 ] );

		/* calcuate r vector */
		VectorScale( projection, -1.0, vecs[ 2 ] );

		/* calculate transform axis */
		for ( i = 0; i < 3; i++ )
			lengths[ i ] = DVectorNormalize( vecs[ i ], axis[ i ] );
		for ( i = 0; i < 2; i++ )
			for ( j = 0; j < 3; j++ )
				dp->texMat[ i ][ j ] = lengths[ i ] > 0.0 ? ( axis[ i ][ j ] / lengths[ i ] ) : 0.0;
		//%	dp->texMat[ i ][ j ] = fabs( vecs[ i ][ j ] ) > 0.0 ? (1.0 / vecs[ i ][ j ]) : 0.0;
		//%	dp->texMat[ i ][ j ] = axis[ i ][ j ] > 0.0 ? (1.0 / axis[ i ][ j ]) : 0.0;

		/* calculalate translation component */
		dp->texMat[ 0 ][ 3 ] = a->st[ 0 ] - DotProduct( a->xyz, dp->texMat[ 0 ] );
		dp->texMat[ 1 ][ 3 ] = a->st[ 1 ] - DotProduct( a->xyz, dp->texMat[ 1 ] );
	}
	#else
	{
		int k;
		dvec3_t origin, deltas[ 3 ];
		double texDeltas[ 3 ][ 2 ];
		double delta, texDelta;


		/* new code */

		/* calculate deltas */
		VectorSubtract( pa, pb, deltas[ 0 ] );
		VectorSubtract( pa, pc, deltas[ 1 ] );
		VectorSubtract( pb, pc, deltas[ 2 ] );
		Vector2Subtract( a->st, b->st, texDeltas[ 0 ] );
		Vector2Subtract( a->st, c->st, texDeltas[ 1 ] );
		Vector2Subtract( b->st, c->st, texDeltas[ 2 ] );

		/* walk st */
		for ( i = 0; i < 2; i++ )
		{
			/* walk xyz */
			for ( j = 0; j < 3; j++ )
			{
				/* clear deltas */
				delta = 0.0;
				texDelta = 0.0;

				/* walk deltas */
				for ( k = 0; k < 3; k++ )
				{
					if ( fabs( deltas[ k ][ j ] ) > delta &&
						 fabs( texDeltas[ k ][ i ] ) > texDelta  ) {
						delta = deltas[ k ][ j ];
						texDelta = texDeltas[ k ][ i ];
					}
				}

				/* set texture matrix component */
				if ( fabs( delta ) > 0.0 ) {
					dp->texMat[ i ][ j ] = texDelta / delta;
				}
				else{
					dp->texMat[ i ][ j ] = 0.0;
				}
			}

			/* set translation component */
			dp->texMat[ i ][ 3 ] = a->st[ i ] - DotProduct( pa, dp->texMat[ i ] );
		}
	}
	#endif

	/* debug code */
	#if 1
	Sys_Printf( "Mat: [ %f %f %f %f ] [ %f %f %f %f ] Theta: %f (%f)\n",
				dp->texMat[ 0 ][ 0 ], dp->texMat[ 0 ][ 1 ], dp->texMat[ 0 ][ 2 ], dp->texMat[ 0 ][ 3 ],
				dp->texMat[ 1 ][ 0 ], dp->texMat[ 1 ][ 1 ], dp->texMat[ 1 ][ 2 ], dp->texMat[ 1 ][ 3 ],
				RAD2DEG( acos( DotProduct( dp->texMat[ 0 ], dp->texMat[ 1 ] ) ) ),
				RAD2DEG( acos( DotProduct( axis[ 0 ], axis[ 1 ] ) ) ) );

	Sys_Printf( "XYZ: %f %f %f ST: %f %f ST(t): %f %f\n",
				a->xyz[ 0 ], a->xyz[ 1 ], a->xyz[ 2 ],
				a->st[ 0 ], a->st[ 1 ],
				DotProduct( a->xyz, dp->texMat[ 0 ] ) + dp->texMat[ 0 ][ 3 ], DotProduct( a->xyz, dp->texMat[ 1 ] ) + dp->texMat[ 1 ][ 3 ] );
	#endif

	/* test texture matrix */
	s = DotProduct( a->xyz, dp->texMat[ 0 ] ) + dp->texMat[ 0 ][ 3 ];
	t = DotProduct( a->xyz, dp->texMat[ 1 ] ) + dp->texMat[ 1 ][ 3 ];
	if ( fabs( s - a->st[ 0 ] ) > 0.01 || fabs( t - a->st[ 1 ] ) > 0.01 ) {
		Sys_Printf( "Bad texture matrix! (A) (%f, %f) != (%f, %f)\n",
					s, t, a->st[ 0 ], a->st[ 1 ] );
		//%	return qfalse;
	}
	s = DotProduct( b->xyz, dp->texMat[ 0 ] ) + dp->texMat[ 0 ][ 3 ];
	t = DotProduct( b->xyz, dp->texMat[ 1 ] ) + dp->texMat[ 1 ][ 3 ];
	if ( fabs( s - b->st[ 0 ] ) > 0.01 || fabs( t - b->st[ 1 ] ) > 0.01 ) {
		Sys_Printf( "Bad texture matrix! (B) (%f, %f) != (%f, %f)\n",
					s, t, b->st[ 0 ], b->st[ 1 ] );
		//%	return qfalse;
	}
	s = DotProduct( c->xyz, dp->texMat[ 0 ] ) + dp->texMat[ 0 ][ 3 ];
	t = DotProduct( c->xyz, dp->texMat[ 1 ] ) + dp->texMat[ 1 ][ 3 ];
	if ( fabs( s - c->st[ 0 ] ) > 0.01 || fabs( t - c->st[ 1 ] ) > 0.01 ) {
		Sys_Printf( "Bad texture matrix! (C) (%f, %f) != (%f, %f)\n",
					s, t, c->st[ 0 ], c->st[ 1 ] );
		//%	return qfalse;
	}

	/* disco */
	return qtrue;
}