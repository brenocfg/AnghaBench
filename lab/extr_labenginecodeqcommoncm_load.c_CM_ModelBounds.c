#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_3__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
typedef  TYPE_1__ cmodel_t ;
typedef  int /*<<< orphan*/  clipHandle_t ;

/* Variables and functions */
 TYPE_1__* CM_ClipHandleToModel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CM_ModelBounds( clipHandle_t model, vec3_t mins, vec3_t maxs ) {
	cmodel_t	*cmod;

	cmod = CM_ClipHandleToModel( model );
	VectorCopy( cmod->mins, mins );
	VectorCopy( cmod->maxs, maxs );
}