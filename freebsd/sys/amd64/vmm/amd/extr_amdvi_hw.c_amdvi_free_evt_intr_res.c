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
struct amdvi_softc {int /*<<< orphan*/  event_irq; int /*<<< orphan*/  event_rid; int /*<<< orphan*/ * event_res; int /*<<< orphan*/ * event_tag; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIB_RELEASE_MSI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct amdvi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amdvi_free_evt_intr_res(device_t dev)
{

	struct amdvi_softc *softc;

	softc = device_get_softc(dev);
	if (softc->event_tag != NULL) {
		bus_teardown_intr(dev, softc->event_res, softc->event_tag);
	}
	if (softc->event_res != NULL) {
		bus_release_resource(dev, SYS_RES_IRQ, softc->event_rid,
		    softc->event_res);
	}
	bus_delete_resource(dev, SYS_RES_IRQ, softc->event_rid);
	PCIB_RELEASE_MSI(device_get_parent(device_get_parent(dev)),
	    dev, 1, &softc->event_irq);
}