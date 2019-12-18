#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double phase; double frequency; float amplitude; } ;
typedef  TYPE_1__ waveForm_t ;
typedef  size_t int64_t ;
struct TYPE_7__ {double shaderTime; int numVertexes; double** xyz; } ;
struct TYPE_6__ {float* sinTable; } ;

/* Variables and functions */
 size_t FUNCTABLE_MASK ; 
 double FUNCTABLE_SIZE ; 
 TYPE_3__ tess ; 
 TYPE_2__ tr ; 

void RB_CalcTurbulentTexCoords( const waveForm_t *wf, float *st )
{
	int i;
	double now;

	now = ( wf->phase + tess.shaderTime * wf->frequency );

	for ( i = 0; i < tess.numVertexes; i++, st += 2 )
	{
		float s = st[0];
		float t = st[1];

		st[0] = s + tr.sinTable[ ( ( int64_t ) ( ( ( tess.xyz[i][0] + tess.xyz[i][2] )* 1.0/128 * 0.125 + now ) * FUNCTABLE_SIZE ) ) & ( FUNCTABLE_MASK ) ] * wf->amplitude;
		st[1] = t + tr.sinTable[ ( ( int64_t ) ( ( tess.xyz[i][1] * 1.0/128 * 0.125 + now ) * FUNCTABLE_SIZE ) ) & ( FUNCTABLE_MASK ) ] * wf->amplitude;
	}
}