#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int subMtlId; struct TYPE_7__* next; } ;
typedef  TYPE_1__ aseSubMaterial_t ;
struct TYPE_8__ {TYPE_1__* subMtls; } ;
typedef  TYPE_2__ aseMaterial_t ;

/* Variables and functions */
 int /*<<< orphan*/  PICO_ERROR ; 
 TYPE_2__* _ase_get_material (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _pico_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static aseSubMaterial_t* _ase_get_submaterial( aseMaterial_t* list, int mtlIdParent, int subMtlId ){
	aseMaterial_t* parent = _ase_get_material( list, mtlIdParent );
	aseSubMaterial_t* subMtl = NULL;

	if ( !parent ) {
		_pico_printf( PICO_ERROR, "No ASE material exists with id %i\n", mtlIdParent );
		return NULL;
	}

	subMtl = parent->subMtls;
	while ( subMtl )
	{
		if ( subMtlId == subMtl->subMtlId ) {
			break;
		}
		subMtl = subMtl->next;
	}
	return subMtl;
}