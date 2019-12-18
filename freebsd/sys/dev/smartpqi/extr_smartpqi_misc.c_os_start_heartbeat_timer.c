#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  heartbeat_timeout_id; } ;
struct pqisrc_softstate {TYPE_1__ os_specific; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int OS_FW_HEARTBEAT_TIMER_INTERVAL ; 
 int hz ; 
 int /*<<< orphan*/  pqisrc_ctrl_offline (struct pqisrc_softstate*) ; 
 int /*<<< orphan*/  pqisrc_heartbeat_timer_handler (struct pqisrc_softstate*) ; 
 int /*<<< orphan*/  timeout (void (*) (void*),struct pqisrc_softstate*,int) ; 

void os_start_heartbeat_timer(void *data)
{
	struct pqisrc_softstate *softs = (struct pqisrc_softstate *)data;
	DBG_FUNC("IN\n");

	pqisrc_heartbeat_timer_handler(softs);
	if (!pqisrc_ctrl_offline(softs)) {
		softs->os_specific.heartbeat_timeout_id =
		timeout(os_start_heartbeat_timer, softs,
		OS_FW_HEARTBEAT_TIMER_INTERVAL * hz);
	}

       DBG_FUNC("OUT\n");
}