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
struct TYPE_7__ {int /*<<< orphan*/  angles; int /*<<< orphan*/  origin; int /*<<< orphan*/  eType; } ;
struct TYPE_8__ {int damage; int spawnflags; int /*<<< orphan*/  think; int /*<<< orphan*/  use; int /*<<< orphan*/  movedir; TYPE_1__ s; struct TYPE_8__* enemy; scalar_t__ target; int /*<<< orphan*/  classname; } ;
typedef  TYPE_2__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  ET_BEAM ; 
 int /*<<< orphan*/  FOFS (int /*<<< orphan*/ ) ; 
 TYPE_2__* G_Find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  G_Printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  G_SetMovedir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_laser_off (TYPE_2__*) ; 
 int /*<<< orphan*/  target_laser_on (TYPE_2__*) ; 
 int /*<<< orphan*/  target_laser_think ; 
 int /*<<< orphan*/  target_laser_use ; 
 int /*<<< orphan*/  targetname ; 
 int /*<<< orphan*/  vtos (int /*<<< orphan*/ ) ; 

void target_laser_start (gentity_t *self)
{
	gentity_t *ent;

	self->s.eType = ET_BEAM;

	if (self->target) {
		ent = G_Find (NULL, FOFS(targetname), self->target);
		if (!ent) {
			G_Printf ("%s at %s: %s is a bad target\n", self->classname, vtos(self->s.origin), self->target);
		}
		self->enemy = ent;
	} else {
		G_SetMovedir (self->s.angles, self->movedir);
	}

	self->use = target_laser_use;
	self->think = target_laser_think;

	if ( !self->damage ) {
		self->damage = 1;
	}

	if (self->spawnflags & 1)
		target_laser_on (self);
	else
		target_laser_off (self);
}