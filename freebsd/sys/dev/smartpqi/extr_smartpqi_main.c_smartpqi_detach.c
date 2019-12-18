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
struct TYPE_2__ {int /*<<< orphan*/  heartbeat_timeout_id; int /*<<< orphan*/  wellness_periodic; int /*<<< orphan*/  eh; } ;
struct pqisrc_softstate {TYPE_1__ os_specific; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deregister_sim (struct pqisrc_softstate*) ; 
 int /*<<< orphan*/  destroy_char_dev (struct pqisrc_softstate*) ; 
 struct pqisrc_softstate* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_start_heartbeat_timer ; 
 int /*<<< orphan*/  os_wellness_periodic ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqisrc_uninit (struct pqisrc_softstate*) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  smartpqi_shutdown (struct pqisrc_softstate*) ; 
 int /*<<< orphan*/  untimeout (int /*<<< orphan*/ ,struct pqisrc_softstate*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smartpqi_detach(device_t dev)
{
	struct pqisrc_softstate *softs = NULL;
	softs = device_get_softc(dev);
	DBG_FUNC("IN\n");

	EVENTHANDLER_DEREGISTER(shutdown_final, softs->os_specific.eh);

	/* kill the periodic event */
	untimeout(os_wellness_periodic, softs, 
			softs->os_specific.wellness_periodic);
	/* Kill the heart beat event */
	untimeout(os_start_heartbeat_timer, softs, 
			softs->os_specific.heartbeat_timeout_id);

	smartpqi_shutdown(softs);
	destroy_char_dev(softs);
	pqisrc_uninit(softs);
	deregister_sim(softs);
	pci_release_msi(dev);
	
	DBG_FUNC("OUT\n");
	return 0;
}