#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mtlId; struct TYPE_4__* next; } ;
typedef  TYPE_1__ aseMaterial_t ;

/* Variables and functions */

__attribute__((used)) static aseMaterial_t* _ase_get_material( aseMaterial_t* list, int mtlIdParent ){
	aseMaterial_t* mtl = list;

	while ( mtl )
	{
		if ( mtlIdParent == mtl->mtlId ) {
			break;
		}
		mtl = mtl->next;
	}
	return mtl;
}