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
struct TYPE_4__ {int /*<<< orphan*/  valid; } ;
struct TYPE_5__ {int /*<<< orphan*/ * leaves; int /*<<< orphan*/ * areas; TYPE_1__ i; } ;
typedef  TYPE_2__ aas_entity_t ;
struct TYPE_6__ {int maxentities; TYPE_2__* entities; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_UnlinkFromAreas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AAS_UnlinkFromBSPLeaves (int /*<<< orphan*/ *) ; 
 TYPE_3__ aasworld ; 

void AAS_UnlinkInvalidEntities(void)
{
	int i;
	aas_entity_t *ent;

	for (i = 0; i < aasworld.maxentities; i++)
	{
		ent = &aasworld.entities[i];
		if (!ent->i.valid)
		{
			AAS_UnlinkFromAreas( ent->areas );
			ent->areas = NULL;
			AAS_UnlinkFromBSPLeaves( ent->leaves );
			ent->leaves = NULL;
		} //end for
	} //end for
}