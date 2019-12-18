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
struct ipmi_softc {scalar_t__ ipmi_irq_rid; int /*<<< orphan*/  ipmi_irq_res; int /*<<< orphan*/  ipmi_dev; } ;
struct ipmi_get_info {scalar_t__ iface_type; scalar_t__ irq; scalar_t__ address; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 scalar_t__ SSIF_MODE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ipmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int ipmi_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_release_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_smbios_identify (struct ipmi_get_info*) ; 
 int ipmi_ssif_attach (struct ipmi_softc*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ipmi_smbus_attach(device_t dev)
{
	struct ipmi_softc *sc = device_get_softc(dev);
	struct ipmi_get_info info;
	int error;

	/* This should never fail. */
	if (!ipmi_smbios_identify(&info))
		return (ENXIO);

	if (info.iface_type != SSIF_MODE) {
		device_printf(dev, "No SSIF IPMI interface found\n");
		return (ENXIO);
	}

	sc->ipmi_dev = dev;

	if (info.irq != 0) {
		sc->ipmi_irq_rid = 0;
		sc->ipmi_irq_res = bus_alloc_resource(dev, SYS_RES_IRQ,
		    &sc->ipmi_irq_rid, info.irq, info.irq, 1,
		    RF_SHAREABLE | RF_ACTIVE);
	}

	device_printf(dev, "SSIF mode found at address 0x%llx on %s\n",
	    (long long)info.address, device_get_name(device_get_parent(dev)));
	error = ipmi_ssif_attach(sc, device_get_parent(dev), info.address);
	if (error)
		goto bad;

	error = ipmi_attach(dev);
	if (error)
		goto bad;

	return (0);
bad:
	ipmi_release_resources(dev);
	return (error);
}