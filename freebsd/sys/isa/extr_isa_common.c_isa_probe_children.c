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
struct isa_device {scalar_t__ id_order; scalar_t__ id_vendorid; int /*<<< orphan*/  id_configs; int /*<<< orphan*/  id_config_arg; int /*<<< orphan*/  (* id_config_cb ) (int /*<<< orphan*/ ,struct isa_config*,int /*<<< orphan*/ ) ;} ;
struct isa_config {int dummy; } ;
typedef  struct isa_config device_t ;

/* Variables and functions */
 struct isa_device* DEVTOISA (struct isa_config) ; 
 scalar_t__ ISA_ORDER_PNPBIOS ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_ZERO ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (struct isa_config) ; 
 int /*<<< orphan*/  bus_generic_probe (struct isa_config) ; 
 int /*<<< orphan*/  bzero (struct isa_config*,int) ; 
 scalar_t__ device_get_children (struct isa_config,struct isa_config**,int*) ; 
 scalar_t__ device_is_attached (struct isa_config) ; 
 int /*<<< orphan*/  device_printf (struct isa_config,char*) ; 
 int device_probe_and_attach (struct isa_config) ; 
 int /*<<< orphan*/  free (struct isa_config*,int /*<<< orphan*/ ) ; 
 scalar_t__ isa_assign_resources (struct isa_config) ; 
 int /*<<< orphan*/  isa_claim_resources (struct isa_config,struct isa_config) ; 
 int isa_running ; 
 int /*<<< orphan*/  kern_ident ; 
 struct isa_config* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct isa_config*,int /*<<< orphan*/ ) ; 

void
isa_probe_children(device_t dev)
{
	struct isa_device *idev;
	device_t *children, child;
	struct isa_config *cfg;
	int nchildren, i, err;

	/*
	 * Create all the non-hinted children by calling drivers'
	 * identify methods.
	 */
	bus_generic_probe(dev);

	if (device_get_children(dev, &children, &nchildren))
		return;

	/*
	 * First disable all pnp devices so that they don't get
	 * matched by legacy probes.
	 */
	if (bootverbose)
		printf("isa_probe_children: disabling PnP devices\n");

	cfg = malloc(sizeof(*cfg), M_TEMP, M_NOWAIT|M_ZERO);
	if (cfg == NULL) {
		free(children, M_TEMP);
		return;
	}

	for (i = 0; i < nchildren; i++) {
		idev = DEVTOISA(children[i]);

		bzero(cfg, sizeof(*cfg));
		if (idev->id_config_cb)
			idev->id_config_cb(idev->id_config_arg, cfg, 0);
	}

	free(cfg, M_TEMP);

	/*
	 * Next, probe all the PnP BIOS devices so they can subsume any
	 * hints.
	 */
	for (i = 0; i < nchildren; i++) {
		child = children[i];
		idev = DEVTOISA(child);

		if (idev->id_order > ISA_ORDER_PNPBIOS)
			continue;
		if (!TAILQ_EMPTY(&idev->id_configs) &&
		    !isa_assign_resources(child))
			continue;

		if (device_probe_and_attach(child) == 0)
			isa_claim_resources(dev, child);
	}
	free(children, M_TEMP);

	/*
	 * Next, enumerate hinted devices and probe all non-pnp devices so
	 * that they claim their resources first.
	 */
	bus_enumerate_hinted_children(dev);
	if (device_get_children(dev, &children, &nchildren))
		return;
	if (bootverbose)
		printf("isa_probe_children: probing non-PnP devices\n");
	for (i = 0; i < nchildren; i++) {
		child = children[i];
		idev = DEVTOISA(child);

		if (device_is_attached(child) ||
		    !TAILQ_EMPTY(&idev->id_configs))
			continue;

		err = device_probe_and_attach(child);
		if (err == 0 && idev->id_vendorid == 0 &&
		    strcmp(kern_ident, "GENERIC") == 0 &&
		    device_is_attached(child))
			device_printf(child,
			    "non-PNP ISA device will be removed from GENERIC in FreeBSD 12.\n");
	}

	/*
	 * Finally assign resource to pnp devices and probe them.
	 */
	if (bootverbose)
		printf("isa_probe_children: probing PnP devices\n");
	for (i = 0; i < nchildren; i++) {
		child = children[i];
		idev = DEVTOISA(child);

		if (device_is_attached(child) || TAILQ_EMPTY(&idev->id_configs))
			continue;

		if (isa_assign_resources(child)) {
			device_probe_and_attach(child);
			isa_claim_resources(dev, child);
		}
	}

	free(children, M_TEMP);

	isa_running = 1;
}