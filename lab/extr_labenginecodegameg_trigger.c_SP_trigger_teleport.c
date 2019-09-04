#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  eType; } ;
struct TYPE_7__ {int /*<<< orphan*/  svFlags; } ;
struct TYPE_9__ {int spawnflags; int /*<<< orphan*/  touch; TYPE_2__ s; TYPE_1__ r; } ;
typedef  TYPE_3__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  ET_TELEPORT_TRIGGER ; 
 int /*<<< orphan*/  G_SoundIndex (char*) ; 
 int /*<<< orphan*/  InitTrigger (TYPE_3__*) ; 
 int /*<<< orphan*/  SVF_NOCLIENT ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_3__*) ; 
 int /*<<< orphan*/  trigger_teleporter_touch ; 

void SP_trigger_teleport( gentity_t *self ) {
	InitTrigger (self);

	// unlike other triggers, we need to send this one to the client
	// unless is a spectator trigger
	if ( self->spawnflags & 1 ) {
		self->r.svFlags |= SVF_NOCLIENT;
	} else {
		self->r.svFlags &= ~SVF_NOCLIENT;
	}

	// make sure the client precaches this sound
	G_SoundIndex("sound/world/jumppad.wav");

	self->s.eType = ET_TELEPORT_TRIGGER;
	self->touch = trigger_teleporter_touch;

	trap_LinkEntity (self);
}