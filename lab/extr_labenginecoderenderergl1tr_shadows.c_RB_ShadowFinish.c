#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int stencilBits; } ;
struct TYPE_5__ {int integer; } ;
struct TYPE_4__ {int /*<<< orphan*/  whiteImage; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_TWO_SIDED ; 
 int GLS_DEPTHMASK_TRUE ; 
 int GLS_DSTBLEND_ZERO ; 
 int GLS_SRCBLEND_DST_COLOR ; 
 int /*<<< orphan*/  GL_Bind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_CLIP_PLANE0 ; 
 int /*<<< orphan*/  GL_Cull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_NOTEQUAL ; 
 int /*<<< orphan*/  GL_QUADS ; 
 int /*<<< orphan*/  GL_STENCIL_TEST ; 
 int /*<<< orphan*/  GL_State (int) ; 
 TYPE_3__ glConfig ; 
 int /*<<< orphan*/  qglBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglColor3f (float,float,float) ; 
 int /*<<< orphan*/  qglColor4f (int,int,int,int) ; 
 int /*<<< orphan*/  qglDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnd () ; 
 int /*<<< orphan*/  qglLoadIdentity () ; 
 int /*<<< orphan*/  qglStencilFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qglVertex3f (int,int,int) ; 
 TYPE_2__* r_shadows ; 
 TYPE_1__ tr ; 

void RB_ShadowFinish( void ) {
	if ( r_shadows->integer != 2 ) {
		return;
	}
	if ( glConfig.stencilBits < 4 ) {
		return;
	}
	qglEnable( GL_STENCIL_TEST );
	qglStencilFunc( GL_NOTEQUAL, 0, 255 );

	qglDisable (GL_CLIP_PLANE0);
	GL_Cull( CT_TWO_SIDED );

	GL_Bind( tr.whiteImage );

    qglLoadIdentity ();

	qglColor3f( 0.6f, 0.6f, 0.6f );
	GL_State( GLS_DEPTHMASK_TRUE | GLS_SRCBLEND_DST_COLOR | GLS_DSTBLEND_ZERO );

//	qglColor3f( 1, 0, 0 );
//	GL_State( GLS_DEPTHMASK_TRUE | GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO );

	qglBegin( GL_QUADS );
	qglVertex3f( -100, 100, -10 );
	qglVertex3f( 100, 100, -10 );
	qglVertex3f( 100, -100, -10 );
	qglVertex3f( -100, -100, -10 );
	qglEnd ();

	qglColor4f(1,1,1,1);
	qglDisable( GL_STENCIL_TEST );
}