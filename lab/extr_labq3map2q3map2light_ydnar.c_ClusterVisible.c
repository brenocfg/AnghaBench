#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int byte ;

/* Variables and functions */
 int VIS_HEADER_SIZE ; 
 int* bspVisBytes ; 
 int numBSPVisBytes ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean ClusterVisible( int a, int b ){
	int portalClusters, leafBytes;
	byte        *pvs;


	/* dummy check */
	if ( a < 0 || b < 0 ) {
		return qfalse;
	}

	/* early out */
	if ( a == b ) {
		return qtrue;
	}

	/* not vised? */
	if ( numBSPVisBytes <= 8 ) {
		return qtrue;
	}

	/* get pvs data */
	portalClusters = ( (int *) bspVisBytes )[ 0 ];
	leafBytes = ( (int*) bspVisBytes )[ 1 ];
	pvs = bspVisBytes + VIS_HEADER_SIZE + ( a * leafBytes );

	/* check */
	if ( ( pvs[ b >> 3 ] & ( 1 << ( b & 7 ) ) ) ) {
		return qtrue;
	}
	return qfalse;
}