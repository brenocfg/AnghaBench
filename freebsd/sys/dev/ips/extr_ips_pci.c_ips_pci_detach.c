#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  queue; scalar_t__ configured; } ;
typedef  TYPE_1__ ips_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_PRINTF (int,int /*<<< orphan*/ ,char*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  bioq_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ips_adapter_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ips_flush_cache (TYPE_1__*) ; 
 int /*<<< orphan*/  ips_pci_free (TYPE_1__*) ; 

__attribute__((used)) static int ips_pci_detach(device_t dev)
{
        ips_softc_t *sc;
        DEVICE_PRINTF(1, dev, "detaching ServeRaid\n");
        sc = (ips_softc_t *) device_get_softc(dev);
	if (sc->configured) {
		sc->configured = 0;
		ips_flush_cache(sc);
		if(ips_adapter_free(sc))
			return EBUSY;
		ips_pci_free(sc);
		bioq_flush(&sc->queue, NULL, ENXIO);
	}
	return 0;
}