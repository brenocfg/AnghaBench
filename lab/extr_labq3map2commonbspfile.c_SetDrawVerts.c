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
typedef  int /*<<< orphan*/  drawVert_t ;

/* Variables and functions */
 scalar_t__ drawVerts ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int numDrawVerts ; 
 int numDrawVertsBuffer ; 
 scalar_t__ safe_malloc_info (int,char*) ; 

void SetDrawVerts( int n ){
	if ( drawVerts != 0 ) {
		free( drawVerts );
	}

	numDrawVerts = n;
	numDrawVertsBuffer = numDrawVerts;

	drawVerts = safe_malloc_info( sizeof( drawVert_t ) * numDrawVertsBuffer, "IncDrawVerts" );

	memset( drawVerts, 0, n * sizeof( drawVert_t ) );
}