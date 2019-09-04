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
struct TYPE_2__ {void* loaded; void* initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_FreeRoutingCaches () ; 
 int /*<<< orphan*/  AAS_InitAASLinkHeap () ; 
 int /*<<< orphan*/  AAS_InitAASLinkedEntities () ; 
 int /*<<< orphan*/  AAS_InitAlternativeRouting () ; 
 int /*<<< orphan*/  AAS_InitReachability () ; 
 int /*<<< orphan*/  AAS_InitSettings () ; 
 int AAS_LoadFiles (char const*) ; 
 int BLERR_NOERROR ; 
 TYPE_1__ aasworld ; 
 void* qfalse ; 

int AAS_LoadMap(const char *mapname)
{
	int	errnum;

	//if no mapname is provided then the string indexes are updated
	if (!mapname)
	{
		return 0;
	} //end if
	//
	aasworld.initialized = qfalse;
	//NOTE: free the routing caches before loading a new map because
	// to free the caches the old number of areas, number of clusters
	// and number of areas in a clusters must be available
	AAS_FreeRoutingCaches();
	//load the map
	errnum = AAS_LoadFiles(mapname);
	if (errnum != BLERR_NOERROR)
	{
		aasworld.loaded = qfalse;
		return errnum;
	} //end if
	//
	AAS_InitSettings();
	//initialize the AAS link heap for the new map
	AAS_InitAASLinkHeap();
	//initialize the AAS linked entities for the new map
	AAS_InitAASLinkedEntities();
	//initialize reachability for the new map
	AAS_InitReachability();
	//initialize the alternative routing
	AAS_InitAlternativeRouting();
	//everything went ok
	return 0;
}