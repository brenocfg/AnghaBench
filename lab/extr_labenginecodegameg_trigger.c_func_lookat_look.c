#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {double member_0; double member_1; double member_2; } ;
typedef  TYPE_2__ vec3_t ;
struct TYPE_14__ {int /*<<< orphan*/  endpos; } ;
typedef  TYPE_3__ trace_t ;
struct TYPE_15__ {TYPE_1__* client; int /*<<< orphan*/  id; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_16__ {scalar_t__ pm_type; } ;
struct TYPE_12__ {TYPE_9__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MoveToEntitySpace (TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__) ; 
 scalar_t__ PM_DEAD ; 
 int /*<<< orphan*/  dmlab_trigger_lookat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__,TYPE_9__*) ; 

void func_lookat_look(gentity_t *self, gentity_t *other, const trace_t *trace) {
	vec3_t local_point = {0.0, 0.0, 0.0};

	if (!other->client) return;
	if (other->client->ps.pm_type == PM_DEAD) return;

	if (trace) {
		MoveToEntitySpace(self, trace->endpos, local_point);
	}
	dmlab_trigger_lookat( self->id, trace != NULL, local_point, &other->client->ps );
}