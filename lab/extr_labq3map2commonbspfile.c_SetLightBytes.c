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

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ lightBytes ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int numLightBytes ; 
 scalar_t__ safe_malloc_info (int,char*) ; 

void SetLightBytes( int n ){
	if ( lightBytes != 0 ) {
		free( lightBytes );
	}

	numLightBytes = n;

	if ( n == 0 ) {
		return;
	}

	lightBytes = safe_malloc_info( numLightBytes, "SetLightBytes" );

	memset( lightBytes, 0, numLightBytes );
}