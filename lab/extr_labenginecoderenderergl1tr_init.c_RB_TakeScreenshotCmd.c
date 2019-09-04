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
struct TYPE_2__ {int /*<<< orphan*/  fileName; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; scalar_t__ jpeg; } ;
typedef  TYPE_1__ screenshotCommand_t ;

/* Variables and functions */
 int /*<<< orphan*/  RB_TakeScreenshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_TakeScreenshotJPEG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const void *RB_TakeScreenshotCmd( const void *data ) {
	const screenshotCommand_t	*cmd;
	
	cmd = (const screenshotCommand_t *)data;
	
	if (cmd->jpeg)
		RB_TakeScreenshotJPEG( cmd->x, cmd->y, cmd->width, cmd->height, cmd->fileName);
	else
		RB_TakeScreenshot( cmd->x, cmd->y, cmd->width, cmd->height, cmd->fileName);
	
	return (const void *)(cmd + 1);	
}