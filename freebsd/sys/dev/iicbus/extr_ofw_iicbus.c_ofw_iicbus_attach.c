#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_2__ {int addr; int /*<<< orphan*/  rl; } ;
struct ofw_iicbus_devinfo {TYPE_1__ opd_dinfo; int /*<<< orphan*/  opd_obdinfo; } ;
struct iicbus_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;
typedef  scalar_t__ phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  paddr ;
typedef  int /*<<< orphan*/  freq ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  compat ;

/* Variables and functions */
 struct iicbus_softc* IICBUS_SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIC_FASTEST ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OF_getencprop (scalar_t__,char*,int*,int) ; 
 int OF_getprop (scalar_t__,char*,char*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_xref_from_node (scalar_t__) ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,struct ofw_iicbus_devinfo*) ; 
 int /*<<< orphan*/  free (struct ofw_iicbus_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_init_frequency (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iicbus_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ofw_iicbus_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_intr_to_rl (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
ofw_iicbus_attach(device_t dev)
{
	struct iicbus_softc *sc = IICBUS_SOFTC(dev);
	struct ofw_iicbus_devinfo *dinfo;
	phandle_t child, node, root;
	pcell_t freq, paddr;
	device_t childdev;
	ssize_t compatlen;
	char compat[255];
	char *curstr;
	u_int iic_addr_8bit = 0;

	sc->dev = dev;
	mtx_init(&sc->lock, "iicbus", NULL, MTX_DEF);

	/*
	 * If there is a clock-frequency property for the device node, use it as
	 * the starting value for the bus frequency.  Then call the common
	 * routine that handles the tunable/sysctl which allows the FDT value to
	 * be overridden by the user.
	 */
	node = ofw_bus_get_node(dev);
	freq = 0;
	OF_getencprop(node, "clock-frequency", &freq, sizeof(freq));
	iicbus_init_frequency(dev, freq);
	
	iicbus_reset(dev, IIC_FASTEST, 0, NULL);

	bus_generic_probe(dev);
	bus_enumerate_hinted_children(dev);

	/*
	 * Check if we're running on a PowerMac, needed for the I2C
	 * address below.
	 */
	root = OF_peer(0);
	compatlen = OF_getprop(root, "compatible", compat,
				sizeof(compat));
	if (compatlen != -1) {
	    for (curstr = compat; curstr < compat + compatlen;
		curstr += strlen(curstr) + 1) {
		if (strncmp(curstr, "MacRISC", 7) == 0)
		    iic_addr_8bit = 1;
	    }
	}

	/*
	 * Attach those children represented in the device tree.
	 */
	for (child = OF_child(node); child != 0; child = OF_peer(child)) {
		/*
		 * Try to get the I2C address first from the i2c-address
		 * property, then try the reg property.  It moves around
		 * on different systems.
		 */
		if (OF_getencprop(child, "i2c-address", &paddr,
		    sizeof(paddr)) == -1)
			if (OF_getencprop(child, "reg", &paddr,
			    sizeof(paddr)) == -1)
				continue;

		/*
		 * Now set up the I2C and OFW bus layer devinfo and add it
		 * to the bus.
		 */
		dinfo = malloc(sizeof(struct ofw_iicbus_devinfo), M_DEVBUF,
		    M_NOWAIT | M_ZERO);
		if (dinfo == NULL)
			continue;
		/*
		 * FreeBSD drivers expect I2C addresses to be expressed as
		 * 8-bit values.  Apple OFW data contains 8-bit values, but
		 * Linux FDT data contains 7-bit values, so shift them up to
		 * 8-bit format.
		 */
		if (iic_addr_8bit)
		    dinfo->opd_dinfo.addr = paddr;
		else
		    dinfo->opd_dinfo.addr = paddr << 1;

		if (ofw_bus_gen_setup_devinfo(&dinfo->opd_obdinfo, child) !=
		    0) {
			free(dinfo, M_DEVBUF);
			continue;
		}

		childdev = device_add_child(dev, NULL, -1);
		resource_list_init(&dinfo->opd_dinfo.rl);
		ofw_bus_intr_to_rl(childdev, child,
					&dinfo->opd_dinfo.rl, NULL);
		device_set_ivars(childdev, dinfo);
	}

	/* Register bus */
	OF_device_register_xref(OF_xref_from_node(node), dev);
	return (bus_generic_attach(dev));
}