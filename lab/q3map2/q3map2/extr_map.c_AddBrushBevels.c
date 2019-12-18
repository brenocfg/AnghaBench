#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  float* vec3_t ;
struct TYPE_8__ {size_t planenum; void* bevel; int /*<<< orphan*/  contentFlags; TYPE_1__* winding; } ;
typedef  TYPE_2__ side_t ;
struct TYPE_10__ {int numsides; float* maxs; float* mins; TYPE_2__* sides; int /*<<< orphan*/  brushNum; int /*<<< orphan*/  entityNum; } ;
struct TYPE_9__ {float* normal; } ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (float*,float*,float*) ; 
 float DotProduct (int /*<<< orphan*/ ,float*) ; 
 void* FindFloatPlane (float*,float,int,int /*<<< orphan*/ *) ; 
 int MAX_BUILD_SIDES ; 
 scalar_t__ PlaneEqual (TYPE_4__*,float*,float) ; 
 int /*<<< orphan*/  SnapNormal (float*) ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 float VectorNormalize (float*,float*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 float bevelSnap ; 
 TYPE_5__* buildBrush ; 
 int /*<<< orphan*/  c_boxbevels ; 
 int /*<<< orphan*/  c_edgebevels ; 
 float ceil (float) ; 
 float floor (float) ; 
 TYPE_4__* mapplanes ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 void* qtrue ; 
 int /*<<< orphan*/  xml_Select (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void AddBrushBevels( void ){
	int axis, dir;
	int i, j, k, l, order;
	side_t sidetemp;
	side_t      *s, *s2;
	winding_t   *w, *w2;
	vec3_t normal;
	float dist;
	vec3_t vec, vec2;
	float d, minBack;

	//
	// add the axial planes
	//
	order = 0;
	for ( axis = 0; axis < 3; axis++ ) {
		for ( dir = -1; dir <= 1; dir += 2, order++ ) {
			// see if the plane is allready present
			for ( i = 0, s = buildBrush->sides; i < buildBrush->numsides; i++, s++ )
			{
				/* ydnar: testing disabling of mre code */
				#if 0
				if ( dir > 0 ) {
					if ( mapplanes[s->planenum].normal[axis] >= 0.9999f ) {
						break;
					}
				}
				else {
					if ( mapplanes[s->planenum].normal[axis] <= -0.9999f ) {
						break;
					}
				}
				#else
				if ( ( dir > 0 && mapplanes[ s->planenum ].normal[ axis ] == 1.0f ) ||
					 ( dir < 0 && mapplanes[ s->planenum ].normal[ axis ] == -1.0f ) ) {
					break;
				}
				#endif
			}

			if ( i == buildBrush->numsides ) {
				// add a new side
				if ( buildBrush->numsides == MAX_BUILD_SIDES ) {
					xml_Select( "MAX_BUILD_SIDES", buildBrush->entityNum, buildBrush->brushNum, qtrue );
				}
				memset( s, 0, sizeof( *s ) );
				buildBrush->numsides++;
				VectorClear( normal );
				normal[axis] = dir;

				if ( dir == 1 ) {
					/* ydnar: adding bevel plane snapping for fewer bsp planes */
					if ( bevelSnap > 0 ) {
						dist = floor( buildBrush->maxs[ axis ] / bevelSnap ) * bevelSnap;
					}
					else{
						dist = buildBrush->maxs[ axis ];
					}
				}
				else
				{
					/* ydnar: adding bevel plane snapping for fewer bsp planes */
					if ( bevelSnap > 0 ) {
						dist = -ceil( buildBrush->mins[ axis ] / bevelSnap ) * bevelSnap;
					}
					else{
						dist = -buildBrush->mins[ axis ];
					}
				}

				s->planenum = FindFloatPlane( normal, dist, 0, NULL );
				s->contentFlags = buildBrush->sides[ 0 ].contentFlags;
				s->bevel = qtrue;
				c_boxbevels++;
			}

			// if the plane is not in it canonical order, swap it
			if ( i != order ) {
				sidetemp = buildBrush->sides[order];
				buildBrush->sides[order] = buildBrush->sides[i];
				buildBrush->sides[i] = sidetemp;
			}
		}
	}

	//
	// add the edge bevels
	//
	if ( buildBrush->numsides == 6 ) {
		return;     // pure axial
	}

	// test the non-axial plane edges
	for ( i = 6; i < buildBrush->numsides; i++ ) {
		s = buildBrush->sides + i;
		w = s->winding;
		if ( !w ) {
			continue;
		}
		for ( j = 0; j < w->numpoints; j++ ) {
			k = ( j + 1 ) % w->numpoints;
			VectorSubtract( w->p[j], w->p[k], vec );
			if ( VectorNormalize( vec, vec ) < 0.5f ) {
				continue;
			}
			SnapNormal( vec );
			for ( k = 0; k < 3; k++ ) {
				if ( vec[k] == -1.0f || vec[k] == 1.0f || ( vec[k] == 0.0f && vec[( k + 1 ) % 3] == 0.0f ) ) {
					break;  // axial
				}
			}
			if ( k != 3 ) {
				continue;   // only test non-axial edges
			}

			/* debug code */
			//%	Sys_Printf( "-------------\n" );

			// try the six possible slanted axials from this edge
			for ( axis = 0; axis < 3; axis++ ) {
				for ( dir = -1; dir <= 1; dir += 2 ) {
					// construct a plane
					VectorClear( vec2 );
					vec2[axis] = dir;
					CrossProduct( vec, vec2, normal );
					if ( VectorNormalize( normal, normal ) < 0.5f ) {
						continue;
					}
					dist = DotProduct( w->p[j], normal );

					// if all the points on all the sides are
					// behind this plane, it is a proper edge bevel
					for ( k = 0; k < buildBrush->numsides; k++ ) {

						// if this plane has allready been used, skip it
						if ( PlaneEqual( &mapplanes[buildBrush->sides[k].planenum], normal, dist ) ) {
							break;
						}

						w2 = buildBrush->sides[k].winding;
						if ( !w2 ) {
							continue;
						}
						minBack = 0.0f;
						for ( l = 0; l < w2->numpoints; l++ ) {
							d = DotProduct( w2->p[l], normal ) - dist;
							if ( d > 0.1f ) {
								break;  // point in front
							}
							if ( d < minBack ) {
								minBack = d;
							}
						}
						// if some point was at the front
						if ( l != w2->numpoints ) {
							break;
						}

						// if no points at the back then the winding is on the bevel plane
						if ( minBack > -0.1f ) {
							//%	Sys_Printf( "On bevel plane\n" );
							break;
						}
					}

					if ( k != buildBrush->numsides ) {
						continue;   // wasn't part of the outer hull
					}

					/* debug code */
					//%	Sys_Printf( "n = %f %f %f\n", normal[ 0 ], normal[ 1 ], normal[ 2 ] );

					// add this plane
					if ( buildBrush->numsides == MAX_BUILD_SIDES ) {
						xml_Select( "MAX_BUILD_SIDES", buildBrush->entityNum, buildBrush->brushNum, qtrue );
					}
					s2 = &buildBrush->sides[buildBrush->numsides];
					buildBrush->numsides++;
					memset( s2, 0, sizeof( *s2 ) );

					s2->planenum = FindFloatPlane( normal, dist, 1, &w->p[ j ] );
					s2->contentFlags = buildBrush->sides[0].contentFlags;
					s2->bevel = qtrue;
					c_edgebevels++;
				}
			}
		}
	}
}