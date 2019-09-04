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
typedef  float* m3x3_t ;

/* Variables and functions */

float m3_det( m3x3_t mat ){
	float det;

	det = mat[0] * ( mat[4] * mat[8] - mat[7] * mat[5] )
		  - mat[1] * ( mat[3] * mat[8] - mat[6] * mat[5] )
		  + mat[2] * ( mat[3] * mat[7] - mat[6] * mat[4] );

	return( det );
}