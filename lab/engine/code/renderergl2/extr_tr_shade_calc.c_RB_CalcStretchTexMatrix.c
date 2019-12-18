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
typedef  int /*<<< orphan*/  waveForm_t ;

/* Variables and functions */
 float EvalWaveForm (int /*<<< orphan*/  const*) ; 

void RB_CalcStretchTexMatrix( const waveForm_t *wf, float *matrix )
{
	float p;

	p = 1.0f / EvalWaveForm( wf );

	matrix[0] = p; matrix[2] = 0; matrix[4] = 0.5f - 0.5f * p;
	matrix[1] = 0; matrix[3] = p; matrix[5] = 0.5f - 0.5f * p;
}