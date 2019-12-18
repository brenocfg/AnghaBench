#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* l_next; } ;
typedef  TYPE_1__ tmp_area_t ;
struct TYPE_6__ {TYPE_1__* areas; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_CheckAreaSharedFaces (TYPE_1__*,TYPE_1__*) ; 
 TYPE_2__ tmpaasworld ; 

void AAS_CheckSharedFaces(void)
{
	tmp_area_t *tmparea1, *tmparea2;

	for (tmparea1 = tmpaasworld.areas; tmparea1; tmparea1 = tmparea1->l_next)
	{
		for (tmparea2 = tmpaasworld.areas; tmparea2; tmparea2 = tmparea2->l_next)
		{
			if (tmparea1 == tmparea2) continue;
			AAS_CheckAreaSharedFaces(tmparea1, tmparea2);
		} //end for
	} //end for
}