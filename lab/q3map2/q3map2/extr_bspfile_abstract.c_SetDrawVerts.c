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
typedef  int /*<<< orphan*/  bspDrawVert_t ;

/* Variables and functions */
 scalar_t__ bspDrawVerts ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int numBSPDrawVerts ; 
 int numBSPDrawVertsBuffer ; 
 scalar_t__ safe_malloc_info (int,char*) ; 

void SetDrawVerts( int n ){
	if ( bspDrawVerts != 0 ) {
		free( bspDrawVerts );
	}

	numBSPDrawVerts = n;
	numBSPDrawVertsBuffer = numBSPDrawVerts;

	bspDrawVerts = safe_malloc_info( sizeof( bspDrawVert_t ) * numBSPDrawVertsBuffer, "IncDrawVerts" );

	memset( bspDrawVerts, 0, n * sizeof( bspDrawVert_t ) );
}