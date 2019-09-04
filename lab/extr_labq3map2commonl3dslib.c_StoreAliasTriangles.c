#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** verts; } ;
struct TYPE_3__ {size_t* v; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ MAXTRIANGLES ; 
 int /*<<< orphan*/ ** fverts ; 
 scalar_t__ numtris ; 
 TYPE_2__* ptri ; 
 scalar_t__ totaltris ; 
 TYPE_1__* tris ; 
 scalar_t__ trisfound ; 
 scalar_t__ vertsfound ; 

void StoreAliasTriangles( void ){
	int i, j, k;

	if ( ( totaltris + numtris ) > MAXTRIANGLES ) {
		Error( "Error: Too many triangles" );
	}

	for ( i = 0; i < numtris ; i++ )
	{
		for ( j = 0 ; j < 3 ; j++ )
		{
			for ( k = 0 ; k < 3 ; k++ )
			{
				ptri[i + totaltris].verts[j][k] = fverts[tris[i].v[j]][k];
			}
		}
	}

	totaltris += numtris;
	numtris = 0;
	vertsfound = 0;
	trisfound = 0;
}