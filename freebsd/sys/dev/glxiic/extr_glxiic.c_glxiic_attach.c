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
typedef  int /*<<< orphan*/  uint32_t ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct glxiic_softc {int old_irq; int /*<<< orphan*/ * irq_res; void* irq_rid; int /*<<< orphan*/ * irq_handler; int /*<<< orphan*/ * gpio_res; void* gpio_rid; int /*<<< orphan*/ * smb_res; void* smb_rid; int /*<<< orphan*/ * iicbus; int /*<<< orphan*/  callout; int /*<<< orphan*/  timeout; int /*<<< orphan*/  mtx; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ich_func_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int ENXIO ; 
 int /*<<< orphan*/  GLXIIC_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  GLXIIC_LOCK_DESTROY (struct glxiic_softc*) ; 
 int /*<<< orphan*/  GLXIIC_LOCK_INIT (struct glxiic_softc*) ; 
 int GLXIIC_MAP_TO_SMB_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLXIIC_MSR_PIC_YSEL_HIGH ; 
 int /*<<< orphan*/  GLXIIC_STATE_IDLE ; 
 int /*<<< orphan*/  IIC_FASTEST ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  OID_AUTO ; 
 void* PCIR_BAR (int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int,int,int,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int) ; 
 scalar_t__ bus_generic_attach ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glxiic_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_oneshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct glxiic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  glxiic_gpio_disable (struct glxiic_softc*) ; 
 int /*<<< orphan*/  glxiic_gpio_enable (struct glxiic_softc*) ; 
 int /*<<< orphan*/  glxiic_intr ; 
 int /*<<< orphan*/  glxiic_smb_disable (struct glxiic_softc*) ; 
 int /*<<< orphan*/  glxiic_smb_enable (struct glxiic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxiic_smb_map_interrupt (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_int_value (char*,int,char*,int*) ; 

__attribute__((used)) static int
glxiic_attach(device_t dev)
{
	struct glxiic_softc *sc;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree;
	int error, irq, unit;
	uint32_t irq_map;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->state = GLXIIC_STATE_IDLE;
	error = 0;

	GLXIIC_LOCK_INIT(sc);
	callout_init_mtx(&sc->callout, &sc->mtx, 0);

	sc->smb_rid = PCIR_BAR(0);
	sc->smb_res = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &sc->smb_rid,
	    RF_ACTIVE);
	if (sc->smb_res == NULL) {
		device_printf(dev, "Could not allocate SMBus I/O port\n");
		error = ENXIO;
		goto out;
	}

	sc->gpio_rid = PCIR_BAR(1);
	sc->gpio_res = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
	    &sc->gpio_rid, RF_SHAREABLE | RF_ACTIVE);
	if (sc->gpio_res == NULL) {
		device_printf(dev, "Could not allocate GPIO I/O port\n");
		error = ENXIO;
		goto out;
	}

	/* Ensure the controller is not enabled by firmware. */
	glxiic_smb_disable(sc);

	/* Read the existing IRQ map. */
	irq_map = rdmsr(GLXIIC_MSR_PIC_YSEL_HIGH);
	sc->old_irq = GLXIIC_MAP_TO_SMB_IRQ(irq_map);

	unit = device_get_unit(dev);
	if (resource_int_value("glxiic", unit, "irq", &irq) == 0) {
		if (irq < 1 || irq > 15) {
			device_printf(dev, "Bad value %d for glxiic.%d.irq\n",
			    irq, unit);
			error = ENXIO;
			goto out;
		}

		if (bootverbose)
			device_printf(dev, "Using irq %d set by hint\n", irq);
	} else if (sc->old_irq != 0) {
		if (bootverbose)
			device_printf(dev, "Using irq %d set by firmware\n",
			    irq);
		irq = sc->old_irq;
	} else {
		device_printf(dev, "No irq mapped by firmware");
		printf(" and no glxiic.%d.irq hint provided\n", unit);
		error = ENXIO;
		goto out;
	}

	/* Map the SMBus interrupt to the requested legacy IRQ. */
	glxiic_smb_map_interrupt(irq);

	sc->irq_rid = 0;
	sc->irq_res = bus_alloc_resource(dev, SYS_RES_IRQ, &sc->irq_rid,
	    irq, irq, 1, RF_SHAREABLE | RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "Could not allocate IRQ %d\n", irq);
		error = ENXIO;
		goto out;
	}

	error = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, glxiic_intr, sc, &(sc->irq_handler));
	if (error != 0) {
		device_printf(dev, "Could not setup IRQ handler\n");
		error = ENXIO;
		goto out;
	}

	if ((sc->iicbus = device_add_child(dev, "iicbus", -1)) == NULL) {
		device_printf(dev, "Could not allocate iicbus instance\n");
		error = ENXIO;
		goto out;
	}

	ctx = device_get_sysctl_ctx(dev);
	tree = device_get_sysctl_tree(dev);

	sc->timeout = GLXIIC_DEFAULT_TIMEOUT;
	SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "timeout", CTLFLAG_RWTUN, &sc->timeout, 0,
	    "activity timeout in ms");

	glxiic_gpio_enable(sc);
	glxiic_smb_enable(sc, IIC_FASTEST, 0);

	/* Probe and attach the iicbus when interrupts are available. */
	config_intrhook_oneshot((ich_func_t)bus_generic_attach, dev);
	error = 0;

out:
	if (error != 0) {
		callout_drain(&sc->callout);

		if (sc->iicbus != NULL)
			device_delete_child(dev, sc->iicbus);
		if (sc->smb_res != NULL) {
			glxiic_smb_disable(sc);
			bus_release_resource(dev, SYS_RES_IOPORT, sc->smb_rid,
			    sc->smb_res);
		}
		if (sc->gpio_res != NULL) {
			glxiic_gpio_disable(sc);
			bus_release_resource(dev, SYS_RES_IOPORT, sc->gpio_rid,
			    sc->gpio_res);
		}
		if (sc->irq_handler != NULL)
			bus_teardown_intr(dev, sc->irq_res, sc->irq_handler);
		if (sc->irq_res != NULL)
			bus_release_resource(dev, SYS_RES_IRQ, sc->irq_rid,
			    sc->irq_res);

		/* Restore the old SMBus interrupt mapping. */
		glxiic_smb_map_interrupt(sc->old_irq);

		GLXIIC_LOCK_DESTROY(sc);
	}

	return (error);
}