#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float** matrix; float* translate; } ;
typedef  TYPE_1__ texModInfo_t ;

/* Variables and functions */

void RB_CalcTransformTexMatrix( const texModInfo_t *tmi, float *matrix  )
{
	matrix[0] = tmi->matrix[0][0]; matrix[2] = tmi->matrix[1][0]; matrix[4] = tmi->translate[0];
	matrix[1] = tmi->matrix[0][1]; matrix[3] = tmi->matrix[1][1]; matrix[5] = tmi->translate[1];
}