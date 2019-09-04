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
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  motionJpeg; int /*<<< orphan*/ * encodeBuffer; int /*<<< orphan*/ * captureBuffer; int /*<<< orphan*/  commandId; } ;
typedef  TYPE_1__ videoFrameCommand_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_5__ {int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_VIDEOFRAME ; 
 TYPE_1__* R_GetCommandBuffer (int) ; 
 TYPE_2__ tr ; 

void RE_TakeVideoFrame( int width, int height,
		byte *captureBuffer, byte *encodeBuffer, qboolean motionJpeg )
{
	videoFrameCommand_t	*cmd;

	if( !tr.registered ) {
		return;
	}

	cmd = R_GetCommandBuffer( sizeof( *cmd ) );
	if( !cmd ) {
		return;
	}

	cmd->commandId = RC_VIDEOFRAME;

	cmd->width = width;
	cmd->height = height;
	cmd->captureBuffer = captureBuffer;
	cmd->encodeBuffer = encodeBuffer;
	cmd->motionJpeg = motionJpeg;
}