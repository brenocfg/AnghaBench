#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ msi_enabled; int /*<<< orphan*/  pqi_dev; } ;
struct TYPE_5__ {TYPE_1__ os_specific; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

void os_free_intr_config(pqisrc_softstate_t *softs)
{
	device_t dev;
	dev = softs->os_specific.pqi_dev;

	DBG_FUNC("IN\n");

        if (softs->os_specific.msi_enabled) {
                pci_release_msi(dev);
                softs->os_specific.msi_enabled = FALSE;
        }

	DBG_FUNC("OUT\n");
}