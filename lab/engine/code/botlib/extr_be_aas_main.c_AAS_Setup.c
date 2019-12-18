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
typedef  int /*<<< orphan*/  aas_entity_t ;
struct TYPE_2__ {int maxclients; int maxentities; scalar_t__ numframes; int /*<<< orphan*/ * entities; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_InvalidateEntities () ; 
 int BLERR_NOERROR ; 
 int /*<<< orphan*/  FreeMemory (int /*<<< orphan*/ *) ; 
 scalar_t__ GetClearedHunkMemory (int) ; 
 int /*<<< orphan*/  LibVar (char*,char*) ; 
 scalar_t__ LibVarValue (char*,char*) ; 
 TYPE_1__ aasworld ; 
 int /*<<< orphan*/  saveroutingcache ; 

int AAS_Setup(void)
{
	aasworld.maxclients = (int) LibVarValue("maxclients", "128");
	aasworld.maxentities = (int) LibVarValue("maxentities", "1024");
	// as soon as it's set to 1 the routing cache will be saved
	saveroutingcache = LibVar("saveroutingcache", "0");
	//allocate memory for the entities
	if (aasworld.entities) FreeMemory(aasworld.entities);
	aasworld.entities = (aas_entity_t *) GetClearedHunkMemory(aasworld.maxentities * sizeof(aas_entity_t));
	//invalidate all the entities
	AAS_InvalidateEntities();
	//force some recalculations
	//LibVarSet("forceclustering", "1");			//force clustering calculation
	//LibVarSet("forcereachability", "1");		//force reachability calculation
	aasworld.numframes = 0;
	return BLERR_NOERROR;
}