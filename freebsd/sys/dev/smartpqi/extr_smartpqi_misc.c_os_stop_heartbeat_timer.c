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
struct TYPE_5__ {int /*<<< orphan*/  heartbeat_timeout_id; } ;
struct TYPE_6__ {TYPE_1__ os_specific; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  os_start_heartbeat_timer ; 
 int /*<<< orphan*/  untimeout (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

void os_stop_heartbeat_timer(pqisrc_softstate_t *softs)
{
	DBG_FUNC("IN\n");

	/* Kill the heart beat event */
	untimeout(os_start_heartbeat_timer, softs, 
			softs->os_specific.heartbeat_timeout_id);

	DBG_FUNC("OUT\n");
}