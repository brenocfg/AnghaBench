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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int health; char* message; struct TYPE_5__* nextTrain; scalar_t__ classname; } ;
typedef  TYPE_1__ gentity_t ;
struct TYPE_6__ {int num_entities; TYPE_1__* locationHead; scalar_t__ locationLinked; } ;

/* Variables and functions */
 scalar_t__ CS_LOCATIONS ; 
 int /*<<< orphan*/  Q_stricmp (scalar_t__,char*) ; 
 TYPE_1__* g_entities ; 
 TYPE_3__ level ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  trap_SetConfigstring (scalar_t__,char*) ; 

__attribute__((used)) static void target_location_linkup(gentity_t *ent)
{
	int i;
	int n;

	if (level.locationLinked) 
		return;

	level.locationLinked = qtrue;

	level.locationHead = NULL;

	trap_SetConfigstring( CS_LOCATIONS, "unknown" );

	for (i = 0, ent = g_entities, n = 1;
			i < level.num_entities;
			i++, ent++) {
		if (ent->classname && !Q_stricmp(ent->classname, "target_location")) {
			// lets overload some variables!
			ent->health = n; // use for location marking
			trap_SetConfigstring( CS_LOCATIONS + n, ent->message );
			n++;
			ent->nextTrain = level.locationHead;
			level.locationHead = ent;
		}
	}

	// All linked together now
}