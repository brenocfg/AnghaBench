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
struct aoagpio_softc {int ctrl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int ENXIO ; 
 int GPIO_CTRL_EXTINT_SET ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int /*<<< orphan*/  INTR_POLARITY_LOW ; 
 int /*<<< orphan*/  INTR_TRIGGER_EDGE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  aoagpio_int ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 struct aoagpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ powerpc_config_intr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_get_start (struct resource*) ; 

__attribute__((used)) static int 
aoagpio_attach(device_t gpio)
{
	struct aoagpio_softc	*sc;
	struct resource		*r;
	void			*cookie;
	int			 irq, rid = 0;

	sc = device_get_softc(gpio);

	if ((1 << sc->ctrl) & GPIO_CTRL_EXTINT_SET) {
		r = bus_alloc_resource_any(gpio, SYS_RES_IRQ, &rid, RF_ACTIVE);
		if (r == NULL)
			return (ENXIO);

		irq = rman_get_start(r);
		DPRINTF(("interrupting at irq %d\n", irq));

		if (powerpc_config_intr(irq, INTR_TRIGGER_EDGE, 
		    INTR_POLARITY_LOW) != 0) 
			return (ENXIO);

		bus_setup_intr(gpio, r, INTR_TYPE_MISC | INTR_MPSAFE |
		    INTR_ENTROPY, NULL, aoagpio_int, gpio, &cookie);
	}

	return (0);
}