#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  contents; } ;
struct TYPE_6__ {int /*<<< orphan*/  look; TYPE_1__ r; } ;
typedef  TYPE_2__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENTS_LOOKAT ; 
 int /*<<< orphan*/  InitTrigger (TYPE_2__*) ; 
 int /*<<< orphan*/  func_lookat_look ; 

void SP_trigger_lookat(gentity_t *self) {
	InitTrigger(self);
	self->r.contents |= CONTENTS_LOOKAT;
	self->look = func_lookat_look;
}