#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ modelnum; int /*<<< orphan*/  solid; int /*<<< orphan*/  absmaxs; int /*<<< orphan*/  absmins; int /*<<< orphan*/  angles; int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ bsp_entdata_t ;
struct TYPE_6__ {scalar_t__ modelindex; int /*<<< orphan*/  solid; int /*<<< orphan*/  maxs; int /*<<< orphan*/  origin; int /*<<< orphan*/  mins; int /*<<< orphan*/  angles; } ;
struct TYPE_8__ {TYPE_1__ i; } ;
typedef  TYPE_3__ aas_entity_t ;
struct TYPE_9__ {TYPE_3__* entities; } ;

/* Variables and functions */
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ aasworld ; 

void AAS_EntityBSPData(int entnum, bsp_entdata_t *entdata)
{
	aas_entity_t *ent;

	ent = &aasworld.entities[entnum];
	VectorCopy(ent->i.origin, entdata->origin);
	VectorCopy(ent->i.angles, entdata->angles);
	VectorAdd(ent->i.origin, ent->i.mins, entdata->absmins);
	VectorAdd(ent->i.origin, ent->i.maxs, entdata->absmaxs);
	entdata->solid = ent->i.solid;
	entdata->modelnum = ent->i.modelindex - 1;
}