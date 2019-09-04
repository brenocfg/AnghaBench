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
typedef  int imgFlags_t ;
struct TYPE_6__ {int /*<<< orphan*/  integer; } ;
struct TYPE_5__ {int numCubemaps; TYPE_1__* cubemaps; } ;
struct TYPE_4__ {scalar_t__ image; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_RGBA8 ; 
 int IMGFLAG_CLAMPTOEDGE ; 
 int IMGFLAG_CUBEMAP ; 
 int IMGFLAG_MIPMAP ; 
 int IMGFLAG_NOLIGHTSCALE ; 
 int IMGFLAG_NO_COMPRESSION ; 
 int /*<<< orphan*/  IMGTYPE_COLORALPHA ; 
 int /*<<< orphan*/  RE_ClearScene () ; 
 scalar_t__ R_CreateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_InitNextFrame () ; 
 int /*<<< orphan*/  R_IssuePendingRenderCommands () ; 
 int /*<<< orphan*/  R_RenderCubemapSide (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_3__* r_cubemapSize ; 
 TYPE_2__ tr ; 
 int /*<<< orphan*/  va (char*,int) ; 

void R_RenderMissingCubemaps(void)
{
	int i, j;
	imgFlags_t flags = IMGFLAG_NO_COMPRESSION | IMGFLAG_CLAMPTOEDGE | IMGFLAG_MIPMAP | IMGFLAG_NOLIGHTSCALE | IMGFLAG_CUBEMAP;

	for (i = 0; i < tr.numCubemaps; i++)
	{
		if (!tr.cubemaps[i].image)
		{
			tr.cubemaps[i].image = R_CreateImage(va("*cubeMap%d", i), NULL, r_cubemapSize->integer, r_cubemapSize->integer, IMGTYPE_COLORALPHA, flags, GL_RGBA8);

			for (j = 0; j < 6; j++)
			{
				RE_ClearScene();
				R_RenderCubemapSide(i, j, qfalse);
				R_IssuePendingRenderCommands();
				R_InitNextFrame();
			}
		}
	}
}