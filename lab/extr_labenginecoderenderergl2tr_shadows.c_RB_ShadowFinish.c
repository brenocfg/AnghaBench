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

void RB_ShadowFinish( void ) {
	// FIXME: implement this
#if 0
	if ( r_shadows->integer != 2 ) {
		return;
	}
	if ( glConfig.stencilBits < 4 ) {
		return;
	}
	qglEnable( GL_STENCIL_TEST );
	qglStencilFunc( GL_NOTEQUAL, 0, 255 );

	GL_Cull( CT_TWO_SIDED );

	GL_BindToTMU( tr.whiteImage, TB_COLORMAP );

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
#endif
}