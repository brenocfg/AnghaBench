#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  eType; } ;
struct TYPE_8__ {int /*<<< orphan*/  svFlags; } ;
struct TYPE_10__ {scalar_t__ nextthink; int /*<<< orphan*/  think; int /*<<< orphan*/  touch; TYPE_2__ s; TYPE_1__ r; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_11__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  AimAtTarget ; 
 int /*<<< orphan*/  ET_PUSH_TRIGGER ; 
 scalar_t__ FRAMETIME ; 
 int /*<<< orphan*/  G_SoundIndex (char*) ; 
 int /*<<< orphan*/  InitTrigger (TYPE_3__*) ; 
 int /*<<< orphan*/  SVF_NOCLIENT ; 
 TYPE_5__ level ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_3__*) ; 
 int /*<<< orphan*/  trigger_push_touch ; 

void SP_trigger_push( gentity_t *self ) {
	InitTrigger (self);

	// unlike other triggers, we need to send this one to the client
	self->r.svFlags &= ~SVF_NOCLIENT;

	// make sure the client precaches this sound
	G_SoundIndex("sound/world/jumppad.wav");

	self->s.eType = ET_PUSH_TRIGGER;
	self->touch = trigger_push_touch;
	self->think = AimAtTarget;
	self->nextthink = level.time + FRAMETIME;
	trap_LinkEntity (self);
}