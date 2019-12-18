#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ func; float base; int phase; int frequency; float amplitude; } ;
typedef  TYPE_1__ waveForm_t ;
typedef  int byte ;
struct TYPE_10__ {int (* ftol ) (int) ;} ;
struct TYPE_9__ {int shaderTime; int numVertexes; } ;
struct TYPE_8__ {float identityLight; } ;

/* Variables and functions */
 float EvalWaveForm (TYPE_1__ const*) ; 
 scalar_t__ GF_NOISE ; 
 float R_NoiseGet4f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ ri ; 
 int stub1 (int) ; 
 TYPE_3__ tess ; 
 TYPE_2__ tr ; 

void RB_CalcWaveColor( const waveForm_t *wf, unsigned char *dstColors )
{
	int i;
	int v;
	float glow;
	int *colors = ( int * ) dstColors;
	byte	color[4];


  if ( wf->func == GF_NOISE ) {
		glow = wf->base + R_NoiseGet4f( 0, 0, 0, ( tess.shaderTime + wf->phase ) * wf->frequency ) * wf->amplitude;
	} else {
		glow = EvalWaveForm( wf ) * tr.identityLight;
	}
	
	if ( glow < 0 ) {
		glow = 0;
	}
	else if ( glow > 1 ) {
		glow = 1;
	}

	v = ri.ftol(255 * glow);
	color[0] = color[1] = color[2] = v;
	color[3] = 255;
	v = *(int *)color;
	
	for ( i = 0; i < tess.numVertexes; i++, colors++ ) {
		*colors = v;
	}
}