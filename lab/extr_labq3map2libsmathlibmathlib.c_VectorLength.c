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
 scalar_t__ sqrt (float) ; 

vec_t VectorLength( vec3_t v ){
	int i;
	float length;

	length = 0.0f;
	for ( i = 0 ; i < 3 ; i++ )
		length += v[i] * v[i];
	length = (float)sqrt( length );

	return length;
}