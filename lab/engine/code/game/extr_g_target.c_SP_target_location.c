#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  origin; } ;
struct TYPE_7__ {TYPE_1__ s; scalar_t__ nextthink; int /*<<< orphan*/  think; } ;
typedef  TYPE_2__ gentity_t ;
struct TYPE_8__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_SetOrigin (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__ level ; 
 int /*<<< orphan*/  target_location_linkup ; 

void SP_target_location( gentity_t *self ){
	self->think = target_location_linkup;
	self->nextthink = level.time + 200;  // Let them all spawn first

	G_SetOrigin( self, self->s.origin );
}