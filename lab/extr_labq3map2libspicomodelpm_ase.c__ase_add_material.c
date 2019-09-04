#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mtlId; struct TYPE_5__* next; int /*<<< orphan*/ * subMtls; } ;
typedef  TYPE_1__ aseMaterial_t ;

/* Variables and functions */
 TYPE_1__* _pico_calloc (int,int) ; 

__attribute__((used)) static aseMaterial_t* _ase_add_material( aseMaterial_t **list, int mtlIdParent ){
	aseMaterial_t *mtl = _pico_calloc( 1, sizeof( aseMaterial_t ) );
	mtl->mtlId = mtlIdParent;
	mtl->subMtls = NULL;
	mtl->next = *list;
	*list = mtl;

	return mtl;
}