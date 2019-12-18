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
typedef  double vec_t ;
typedef  double* vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorClear (double*) ; 
 double sqrt (double) ; 

vec_t VectorNormalize(vec3_t inout)
{
	vec_t	length, ilength;

	length = sqrt (inout[0]*inout[0] + inout[1]*inout[1] + inout[2]*inout[2]);
	if (length == 0)
	{
		VectorClear (inout);
		return 0;
	}

	ilength = 1.0/length;
	inout[0] = inout[0]*ilength;
	inout[1] = inout[1]*ilength;
	inout[2] = inout[2]*ilength;

	return length;
}