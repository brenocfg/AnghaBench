#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ backlerp; int /*<<< orphan*/ * axis; int /*<<< orphan*/  origin; int /*<<< orphan*/  frame; int /*<<< orphan*/  oldframe; } ;
typedef  TYPE_1__ refEntity_t ;
struct TYPE_7__ {int /*<<< orphan*/  axis; int /*<<< orphan*/ * origin; } ;
typedef  TYPE_2__ orientation_t ;
typedef  int /*<<< orphan*/  clipHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MatrixMultiply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_CM_LerpTag (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 

__attribute__((used)) static void UI_PositionEntityOnTag( refEntity_t *entity, const refEntity_t *parent, 
							clipHandle_t parentModel, char *tagName ) {
	int				i;
	orientation_t	lerped;
	
	// lerp the tag
	trap_CM_LerpTag( &lerped, parentModel, parent->oldframe, parent->frame,
		1.0 - parent->backlerp, tagName );

	// FIXME: allow origin offsets along tag?
	VectorCopy( parent->origin, entity->origin );
	for ( i = 0 ; i < 3 ; i++ ) {
		VectorMA( entity->origin, lerped.origin[i], parent->axis[i], entity->origin );
	}

	// cast away const because of compiler problems
	MatrixMultiply( lerped.axis, ((refEntity_t*)parent)->axis, entity->axis );
	entity->backlerp = parent->backlerp;
}