#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ctrl_online; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  os_complete_outstanding_cmds_nodevice (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_take_devices_offline (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_trigger_nmi_sis (TYPE_1__*) ; 

void pqisrc_take_ctrl_offline(pqisrc_softstate_t *softs)
{

	DBG_FUNC("IN\n");

	softs->ctrl_online = false;
	pqisrc_trigger_nmi_sis(softs);
	os_complete_outstanding_cmds_nodevice(softs);
	pqisrc_take_devices_offline(softs);

	DBG_FUNC("OUT\n");
}