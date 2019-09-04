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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_4__ {scalar_t__ type; int modelindex; int /*<<< orphan*/  origin; } ;
struct TYPE_5__ {TYPE_1__ i; } ;
typedef  TYPE_2__ aas_entity_t ;
struct TYPE_6__ {int maxentities; TYPE_2__* entities; } ;

/* Variables and functions */
 scalar_t__ ET_MOVER ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ aasworld ; 
 int qfalse ; 
 int qtrue ; 

int AAS_OriginOfMoverWithModelNum(int modelnum, vec3_t origin)
{
	int i;
	aas_entity_t *ent;

	for (i = 0; i < aasworld.maxentities; i++)
	{
		ent = &aasworld.entities[i];
		if (ent->i.type == ET_MOVER)
		{
			if (ent->i.modelindex == modelnum)
			{
				VectorCopy(ent->i.origin, origin);
				return qtrue;
			} //end if
		} //end if
	} //end for
	return qfalse;
}