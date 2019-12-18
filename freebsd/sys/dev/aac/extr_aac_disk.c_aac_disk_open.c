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
struct disk {scalar_t__ d_drv1; } ;
struct aac_disk {int /*<<< orphan*/  ad_flags; TYPE_1__* ad_controller; } ;
struct TYPE_2__ {int aac_state; int /*<<< orphan*/  aac_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_DISK_OPEN ; 
 int AAC_STATE_SUSPEND ; 
 int ENXIO ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fwprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
aac_disk_open(struct disk *dp)
{
	struct aac_disk	*sc;

	fwprintf(NULL, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	sc = (struct aac_disk *)dp->d_drv1;
	
	if (sc == NULL) {
		printf("aac_disk_open: No Softc\n");
		return (ENXIO);
	}

	/* check that the controller is up and running */
	if (sc->ad_controller->aac_state & AAC_STATE_SUSPEND) {
		device_printf(sc->ad_controller->aac_dev,
		    "Controller Suspended controller state = 0x%x\n",
		    sc->ad_controller->aac_state);
		return(ENXIO);
	}

	sc->ad_flags |= AAC_DISK_OPEN;
	return (0);
}