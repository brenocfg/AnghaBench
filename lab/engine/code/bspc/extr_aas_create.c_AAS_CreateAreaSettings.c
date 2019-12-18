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
struct TYPE_5__ {int faceflags; TYPE_3__* frontarea; struct TYPE_5__** next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_6__ {int contents; int /*<<< orphan*/  presencetype; int /*<<< orphan*/  areaflags; int /*<<< orphan*/  modelnum; } ;
typedef  TYPE_2__ tmp_areasettings_t ;
struct TYPE_7__ {int contents; int /*<<< orphan*/  presencetype; TYPE_2__* settings; TYPE_1__* tmpfaces; int /*<<< orphan*/  modelnum; scalar_t__ invalid; struct TYPE_7__* l_next; } ;
typedef  TYPE_3__ tmp_area_t ;
struct TYPE_8__ {TYPE_3__* areas; } ;

/* Variables and functions */
 int AREACONTENTS_LAVA ; 
 int AREACONTENTS_SLIME ; 
 int AREACONTENTS_WATER ; 
 int /*<<< orphan*/  AREA_GROUNDED ; 
 int /*<<< orphan*/  AREA_LADDER ; 
 int /*<<< orphan*/  AREA_LIQUID ; 
 int FACE_GROUND ; 
 int FACE_LADDER ; 
 scalar_t__ GetClearedMemory (int) ; 
 int /*<<< orphan*/  Log_Print (char*,int) ; 
 int /*<<< orphan*/  Log_Write (char*) ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 TYPE_4__ tmpaasworld ; 

void AAS_CreateAreaSettings(void)
{
	int i, flags, side, numgrounded, numladderareas, numliquidareas;
	tmp_face_t *face;
	tmp_area_t *tmparea;

	numgrounded = 0;
	numladderareas = 0;
	numliquidareas = 0;
	Log_Write("AAS_CreateAreaSettings\r\n");
	i = 0;
	qprintf("%6d areas provided with settings", i);
	for (tmparea = tmpaasworld.areas; tmparea; tmparea = tmparea->l_next)
	{
		//if the area is invalid there no need to create settings for it
		if (tmparea->invalid) continue;

		tmparea->settings = (tmp_areasettings_t *) GetClearedMemory(sizeof(tmp_areasettings_t));
		tmparea->settings->contents = tmparea->contents;
		tmparea->settings->modelnum = tmparea->modelnum;
		flags = 0;
		for (face = tmparea->tmpfaces; face; face = face->next[side])
		{
			side = face->frontarea != tmparea;
			flags |= face->faceflags;
		} //end for
		tmparea->settings->areaflags = 0;
		if (flags & FACE_GROUND)
		{
			tmparea->settings->areaflags |= AREA_GROUNDED;
			numgrounded++;
		} //end if
		if (flags & FACE_LADDER)
		{
			tmparea->settings->areaflags |= AREA_LADDER;
			numladderareas++;
		} //end if
		if (tmparea->contents & (AREACONTENTS_WATER |
											AREACONTENTS_SLIME |
											AREACONTENTS_LAVA))
		{
			tmparea->settings->areaflags |= AREA_LIQUID;
			numliquidareas++;
		} //end if
		//presence type of the area
		tmparea->settings->presencetype = tmparea->presencetype;
		//
		qprintf("\r%6d", ++i);
	} //end for
	qprintf("\n");
#ifdef AASINFO
	Log_Print("%6d grounded areas\n", numgrounded);
	Log_Print("%6d ladder areas\n", numladderareas);
	Log_Print("%6d liquid areas\n", numliquidareas);
#endif //AASINFO
}