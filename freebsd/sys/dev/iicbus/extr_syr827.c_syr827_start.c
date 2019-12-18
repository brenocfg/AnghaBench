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
typedef  int uint8_t ;
struct syr827_softc {int /*<<< orphan*/  intr_hook; } ;
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ID1 ; 
 int ID1_DIE_MASK ; 
 int ID1_VENDOR_MASK ; 
 int ID1_VENDOR_SHIFT ; 
 int /*<<< orphan*/  ID2 ; 
 int ID2_DIE_REV_MASK ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct syr827_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,int,...) ; 
 int /*<<< orphan*/  syr827_read (void*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
syr827_start(void *pdev)
{
	struct syr827_softc *sc;
	device_t dev;
	uint8_t val;

	dev = pdev;
	sc = device_get_softc(dev);

	if (bootverbose) {
		syr827_read(dev, ID1, &val, 1);
		device_printf(dev, "Vendor ID: %x, DIE ID: %x\n",
		    (val & ID1_VENDOR_MASK) >> ID1_VENDOR_SHIFT,
		    val & ID1_DIE_MASK);
		syr827_read(dev, ID2, &val, 1);
		device_printf(dev, "DIE Rev: %x\n", val & ID2_DIE_REV_MASK);
	}

	config_intrhook_disestablish(&sc->intr_hook);
}