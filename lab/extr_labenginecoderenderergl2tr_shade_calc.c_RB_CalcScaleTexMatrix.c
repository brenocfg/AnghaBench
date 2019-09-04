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

void RB_CalcScaleTexMatrix( const float scale[2], float *matrix )
{
	matrix[0] = scale[0]; matrix[2] = 0.0f;     matrix[4] = 0.0f;
	matrix[1] = 0.0f;     matrix[3] = scale[1]; matrix[5] = 0.0f;
}