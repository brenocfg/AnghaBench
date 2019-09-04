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
struct TYPE_6__ {int /*<<< orphan*/  think; int /*<<< orphan*/  nextthink; struct TYPE_6__* activator; scalar_t__ client; } ;
typedef  TYPE_1__ gentity_t ;
struct TYPE_7__ {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  Think_LuaMover ; 
 TYPE_2__ level ; 

void Use_LuaMover( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	if (activator->client) {
		ent->activator = activator;
		ent->nextthink = level.time;
		ent->think = Think_LuaMover;
	}
}