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
struct TYPE_6__ {int wait; int random; struct TYPE_6__* activator; int /*<<< orphan*/  think; scalar_t__ nextthink; } ;
typedef  TYPE_1__ gentity_t ;
struct TYPE_7__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  Think_Target_Delay ; 
 int crandom () ; 
 TYPE_2__ level ; 

void Use_Target_Delay( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	ent->nextthink = level.time + ( ent->wait + ent->random * crandom() ) * 1000;
	ent->think = Think_Target_Delay;
	ent->activator = activator;
}