#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int traveltype; } ;
typedef  TYPE_1__ aas_reachability_t ;
struct TYPE_8__ {int numreachableareas; int firstreachablearea; } ;
typedef  TYPE_2__ aas_areasettings_t ;
struct TYPE_10__ {int /*<<< orphan*/ * reachability; TYPE_2__* areasettings; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_PrintTravelType (int) ; 
 int /*<<< orphan*/  AAS_ShowReachability (TYPE_1__*) ; 
 float AAS_Time () ; 
 int /*<<< orphan*/  Com_Memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int TRAVELTYPE_MASK ; 
 TYPE_4__ aasworld ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void AAS_ShowReachableAreas(int areanum)
{
	aas_areasettings_t *settings;
	static aas_reachability_t reach;
	static int index, lastareanum;
	static float lasttime;

	if (areanum != lastareanum)
	{
		index = 0;
		lastareanum = areanum;
	} //end if
	settings = &aasworld.areasettings[areanum];
	//
	if (!settings->numreachableareas) return;
	//
	if (index >= settings->numreachableareas) index = 0;
	//
	if (AAS_Time() - lasttime > 1.5)
	{
		Com_Memcpy(&reach, &aasworld.reachability[settings->firstreachablearea + index], sizeof(aas_reachability_t));
		index++;
		lasttime = AAS_Time();
		AAS_PrintTravelType(reach.traveltype & TRAVELTYPE_MASK);
		botimport.Print(PRT_MESSAGE, "\n");
	} //end if
	AAS_ShowReachability(&reach);
}