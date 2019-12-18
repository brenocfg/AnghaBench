#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shader_t ;
struct TYPE_2__ {int /*<<< orphan*/ ** sortedShaders; } ;

/* Variables and functions */
 int MAX_SHADERS ; 
 unsigned int QSORT_FOGNUM_SHIFT ; 
 unsigned int QSORT_REFENTITYNUM_SHIFT ; 
 unsigned int QSORT_SHADERNUM_SHIFT ; 
 unsigned int REFENTITYNUM_MASK ; 
 TYPE_1__ tr ; 

void R_DecomposeSort( unsigned sort, int *entityNum, shader_t **shader, 
					 int *fogNum, int *dlightMap ) {
	*fogNum = ( sort >> QSORT_FOGNUM_SHIFT ) & 31;
	*shader = tr.sortedShaders[ ( sort >> QSORT_SHADERNUM_SHIFT ) & (MAX_SHADERS-1) ];
	*entityNum = ( sort >> QSORT_REFENTITYNUM_SHIFT ) & REFENTITYNUM_MASK;
	*dlightMap = sort & 3;
}