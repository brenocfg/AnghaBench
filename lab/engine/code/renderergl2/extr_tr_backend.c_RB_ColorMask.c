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
struct TYPE_5__ {int /*<<< orphan*/ * rgba; } ;
typedef  TYPE_1__ colorMaskCommand_t ;
struct TYPE_8__ {int* colorMask; } ;
struct TYPE_7__ {scalar_t__ framebufferObject; } ;
struct TYPE_6__ {scalar_t__ numIndexes; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EndSurface () ; 
 TYPE_4__ backEnd ; 
 TYPE_3__ glRefConfig ; 
 int /*<<< orphan*/  qglColorMask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ tess ; 

const void *RB_ColorMask(const void *data)
{
	const colorMaskCommand_t *cmd = data;

	// finish any 2D drawing if needed
	if(tess.numIndexes)
		RB_EndSurface();

	if (glRefConfig.framebufferObject)
	{
		// reverse color mask, so 0 0 0 0 is the default
		backEnd.colorMask[0] = !cmd->rgba[0];
		backEnd.colorMask[1] = !cmd->rgba[1];
		backEnd.colorMask[2] = !cmd->rgba[2];
		backEnd.colorMask[3] = !cmd->rgba[3];
	}

	qglColorMask(cmd->rgba[0], cmd->rgba[1], cmd->rgba[2], cmd->rgba[3]);
	
	return (const void *)(cmd + 1);
}