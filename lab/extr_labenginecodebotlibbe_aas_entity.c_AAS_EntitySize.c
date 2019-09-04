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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
struct TYPE_6__ {TYPE_1__ i; } ;
typedef  TYPE_2__ aas_entity_t ;
struct TYPE_8__ {int maxentities; TYPE_2__* entities; int /*<<< orphan*/  initialized; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_FATAL ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ aasworld ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

void AAS_EntitySize(int entnum, vec3_t mins, vec3_t maxs)
{
	aas_entity_t *ent;

	if (!aasworld.initialized) return;

	if (entnum < 0 || entnum >= aasworld.maxentities)
	{
		botimport.Print(PRT_FATAL, "AAS_EntitySize: entnum %d out of range\n", entnum);
		return;
	} //end if

	ent = &aasworld.entities[entnum];
	VectorCopy(ent->i.mins, mins);
	VectorCopy(ent->i.maxs, maxs);
}