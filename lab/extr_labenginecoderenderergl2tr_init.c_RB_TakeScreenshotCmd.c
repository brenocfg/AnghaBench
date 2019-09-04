#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fileName; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; scalar_t__ jpeg; } ;
typedef  TYPE_1__ screenshotCommand_t ;
struct TYPE_4__ {scalar_t__ numIndexes; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EndSurface () ; 
 int /*<<< orphan*/  RB_TakeScreenshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_TakeScreenshotJPEG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ tess ; 

const void *RB_TakeScreenshotCmd( const void *data ) {
	const screenshotCommand_t	*cmd;
	
	cmd = (const screenshotCommand_t *)data;

	// finish any 2D drawing if needed
	if(tess.numIndexes)
		RB_EndSurface();

	if (cmd->jpeg)
		RB_TakeScreenshotJPEG( cmd->x, cmd->y, cmd->width, cmd->height, cmd->fileName);
	else
		RB_TakeScreenshot( cmd->x, cmd->y, cmd->width, cmd->height, cmd->fileName);
	
	return (const void *)(cmd + 1);	
}