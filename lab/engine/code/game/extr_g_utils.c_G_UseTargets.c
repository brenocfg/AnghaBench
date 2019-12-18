#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  inuse; int /*<<< orphan*/  (* use ) (TYPE_2__*,TYPE_2__*,TYPE_2__*) ;int /*<<< orphan*/  target; TYPE_1__* client; int /*<<< orphan*/  id; scalar_t__ targetShaderNewName; scalar_t__ targetShaderName; } ;
typedef  TYPE_2__ gentity_t ;
struct TYPE_13__ {double time; } ;
struct TYPE_11__ {int /*<<< orphan*/  ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddRemap (scalar_t__,scalar_t__,float) ; 
 int /*<<< orphan*/  BuildShaderStateConfig () ; 
 int /*<<< orphan*/  CS_SHADERSTATE ; 
 int /*<<< orphan*/  FOFS (int /*<<< orphan*/ ) ; 
 TYPE_2__* G_Find (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_Printf (char*) ; 
 int /*<<< orphan*/  dmlab_can_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dmlab_override_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__ level ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  targetname ; 
 int /*<<< orphan*/  trap_SetConfigstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void G_UseTargets( gentity_t *ent, gentity_t *activator ) {
	gentity_t		*t;
	
	if ( !ent ) {
		return;
	}

	if (ent->targetShaderName && ent->targetShaderNewName) {
		float f = level.time * 0.001;
		AddRemap(ent->targetShaderName, ent->targetShaderNewName, f);
		trap_SetConfigstring(CS_SHADERSTATE, BuildShaderStateConfig());
	}

	if ( !ent->target ) {
		return;
	}

	if ( activator->client &&
			!dmlab_can_trigger( ent->id, ent->target, &activator->client->ps ) ) {
		return;
	}

	if ( activator->client &&
			dmlab_override_trigger( ent->id, ent->target, &activator->client->ps ) ) {
		return;
	}

	t = NULL;
	while ( (t = G_Find (t, FOFS(targetname), ent->target)) != NULL ) {
		if ( t == ent ) {
			G_Printf ("WARNING: Entity used itself.\n");
		} else {
			if ( t->use ) {
				t->use (t, ent, activator);
			}
		}
		if ( !ent->inuse ) {
			G_Printf("entity was removed while using targets\n");
			return;
		}
	}
}