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
typedef  float vec_t ;
typedef  float* vec3_t ;

/* Variables and functions */
 scalar_t__ floor (float) ; 

void VectorFSnap( vec3_t point, float snap ){
	int i;
	for ( i = 0 ; i < 3 ; i++ )
	{
		point[i] = (vec_t)floor( point[i] / snap + 0.5 ) * snap;
	}
}