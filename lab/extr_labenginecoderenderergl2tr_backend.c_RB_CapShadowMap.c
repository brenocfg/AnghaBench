#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int map; int cubeSide; } ;
typedef  TYPE_4__ capShadowmapCommand_t ;
struct TYPE_11__ {scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_16__ {TYPE_3__ refdef; } ;
struct TYPE_15__ {scalar_t__ vidHeight; } ;
struct TYPE_14__ {scalar_t__ numIndexes; } ;
struct TYPE_13__ {TYPE_2__** pshadowMaps; TYPE_1__** shadowCubemaps; } ;
struct TYPE_10__ {int /*<<< orphan*/  texnum; } ;
struct TYPE_9__ {int /*<<< orphan*/  texnum; } ;

/* Variables and functions */
 scalar_t__ GL_TEXTURE_2D ; 
 scalar_t__ GL_TEXTURE_CUBE_MAP_POSITIVE_X ; 
 scalar_t__ PSHADOW_MAP_SIZE ; 
 int /*<<< orphan*/  RB_EndSurface () ; 
 TYPE_8__ backEnd ; 
 TYPE_7__ glConfig ; 
 int /*<<< orphan*/  qglCopyTextureSubImage2DEXT (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_6__ tess ; 
 TYPE_5__ tr ; 

const void *RB_CapShadowMap(const void *data)
{
	const capShadowmapCommand_t *cmd = data;

	// finish any 2D drawing if needed
	if(tess.numIndexes)
		RB_EndSurface();

	if (cmd->map != -1)
	{
		if (cmd->cubeSide != -1)
		{
			if (tr.shadowCubemaps[cmd->map])
			{
				qglCopyTextureSubImage2DEXT(tr.shadowCubemaps[cmd->map]->texnum, GL_TEXTURE_CUBE_MAP_POSITIVE_X + cmd->cubeSide, 0, 0, 0, backEnd.refdef.x, glConfig.vidHeight - ( backEnd.refdef.y + PSHADOW_MAP_SIZE ), PSHADOW_MAP_SIZE, PSHADOW_MAP_SIZE);
			}
		}
		else
		{
			if (tr.pshadowMaps[cmd->map])
			{
				qglCopyTextureSubImage2DEXT(tr.pshadowMaps[cmd->map]->texnum, GL_TEXTURE_2D, 0, 0, 0, backEnd.refdef.x, glConfig.vidHeight - (backEnd.refdef.y + PSHADOW_MAP_SIZE), PSHADOW_MAP_SIZE, PSHADOW_MAP_SIZE);
			}
		}
	}

	return (const void *)(cmd + 1);
}