#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double time; double floatTime; scalar_t__ vertFlipBuffer; } ;
struct TYPE_6__ {scalar_t__ vertFlipBuffer; } ;
struct TYPE_10__ {TYPE_2__ refdef; TYPE_1__ viewParms; int /*<<< orphan*/  projection2D; } ;
struct TYPE_9__ {int /*<<< orphan*/  vidHeight; int /*<<< orphan*/  vidWidth; } ;
struct TYPE_8__ {double (* Milliseconds ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CT_TWO_SIDED ; 
 int GLS_DEPTHTEST_DISABLE ; 
 int GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA ; 
 int GLS_SRCBLEND_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_CLIP_PLANE0 ; 
 int /*<<< orphan*/  GL_Cull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_State (int) ; 
 TYPE_5__ backEnd ; 
 TYPE_4__ glConfig ; 
 int /*<<< orphan*/  qglDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglLoadIdentity () ; 
 int /*<<< orphan*/  qglMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglOrtho (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qglScissor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_3__ ri ; 
 double stub1 () ; 

void	RB_SetGL2D (void) {
	backEnd.projection2D = qtrue;
	backEnd.viewParms.vertFlipBuffer = backEnd.refdef.vertFlipBuffer;

	// set 2D virtual screen size
	qglViewport( 0, 0, glConfig.vidWidth, glConfig.vidHeight );
	qglScissor( 0, 0, glConfig.vidWidth, glConfig.vidHeight );
	qglMatrixMode(GL_PROJECTION);
    qglLoadIdentity ();
	if(backEnd.viewParms.vertFlipBuffer)
	{
		qglOrtho (0, glConfig.vidWidth, 0, glConfig.vidHeight, 0, 1);
	}
	else
	{
		qglOrtho (0, glConfig.vidWidth, glConfig.vidHeight, 0, 0, 1);
	}
	qglMatrixMode(GL_MODELVIEW);
    qglLoadIdentity ();

	GL_State( GLS_DEPTHTEST_DISABLE |
			  GLS_SRCBLEND_SRC_ALPHA |
			  GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA );

	GL_Cull( CT_TWO_SIDED );
	qglDisable( GL_CLIP_PLANE0 );

	// set time for 2D shaders
	backEnd.refdef.time = ri.Milliseconds();
	backEnd.refdef.floatTime = backEnd.refdef.time * 0.001;
}