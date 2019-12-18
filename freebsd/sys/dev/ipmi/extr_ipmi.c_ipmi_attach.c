#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct ipmi_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct ipmi_softc {TYPE_1__ ipmi_ich; int /*<<< orphan*/  ipmi_irq; int /*<<< orphan*/ * ipmi_intr; int /*<<< orphan*/ * ipmi_irq_res; } ;
struct intr_config_hook {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ipmi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 struct ipmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ipmi_attached ; 
 int /*<<< orphan*/  ipmi_startup ; 

int
ipmi_attach(device_t dev)
{
	struct ipmi_softc *sc = device_get_softc(dev);
	int error;

	if (sc->ipmi_irq_res != NULL && sc->ipmi_intr != NULL) {
		error = bus_setup_intr(dev, sc->ipmi_irq_res, INTR_TYPE_MISC,
		    NULL, sc->ipmi_intr, sc, &sc->ipmi_irq);
		if (error) {
			device_printf(dev, "can't set up interrupt\n");
			return (error);
		}
	}

	bzero(&sc->ipmi_ich, sizeof(struct intr_config_hook));
	sc->ipmi_ich.ich_func = ipmi_startup;
	sc->ipmi_ich.ich_arg = sc;
	if (config_intrhook_establish(&sc->ipmi_ich) != 0) {
		device_printf(dev, "can't establish configuration hook\n");
		return (ENOMEM);
	}

	ipmi_attached = 1;
	return (0);
}