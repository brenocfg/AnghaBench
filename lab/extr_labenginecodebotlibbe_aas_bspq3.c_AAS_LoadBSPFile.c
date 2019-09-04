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
struct TYPE_4__ {int /*<<< orphan*/  (* BSPEntityData ) () ;} ;
struct TYPE_3__ {char* dentdata; int /*<<< orphan*/  loaded; scalar_t__ entdatasize; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_DumpBSPData () ; 
 int /*<<< orphan*/  AAS_ParseBSPEntities () ; 
 int BLERR_NOERROR ; 
 int /*<<< orphan*/  Com_Memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ GetClearedHunkMemory (scalar_t__) ; 
 TYPE_2__ botimport ; 
 TYPE_1__ bspworld ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

int AAS_LoadBSPFile(void)
{
	AAS_DumpBSPData();
	bspworld.entdatasize = strlen(botimport.BSPEntityData()) + 1;
	bspworld.dentdata = (char *) GetClearedHunkMemory(bspworld.entdatasize);
	Com_Memcpy(bspworld.dentdata, botimport.BSPEntityData(), bspworld.entdatasize);
	AAS_ParseBSPEntities();
	bspworld.loaded = qtrue;
	return BLERR_NOERROR;
}