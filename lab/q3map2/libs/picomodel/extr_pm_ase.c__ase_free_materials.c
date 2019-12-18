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
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* subMtls; } ;
typedef  TYPE_1__ aseSubMaterial_t ;
typedef  TYPE_1__ aseMaterial_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_free (TYPE_1__*) ; 

__attribute__((used)) static void _ase_free_materials( aseMaterial_t **list ){
	aseMaterial_t* mtl = *list;
	aseSubMaterial_t* subMtl = NULL;

	aseMaterial_t* mtlTemp = NULL;
	aseSubMaterial_t* subMtlTemp = NULL;

	while ( mtl )
	{
		subMtl = mtl->subMtls;
		while ( subMtl )
		{
			subMtlTemp = subMtl->next;
			_pico_free( subMtl );
			subMtl = subMtlTemp;
		}
		mtlTemp = mtl->next;
		_pico_free( mtl );
		mtl = mtlTemp;
	}
	( *list ) = NULL;
}