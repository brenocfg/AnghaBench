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
 int pow (int,int) ; 

int IterationsForCurve( float len, int subdivisions ){
	int iterations, facets;


	/* calculate the number of subdivisions */
	for ( iterations = 0; iterations < 3; iterations++ )
	{
		facets = subdivisions * 16 * pow( 2, iterations );
		if ( facets >= len ) {
			break;
		}
	}

	/* return to caller */
	return iterations;
}