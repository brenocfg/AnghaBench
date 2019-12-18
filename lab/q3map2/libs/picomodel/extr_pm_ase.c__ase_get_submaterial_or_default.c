#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  aseSubMaterial_t ;
typedef  int /*<<< orphan*/  aseMaterial_t ;

/* Variables and functions */
 int /*<<< orphan*/  PICO_ERROR ; 
 int /*<<< orphan*/ * _ase_get_submaterial (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  _pico_printf (int /*<<< orphan*/ ,char*,int,int) ; 

aseSubMaterial_t* _ase_get_submaterial_or_default( aseMaterial_t* materials, int mtlIdParent, int subMtlId ){
	aseSubMaterial_t* subMtl = _ase_get_submaterial( materials, mtlIdParent, subMtlId );
	if ( subMtl != NULL ) {
		return subMtl;
	}

	/* ydnar: trying default submaterial */
	subMtl = _ase_get_submaterial( materials, mtlIdParent, 0 );
	if ( subMtl != NULL ) {
		return subMtl;
	}

	_pico_printf( PICO_ERROR, "Could not find material/submaterial for id %d/%d\n", mtlIdParent, subMtlId );
	return NULL;
}