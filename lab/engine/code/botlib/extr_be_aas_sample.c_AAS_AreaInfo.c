#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  presencetype; int /*<<< orphan*/  areaflags; int /*<<< orphan*/  contents; int /*<<< orphan*/  cluster; } ;
typedef  TYPE_2__ aas_areasettings_t ;
struct TYPE_9__ {int /*<<< orphan*/  center; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  presencetype; int /*<<< orphan*/  flags; int /*<<< orphan*/  contents; int /*<<< orphan*/  cluster; } ;
typedef  TYPE_3__ aas_areainfo_t ;
struct TYPE_11__ {int numareas; TYPE_1__* areas; TYPE_2__* areasettings; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  center; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ aasworld ; 
 TYPE_4__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

int AAS_AreaInfo( int areanum, aas_areainfo_t *info )
{
	aas_areasettings_t *settings;
	if (!info)
		return 0;
	if (areanum <= 0 || areanum >= aasworld.numareas)
	{
		botimport.Print(PRT_ERROR, "AAS_AreaInfo: areanum %d out of range\n", areanum);
		return 0;
	} //end if
	settings = &aasworld.areasettings[areanum];
	info->cluster = settings->cluster;
	info->contents = settings->contents;
	info->flags = settings->areaflags;
	info->presencetype = settings->presencetype;
	VectorCopy(aasworld.areas[areanum].mins, info->mins);
	VectorCopy(aasworld.areas[areanum].maxs, info->maxs);
	VectorCopy(aasworld.areas[areanum].center, info->center);
	return sizeof(aas_areainfo_t);
}