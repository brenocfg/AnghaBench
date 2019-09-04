#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoShader_t ;
struct TYPE_10__ {int subMtlId; struct TYPE_10__* next; int /*<<< orphan*/ * shader; } ;
typedef  TYPE_1__ aseSubMaterial_t ;
struct TYPE_11__ {TYPE_1__* subMtls; } ;
typedef  TYPE_2__ aseMaterial_t ;

/* Variables and functions */
 TYPE_2__* _ase_add_material (TYPE_2__**,int) ; 
 TYPE_2__* _ase_get_material (TYPE_2__*,int) ; 
 TYPE_1__* _pico_calloc (int,int) ; 

__attribute__((used)) static aseSubMaterial_t* _ase_add_submaterial( aseMaterial_t **list, int mtlIdParent, int subMtlId, picoShader_t* shader ){
	aseMaterial_t *parent = _ase_get_material( *list,  mtlIdParent );
	aseSubMaterial_t *subMtl = _pico_calloc( 1, sizeof( aseSubMaterial_t ) );

	if ( !parent ) {
		parent = _ase_add_material( list, mtlIdParent );
	}

	subMtl->shader = shader;
	subMtl->subMtlId = subMtlId;
	subMtl->next = parent->subMtls;
	parent->subMtls = subMtl;

	return subMtl;
}