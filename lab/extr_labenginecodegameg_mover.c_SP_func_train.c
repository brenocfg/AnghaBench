#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  absmin; } ;
struct TYPE_10__ {int /*<<< orphan*/  angles; } ;
struct TYPE_11__ {int spawnflags; int damage; int speed; int /*<<< orphan*/  think; scalar_t__ nextthink; int /*<<< orphan*/  reached; int /*<<< orphan*/  model; TYPE_1__ r; int /*<<< orphan*/  target; TYPE_2__ s; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_12__ {scalar_t__ time; } ;

/* Variables and functions */
 scalar_t__ FRAMETIME ; 
 int /*<<< orphan*/  G_FreeEntity (TYPE_3__*) ; 
 int /*<<< orphan*/  G_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitMover (TYPE_3__*) ; 
 int /*<<< orphan*/  Reached_Train ; 
 int TRAIN_BLOCK_STOPS ; 
 int /*<<< orphan*/  Think_SetupTrainTargets ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 TYPE_5__ level ; 
 int /*<<< orphan*/  trap_SetBrushModel (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtos (int /*<<< orphan*/ ) ; 

void SP_func_train (gentity_t *self) {
	VectorClear (self->s.angles);

	if (self->spawnflags & TRAIN_BLOCK_STOPS) {
		self->damage = 0;
	} else {
		if (!self->damage) {
			self->damage = 2;
		}
	}

	if ( !self->speed ) {
		self->speed = 100;
	}

	if ( !self->target ) {
		G_Printf ("func_train without a target at %s\n", vtos(self->r.absmin));
		G_FreeEntity( self );
		return;
	}

	trap_SetBrushModel( self, self->model );
	InitMover( self );

	self->reached = Reached_Train;

	// start trains on the second frame, to make sure their targets have had
	// a chance to spawn
	self->nextthink = level.time + FRAMETIME;
	self->think = Think_SetupTrainTargets;
}