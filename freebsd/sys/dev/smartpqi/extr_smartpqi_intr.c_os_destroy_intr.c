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
struct TYPE_6__ {scalar_t__ msi_enabled; int /*<<< orphan*/  pqi_dev; } ;
struct TYPE_7__ {scalar_t__ intr_type; TYPE_1__ os_specific; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ INTR_TYPE_FIXED ; 
 scalar_t__ INTR_TYPE_MSIX ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  deregister_pqi_intx (TYPE_2__*) ; 
 int /*<<< orphan*/  deregister_pqi_msix (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

int os_destroy_intr(pqisrc_softstate_t *softs)
{
	device_t dev;
	dev = softs->os_specific.pqi_dev;

	DBG_FUNC("IN\n");

	if (softs->intr_type == INTR_TYPE_FIXED) {
		deregister_pqi_intx(softs);
	} else if (softs->intr_type == INTR_TYPE_MSIX) {
		deregister_pqi_msix(softs);
	}
	if (softs->os_specific.msi_enabled) {
		pci_release_msi(dev);
		softs->os_specific.msi_enabled = FALSE;
	} 
	
	DBG_FUNC("OUT\n");

	return PQI_STATUS_SUCCESS;
}