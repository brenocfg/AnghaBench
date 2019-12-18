#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_4__ {int height; int width; TYPE_2__* verts; } ;
typedef  TYPE_1__ mesh_t ;
struct TYPE_5__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_2__ bspDrawVert_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

void MakeMeshNormals( mesh_t in ){
	int i, j, k, dist;
	vec3_t normal;
	vec3_t sum;
	int count;
	vec3_t base;
	vec3_t delta;
	int x, y;
	bspDrawVert_t   *dv;
	vec3_t around[8], temp;
	qboolean good[8];
	qboolean wrapWidth, wrapHeight;
	float len;
	int neighbors[8][2] =
	{
		{0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}
	};


	wrapWidth = qfalse;
	for ( i = 0 ; i < in.height ; i++ ) {
		VectorSubtract( in.verts[i * in.width].xyz,
						in.verts[i * in.width + in.width - 1].xyz, delta );
		len = VectorLength( delta );
		if ( len > 1.0 ) {
			break;
		}
	}
	if ( i == in.height ) {
		wrapWidth = qtrue;
	}

	wrapHeight = qfalse;
	for ( i = 0 ; i < in.width ; i++ ) {
		VectorSubtract( in.verts[i].xyz,
						in.verts[i + ( in.height - 1 ) * in.width].xyz, delta );
		len = VectorLength( delta );
		if ( len > 1.0 ) {
			break;
		}
	}
	if ( i == in.width ) {
		wrapHeight = qtrue;
	}


	for ( i = 0 ; i < in.width ; i++ ) {
		for ( j = 0 ; j < in.height ; j++ ) {
			count = 0;
			dv = &in.verts[j * in.width + i];
			VectorCopy( dv->xyz, base );
			for ( k = 0 ; k < 8 ; k++ ) {
				VectorClear( around[k] );
				good[k] = qfalse;

				for ( dist = 1 ; dist <= 3 ; dist++ ) {
					x = i + neighbors[k][0] * dist;
					y = j + neighbors[k][1] * dist;
					if ( wrapWidth ) {
						if ( x < 0 ) {
							x = in.width - 1 + x;
						}
						else if ( x >= in.width ) {
							x = 1 + x - in.width;
						}
					}
					if ( wrapHeight ) {
						if ( y < 0 ) {
							y = in.height - 1 + y;
						}
						else if ( y >= in.height ) {
							y = 1 + y - in.height;
						}
					}

					if ( x < 0 || x >= in.width || y < 0 || y >= in.height ) {
						break;                  // edge of patch
					}
					VectorSubtract( in.verts[y * in.width + x].xyz, base, temp );
					if ( VectorNormalize( temp, temp ) == 0 ) {
						continue;               // degenerate edge, get more dist
					}
					else {
						good[k] = qtrue;
						VectorCopy( temp, around[k] );
						break;                  // good edge
					}
				}
			}

			VectorClear( sum );
			for ( k = 0 ; k < 8 ; k++ ) {
				if ( !good[k] || !good[( k + 1 ) & 7] ) {
					continue;   // didn't get two points
				}
				CrossProduct( around[( k + 1 ) & 7], around[k], normal );
				if ( VectorNormalize( normal, normal ) == 0 ) {
					continue;
				}
				VectorAdd( normal, sum, sum );
				count++;
			}
			if ( count == 0 ) {
//Sys_Printf("bad normal\n");
				count = 1;
			}
			VectorNormalize( sum, dv->normal );
		}
	}
}