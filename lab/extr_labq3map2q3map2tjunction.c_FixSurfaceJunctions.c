#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  verts ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_10__ {int numVerts; TYPE_4__* verts; } ;
typedef  TYPE_1__ mapDrawSurface_t ;
struct TYPE_11__ {float intercept; struct TYPE_11__* prev; struct TYPE_11__* next; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_2__ edgePoint_t ;
struct TYPE_12__ {TYPE_2__ chain; int /*<<< orphan*/  dir; int /*<<< orphan*/  origin; } ;
typedef  TYPE_3__ edgeLine_t ;
typedef  scalar_t__ byte ;
struct TYPE_13__ {float* st; scalar_t__** color; int /*<<< orphan*/  normal; int /*<<< orphan*/  xyz; scalar_t__** lightmap; } ;
typedef  TYPE_4__ bspDrawVert_t ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_LIGHTMAPS ; 
 int MAX_SURFACE_VERTS ; 
 float ON_EPSILON ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int c_addedVerts ; 
 int /*<<< orphan*/  c_cant ; 
 int /*<<< orphan*/  c_natural ; 
 int /*<<< orphan*/  c_rotate ; 
 int c_totalVerts ; 
 TYPE_3__* edgeLines ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 void* safe_malloc (int) ; 

void FixSurfaceJunctions( mapDrawSurface_t *ds ) {
	int i, j, k;
	edgeLine_t  *e;
	edgePoint_t *p;
	int originalVerts;
	int counts[MAX_SURFACE_VERTS];
	int originals[MAX_SURFACE_VERTS];
	int firstVert[MAX_SURFACE_VERTS];
	bspDrawVert_t verts[MAX_SURFACE_VERTS], *v1, *v2;
	int numVerts;
	float start, end, frac, c;
	vec3_t delta;


	originalVerts = ds->numVerts;

	numVerts = 0;
	for ( i = 0 ; i < ds->numVerts ; i++ )
	{
		counts[i] = 0;
		firstVert[i] = numVerts;

		// copy first vert
		if ( numVerts == MAX_SURFACE_VERTS ) {
			Error( "MAX_SURFACE_VERTS" );
		}
		verts[numVerts] = ds->verts[i];
		originals[numVerts] = i;
		numVerts++;

		// check to see if there are any t junctions before the next vert
		v1 = &ds->verts[i];
		v2 = &ds->verts[ ( i + 1 ) % ds->numVerts ];

		j = (int)ds->verts[i].lightmap[ 0 ][ 0 ];
		if ( j == -1 ) {
			continue;       // degenerate edge
		}
		e = &edgeLines[ j ];

		VectorSubtract( v1->xyz, e->origin, delta );
		start = DotProduct( delta, e->dir );

		VectorSubtract( v2->xyz, e->origin, delta );
		end = DotProduct( delta, e->dir );


		if ( start < end ) {
			p = e->chain.next;
		}
		else {
			p = e->chain.prev;
		}

		for (  ; p != &e->chain ; ) {
			if ( start < end ) {
				if ( p->intercept > end - ON_EPSILON ) {
					break;
				}
			}
			else {
				if ( p->intercept < end + ON_EPSILON ) {
					break;
				}
			}

			if (
				( start < end && p->intercept > start + ON_EPSILON ) ||
				( start > end && p->intercept < start - ON_EPSILON ) ) {
				// insert this point
				if ( numVerts == MAX_SURFACE_VERTS ) {
					Error( "MAX_SURFACE_VERTS" );
				}
				memset(&verts[ numVerts ], 0, sizeof(verts[ numVerts ]));

				/* take the exact intercept point */
				VectorCopy( p->xyz, verts[ numVerts ].xyz );

				/* interpolate the texture coordinates */
				frac = ( p->intercept - start ) / ( end - start );
				for ( j = 0 ; j < 2 ; j++ ) {
					verts[ numVerts ].st[j] = v1->st[j] +
											  frac * ( v2->st[j] - v1->st[j] );
				}

				/* copy the normal (FIXME: what about nonplanar surfaces? */
				VectorCopy( v1->normal, verts[ numVerts ].normal );

				/* ydnar: interpolate the color */
				for ( k = 0; k < MAX_LIGHTMAPS; k++ )
				{
					for ( j = 0; j < 4; j++ )
					{
						c = (float) v1->color[ k ][ j ] + frac * ( (float) v2->color[ k ][ j ] - (float) v1->color[ k ][ j ] );
						verts[ numVerts ].color[ k ][ j ] = (byte) ( c < 255.0f ? c : 255 );
					}
				}

				/* next... */
				originals[ numVerts ] = i;
				numVerts++;
				counts[ i ]++;
			}

			if ( start < end ) {
				p = p->next;
			}
			else {
				p = p->prev;
			}
		}
	}

	c_addedVerts += numVerts - ds->numVerts;
	c_totalVerts += numVerts;


	// FIXME: check to see if the entire surface degenerated
	// after snapping

	// rotate the points so that the initial vertex is between
	// two non-subdivided edges
	for ( i = 0 ; i < numVerts ; i++ ) {
		if ( originals[ ( i + 1 ) % numVerts ] == originals[ i ] ) {
			continue;
		}
		j = ( i + numVerts - 1 ) % numVerts;
		k = ( i + numVerts - 2 ) % numVerts;
		if ( originals[ j ] == originals[ k ] ) {
			continue;
		}
		break;
	}

	if ( i == 0 ) {
		// fine the way it is
		c_natural++;

		ds->numVerts = numVerts;
		ds->verts = safe_malloc( numVerts * sizeof( *ds->verts ) );
		memcpy( ds->verts, verts, numVerts * sizeof( *ds->verts ) );

		return;
	}
	if ( i == numVerts ) {
		// create a vertex in the middle to start the fan
		c_cant++;

/*
        memset ( &verts[numVerts], 0, sizeof( verts[numVerts] ) );
        for ( i = 0 ; i < numVerts ; i++ ) {
            for ( j = 0 ; j < 10 ; j++ ) {
                verts[numVerts].xyz[j] += verts[i].xyz[j];
            }
        }
        for ( j = 0 ; j < 10 ; j++ ) {
            verts[numVerts].xyz[j] /= numVerts;
        }

        i = numVerts;
        numVerts++;
 */
	}
	else {
		// just rotate the vertexes
		c_rotate++;

	}

	ds->numVerts = numVerts;
	ds->verts = safe_malloc( numVerts * sizeof( *ds->verts ) );

	for ( j = 0 ; j < ds->numVerts ; j++ ) {
		ds->verts[j] = verts[ ( j + i ) % ds->numVerts ];
	}
}