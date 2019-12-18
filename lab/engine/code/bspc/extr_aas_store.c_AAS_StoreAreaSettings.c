#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int contents; int modelnum; int /*<<< orphan*/  presencetype; int /*<<< orphan*/  areaflags; } ;
typedef  TYPE_1__ tmp_areasettings_t ;
struct TYPE_6__ {int contents; int /*<<< orphan*/  presencetype; int /*<<< orphan*/  areaflags; } ;
typedef  TYPE_2__ aas_areasettings_t ;
struct TYPE_7__ {int numareasettings; TYPE_2__* areasettings; } ;

/* Variables and functions */
 int AREACONTENTS_MAXMODELNUM ; 
 int AREACONTENTS_MODELNUMSHIFT ; 
 int /*<<< orphan*/  Log_Print (char*,int) ; 
 TYPE_3__ aasworld ; 

void AAS_StoreAreaSettings(tmp_areasettings_t *tmpareasettings)
{
	aas_areasettings_t *areasettings;

	if (aasworld.numareasettings == 0) aasworld.numareasettings = 1;
	areasettings = &aasworld.areasettings[aasworld.numareasettings++];
	areasettings->areaflags = tmpareasettings->areaflags;
	areasettings->presencetype = tmpareasettings->presencetype;
	areasettings->contents = tmpareasettings->contents;
	if (tmpareasettings->modelnum > AREACONTENTS_MAXMODELNUM)
		Log_Print("WARNING: more than %d mover models\n", AREACONTENTS_MAXMODELNUM);
	areasettings->contents |= (tmpareasettings->modelnum & AREACONTENTS_MAXMODELNUM) << AREACONTENTS_MODELNUMSHIFT;
}