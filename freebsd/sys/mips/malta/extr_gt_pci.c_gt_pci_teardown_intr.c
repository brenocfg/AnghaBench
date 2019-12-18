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
struct resource {int dummy; } ;
struct gt_pci_softc {int /*<<< orphan*/ * sc_intr_cookies; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct gt_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gt_pci_mask_irq (void*) ; 
 int intr_event_remove_handler (void*) ; 
 int rman_get_start (struct resource*) ; 

__attribute__((used)) static int
gt_pci_teardown_intr(device_t dev, device_t child, struct resource *res,
    void *cookie)
{
	struct gt_pci_softc *sc = device_get_softc(dev);
	int irq;

	irq = rman_get_start(res);
	gt_pci_mask_irq((void *)&sc->sc_intr_cookies[irq]);

	return (intr_event_remove_handler(cookie));
}