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
struct TYPE_5__ {int width; int height; TYPE_1__* verts; } ;
typedef  TYPE_2__ mesh_t ;
struct TYPE_4__ {double* xyz; double* st; double** lightmap; } ;

/* Variables and functions */
 int MAX_LIGHTMAPS ; 

void PutMeshOnCurve( mesh_t in ) {
	int i, j, l, m;
	float prev, next;


	// put all the aproximating points on the curve
	for ( i = 0 ; i < in.width ; i++ ) {
		for ( j = 1 ; j < in.height ; j += 2 ) {
			for ( l = 0 ; l < 3 ; l++ ) {
				prev = ( in.verts[j * in.width + i].xyz[l] + in.verts[( j + 1 ) * in.width + i].xyz[l] ) * 0.5;
				next = ( in.verts[j * in.width + i].xyz[l] + in.verts[( j - 1 ) * in.width + i].xyz[l] ) * 0.5;
				in.verts[j * in.width + i].xyz[l] = ( prev + next ) * 0.5;

				/* ydnar: interpolating st coords */
				if ( l < 2 ) {
					prev = ( in.verts[j * in.width + i].st[l] + in.verts[( j + 1 ) * in.width + i].st[l] ) * 0.5;
					next = ( in.verts[j * in.width + i].st[l] + in.verts[( j - 1 ) * in.width + i].st[l] ) * 0.5;
					in.verts[j * in.width + i].st[l] = ( prev + next ) * 0.5;

					for ( m = 0; m < MAX_LIGHTMAPS; m++ )
					{
						prev = ( in.verts[j * in.width + i].lightmap[ m ][l] + in.verts[( j + 1 ) * in.width + i].lightmap[ m ][l] ) * 0.5;
						next = ( in.verts[j * in.width + i].lightmap[ m ][l] + in.verts[( j - 1 ) * in.width + i].lightmap[ m ][l] ) * 0.5;
						in.verts[j * in.width + i].lightmap[ m ][l] = ( prev + next ) * 0.5;
					}
				}
			}
		}
	}

	for ( j = 0 ; j < in.height ; j++ ) {
		for ( i = 1 ; i < in.width ; i += 2 ) {
			for ( l = 0 ; l < 3 ; l++ ) {
				prev = ( in.verts[j * in.width + i].xyz[l] + in.verts[j * in.width + i + 1].xyz[l] ) * 0.5;
				next = ( in.verts[j * in.width + i].xyz[l] + in.verts[j * in.width + i - 1].xyz[l] ) * 0.5;
				in.verts[j * in.width + i].xyz[l] = ( prev + next ) * 0.5;

				/* ydnar: interpolating st coords */
				if ( l < 2 ) {
					prev = ( in.verts[j * in.width + i].st[l] + in.verts[j * in.width + i + 1].st[l] ) * 0.5;
					next = ( in.verts[j * in.width + i].st[l] + in.verts[j * in.width + i - 1].st[l] ) * 0.5;
					in.verts[j * in.width + i].st[l] = ( prev + next ) * 0.5;

					for ( m = 0; m < MAX_LIGHTMAPS; m++ )
					{
						prev = ( in.verts[j * in.width + i].lightmap[ m ][l] + in.verts[j * in.width + i + 1].lightmap[ m ][l] ) * 0.5;
						next = ( in.verts[j * in.width + i].lightmap[ m ][l] + in.verts[j * in.width + i - 1].lightmap[ m ][l] ) * 0.5;
						in.verts[j * in.width + i].lightmap[ m ][l] = ( prev + next ) * 0.5;
					}
				}
			}
		}
	}
}