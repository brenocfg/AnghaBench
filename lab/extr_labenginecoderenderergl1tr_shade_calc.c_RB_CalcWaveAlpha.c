#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  waveForm_t ;
struct TYPE_2__ {int numVertexes; } ;

/* Variables and functions */
 float EvalWaveFormClamped (int /*<<< orphan*/  const*) ; 
 TYPE_1__ tess ; 

void RB_CalcWaveAlpha( const waveForm_t *wf, unsigned char *dstColors )
{
	int i;
	int v;
	float glow;

	glow = EvalWaveFormClamped( wf );

	v = 255 * glow;

	for ( i = 0; i < tess.numVertexes; i++, dstColors += 4 )
	{
		dstColors[3] = v;
	}
}