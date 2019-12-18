#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vmbus_softc {void* vmbus_version; int /*<<< orphan*/  vmbus_dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  VMBUS_VERSION_MAJOR (void*) ; 
 int /*<<< orphan*/  VMBUS_VERSION_MINOR (void*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nitems (void**) ; 
 int vmbus_connect (struct vmbus_softc*,void*) ; 
 void* vmbus_current_version ; 
 void** vmbus_version ; 

__attribute__((used)) static int
vmbus_init(struct vmbus_softc *sc)
{
	int i;

	for (i = 0; i < nitems(vmbus_version); ++i) {
		int error;

		error = vmbus_connect(sc, vmbus_version[i]);
		if (!error) {
			vmbus_current_version = vmbus_version[i];
			sc->vmbus_version = vmbus_version[i];
			device_printf(sc->vmbus_dev, "version %u.%u\n",
			    VMBUS_VERSION_MAJOR(sc->vmbus_version),
			    VMBUS_VERSION_MINOR(sc->vmbus_version));
			return 0;
		}
	}
	return ENXIO;
}