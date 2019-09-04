#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  axis; int /*<<< orphan*/  renderfx; int /*<<< orphan*/  hModel; int /*<<< orphan*/  oldorigin; int /*<<< orphan*/  origin; scalar_t__ backlerp; int /*<<< orphan*/  frame; int /*<<< orphan*/  oldframe; } ;
typedef  TYPE_3__ refEntity_t ;
struct TYPE_14__ {size_t modelindex; scalar_t__ number; int /*<<< orphan*/  frame; } ;
typedef  TYPE_4__ entityState_t ;
typedef  int /*<<< orphan*/  ent ;
struct TYPE_15__ {int /*<<< orphan*/  lerpAngles; int /*<<< orphan*/  lerpOrigin; TYPE_4__ currentState; } ;
typedef  TYPE_5__ centity_t ;
struct TYPE_17__ {TYPE_2__* snap; } ;
struct TYPE_16__ {int /*<<< orphan*/ * gameModels; } ;
struct TYPE_11__ {scalar_t__ clientNum; } ;
struct TYPE_12__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_THIRD_PERSON ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ cg ; 
 TYPE_8__ cgs ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_3__*) ; 

__attribute__((used)) static void CG_General( centity_t *cent ) {
	refEntity_t			ent;
	entityState_t		*s1;

	s1 = &cent->currentState;

	// if set to invisible, skip
	if (!s1->modelindex) {
		return;
	}

	memset (&ent, 0, sizeof(ent));

	// set frame

	ent.frame = s1->frame;
	ent.oldframe = ent.frame;
	ent.backlerp = 0;

	VectorCopy( cent->lerpOrigin, ent.origin);
	VectorCopy( cent->lerpOrigin, ent.oldorigin);

	ent.hModel = cgs.gameModels[s1->modelindex];

	// player model
	if (s1->number == cg.snap->ps.clientNum) {
		ent.renderfx |= RF_THIRD_PERSON;	// only draw from mirrors
	}

	// convert angles to axis
	AnglesToAxis( cent->lerpAngles, ent.axis );

	// add to refresh list
	trap_R_AddRefEntityToScene (&ent);
}