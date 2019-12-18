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
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 scalar_t__ ENXIO ; 
 scalar_t__ IO_KBD ; 
 scalar_t__ ISA_PNP_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KBD_STATUS_PORT ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  atkbdc_ids ; 
 int atkbdc_probe_unit (int /*<<< orphan*/ ,struct resource*,struct resource*) ; 
 scalar_t__ bootverbose ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_verbose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 

__attribute__((used)) static int
atkbdc_isa_probe(device_t dev)
{
	struct resource	*port0;
	struct resource	*port1;
	rman_res_t	start;
	rman_res_t	count;
	int		error;
	int		rid;
#if defined(__i386__) || defined(__amd64__)
	bus_space_tag_t	tag;
	bus_space_handle_t ioh1;
	volatile int	i;
	register_t	flags;
#endif

	/* check PnP IDs */
	if (ISA_PNP_PROBE(device_get_parent(dev), dev, atkbdc_ids) == ENXIO)
		return ENXIO;

	device_set_desc(dev, "Keyboard controller (i8042)");

	/*
	 * Adjust I/O port resources.
	 * The AT keyboard controller uses two ports (a command/data port
	 * 0x60 and a status port 0x64), which may be given to us in 
	 * one resource (0x60 through 0x64) or as two separate resources
	 * (0x60 and 0x64). Some brain-damaged ACPI BIOS has reversed
	 * command/data port and status port. Furthermore, /boot/device.hints
	 * may contain just one port, 0x60. We shall adjust resource settings
	 * so that these two ports are available as two separate resources
	 * in correct order.
	 */
	device_quiet(dev);
	rid = 0;
	if (bus_get_resource(dev, SYS_RES_IOPORT, rid, &start, &count) != 0)
		return ENXIO;
	if (start == IO_KBD + KBD_STATUS_PORT) {
		start = IO_KBD;
		count++;
	}
	if (count > 1)	/* adjust the count and/or start port */
		bus_set_resource(dev, SYS_RES_IOPORT, rid, start, 1);
	port0 = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid, RF_ACTIVE);
	if (port0 == NULL)
		return ENXIO;
	rid = 1;
	if (bus_get_resource(dev, SYS_RES_IOPORT, rid, NULL, NULL) != 0)
		bus_set_resource(dev, SYS_RES_IOPORT, 1,
				 start + KBD_STATUS_PORT, 1);
	port1 = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid, RF_ACTIVE);
	if (port1 == NULL) {
		bus_release_resource(dev, SYS_RES_IOPORT, 0, port0);
		return ENXIO;
	}

#if defined(__i386__) || defined(__amd64__)
	/*
	 * Check if we really have AT keyboard controller. Poll status
	 * register until we get "all clear" indication. If no such
	 * indication comes, it probably means that there is no AT
	 * keyboard controller present. Give up in such case. Check relies
	 * on the fact that reading from non-existing in/out port returns
	 * 0xff on i386. May or may not be true on other platforms.
	 */
	tag = rman_get_bustag(port0);
	ioh1 = rman_get_bushandle(port1);
	flags = intr_disable();
	for (i = 0; i != 65535; i++) {
		if ((bus_space_read_1(tag, ioh1, 0) & 0x2) == 0)
			break;
	}
	intr_restore(flags);
	if (i == 65535) {
		bus_release_resource(dev, SYS_RES_IOPORT, 0, port0);
		bus_release_resource(dev, SYS_RES_IOPORT, 1, port1);
		if (bootverbose)
			device_printf(dev, "AT keyboard controller not found\n");
		return ENXIO;
	}
#endif

	device_verbose(dev);

	error = atkbdc_probe_unit(device_get_unit(dev), port0, port1);

	bus_release_resource(dev, SYS_RES_IOPORT, 0, port0);
	bus_release_resource(dev, SYS_RES_IOPORT, 1, port1);

	return error;
}