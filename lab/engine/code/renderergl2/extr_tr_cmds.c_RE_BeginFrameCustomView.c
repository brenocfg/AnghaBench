#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  commandId; } ;
typedef  TYPE_2__ drawBufferCommand_t ;
struct TYPE_20__ {int /*<<< orphan*/  vidHeight; int /*<<< orphan*/  vidWidth; } ;
struct TYPE_19__ {void* finishCalled; } ;
struct TYPE_18__ {void* modified; } ;
struct TYPE_17__ {int /*<<< orphan*/  integer; } ;
struct TYPE_16__ {void* modified; int /*<<< orphan*/  string; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  vertFlipBuffer; int /*<<< orphan*/  stereoFrame; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {TYPE_1__ refdef; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  GL_BACK ; 
 int GL_NO_ERROR ; 
 int /*<<< orphan*/  GL_TextureMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC_DRAW_BUFFER ; 
 TYPE_2__* R_GetCommandBuffer (int) ; 
 int /*<<< orphan*/  R_IssuePendingRenderCommands () ; 
 int /*<<< orphan*/  R_SetColorMappings () ; 
 int /*<<< orphan*/  STEREO_CENTER ; 
 int /*<<< orphan*/  SwapVidAndBuff (TYPE_9__*) ; 
 TYPE_9__ glConfig ; 
 TYPE_8__ glState ; 
 void* qfalse ; 
 int qglGetError () ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_7__* r_gamma ; 
 TYPE_6__* r_ignoreGLErrors ; 
 TYPE_5__* r_textureMode ; 
 TYPE_4__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_3__ tr ; 

void RE_BeginFrameCustomView( void ) {
	drawBufferCommand_t	*cmd = NULL;
	if ( !tr.registered ) {
		return;
	}
	SwapVidAndBuff( &glConfig );
	tr.refdef.width = glConfig.vidWidth;
	tr.refdef.height = glConfig.vidHeight;
	glState.finishCalled = qfalse;

	//
	// texturemode stuff
	//
	if ( r_textureMode->modified ) {
		R_IssuePendingRenderCommands();
		GL_TextureMode( r_textureMode->string );
		r_textureMode->modified = qfalse;
	}

	//
	// gamma stuff
	//
	if ( r_gamma->modified ) {
		r_gamma->modified = qfalse;

		R_IssuePendingRenderCommands();
		R_SetColorMappings();
	}

	// check for errors
	if ( !r_ignoreGLErrors->integer )
	{
		int	err;

		R_IssuePendingRenderCommands();
		if ((err = qglGetError()) != GL_NO_ERROR)
			ri.Error(ERR_FATAL, "RE_BeginFrame() - glGetError() failed (0x%x)!", err);
	}

	if( !(cmd = R_GetCommandBuffer(sizeof(*cmd))) )
		return;
	if(cmd)
	{
		cmd->commandId = RC_DRAW_BUFFER;
		cmd->buffer = GL_BACK;
	}

	tr.refdef.stereoFrame = STEREO_CENTER;

	tr.refdef.vertFlipBuffer = qtrue;
}