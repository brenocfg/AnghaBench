#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float phase; float frequency; float amplitude; } ;
typedef  TYPE_1__ waveForm_t ;
struct TYPE_5__ {float shaderTime; } ;

/* Variables and functions */
 TYPE_2__ tess ; 

void RB_CalcTurbulentFactors( const waveForm_t *wf, float *amplitude, float *now )
{
	*now = wf->phase + tess.shaderTime * wf->frequency;
	*amplitude = wf->amplitude;
}