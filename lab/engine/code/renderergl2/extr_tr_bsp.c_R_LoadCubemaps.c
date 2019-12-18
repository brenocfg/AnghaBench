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
struct TYPE_5__ {int /*<<< orphan*/  image; } ;
typedef  TYPE_2__ cubemap_t ;
struct TYPE_6__ {int numCubemaps; TYPE_1__* world; TYPE_2__* cubemaps; } ;
struct TYPE_4__ {int /*<<< orphan*/  baseName; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ,int) ; 
 int IMGFLAG_CLAMPTOEDGE ; 
 int IMGFLAG_CUBEMAP ; 
 int IMGFLAG_MIPMAP ; 
 int IMGFLAG_NOLIGHTSCALE ; 
 int /*<<< orphan*/  IMGTYPE_COLORALPHA ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  R_FindImageFile (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ tr ; 

void R_LoadCubemaps(void)
{
	int i;
	imgFlags_t flags = IMGFLAG_CLAMPTOEDGE | IMGFLAG_MIPMAP | IMGFLAG_NOLIGHTSCALE | IMGFLAG_CUBEMAP;

	for (i = 0; i < tr.numCubemaps; i++)
	{
		char filename[MAX_QPATH];
		cubemap_t *cubemap = &tr.cubemaps[i];

		Com_sprintf(filename, MAX_QPATH, "cubemaps/%s/%03d.dds", tr.world->baseName, i);

		cubemap->image = R_FindImageFile(filename, IMGTYPE_COLORALPHA, flags);
	}
}