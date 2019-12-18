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
struct TYPE_2__ {int /*<<< orphan*/  pqi_state; } ;
struct pqisrc_softstate {TYPE_1__ os_specific; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_INFO (char*,struct pqisrc_softstate*) ; 
 int /*<<< orphan*/  SMART_STATE_SUSPEND ; 
 struct pqisrc_softstate* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smartpqi_suspend(device_t dev)
{
	struct pqisrc_softstate *softs;
	softs = device_get_softc(dev);
	DBG_FUNC("IN\n");

	DBG_INFO("Suspending the device %p\n", softs);
	softs->os_specific.pqi_state |= SMART_STATE_SUSPEND;

	DBG_FUNC("OUT\n");
	return(0);
}