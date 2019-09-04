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
typedef  float* vec3_t ;

/* Variables and functions */
 float cos (float) ; 
 float sin (float) ; 

void VectorPolar( vec3_t v, float radius, float theta, float phi ){
	v[0] = (float)( radius * cos( theta ) * cos( phi ) );
	v[1] = (float)( radius * sin( theta ) * cos( phi ) );
	v[2] = (float)( radius * sin( phi ) );
}