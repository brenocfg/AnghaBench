#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ drawBufferCommand_t ;
struct TYPE_8__ {scalar_t__ framebufferObject; } ;
struct TYPE_7__ {scalar_t__ integer; } ;
struct TYPE_6__ {scalar_t__ numIndexes; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBO_Bind (int /*<<< orphan*/ *) ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  RB_EndSurface () ; 
 TYPE_4__ glRefConfig ; 
 int /*<<< orphan*/  qglClear (int) ; 
 int /*<<< orphan*/  qglClearColor (int,int /*<<< orphan*/ ,double,int) ; 
 int /*<<< orphan*/  qglDrawBuffer (int /*<<< orphan*/ ) ; 
 TYPE_3__* r_clear ; 
 TYPE_2__ tess ; 

const void	*RB_DrawBuffer( const void *data ) {
	const drawBufferCommand_t	*cmd;

	cmd = (const drawBufferCommand_t *)data;

	// finish any 2D drawing if needed
	if(tess.numIndexes)
		RB_EndSurface();

	if (glRefConfig.framebufferObject)
		FBO_Bind(NULL);

	qglDrawBuffer( cmd->buffer );

	// clear screen for debugging
	if ( r_clear->integer ) {
		qglClearColor( 1, 0, 0.5, 1 );
		qglClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	return (const void *)(cmd + 1);
}