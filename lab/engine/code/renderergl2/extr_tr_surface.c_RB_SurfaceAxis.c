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
struct TYPE_2__ {int /*<<< orphan*/  whiteImage; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLS_DEFAULT ; 
 int /*<<< orphan*/  GL_BindToTMU (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_LINES ; 
 int /*<<< orphan*/  GL_State (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_COLORMAP ; 
 int /*<<< orphan*/  qglBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglColor3f (int,int,int) ; 
 int /*<<< orphan*/  qglEnd () ; 
 int /*<<< orphan*/  qglLineWidth (int) ; 
 int /*<<< orphan*/  qglVertex3f (int,int,int) ; 
 TYPE_1__ tr ; 

__attribute__((used)) static void RB_SurfaceAxis( void ) {
	// FIXME: implement this
#if 0
	GL_BindToTMU( tr.whiteImage, TB_COLORMAP );
	GL_State( GLS_DEFAULT );
	qglLineWidth( 3 );
	qglBegin( GL_LINES );
	qglColor3f( 1,0,0 );
	qglVertex3f( 0,0,0 );
	qglVertex3f( 16,0,0 );
	qglColor3f( 0,1,0 );
	qglVertex3f( 0,0,0 );
	qglVertex3f( 0,16,0 );
	qglColor3f( 0,0,1 );
	qglVertex3f( 0,0,0 );
	qglVertex3f( 0,0,16 );
	qglEnd();
	qglLineWidth( 1 );
#endif
}