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
struct smu_softc {int sc_doorbellirqid; int sc_u3; int sc_cpu_diode_scale; int sc_cpu_diode_offset; int sc_cpu_volt_scale; int sc_cpu_volt_offset; int sc_cpu_curr_scale; int sc_cpu_curr_offset; int sc_slots_pow_scale; int sc_slots_pow_offset; int /*<<< orphan*/  sc_doorbellirq; int /*<<< orphan*/  sc_doorbellirqcookie; int /*<<< orphan*/  sc_leddev; int /*<<< orphan*/  sc_cmdq; int /*<<< orphan*/  sc_cmd; int /*<<< orphan*/  sc_cmd_dmamap; int /*<<< orphan*/  sc_dmatag; int /*<<< orphan*/  sc_mailbox; int /*<<< orphan*/ * sc_bt; int /*<<< orphan*/ * sc_cur_cmd; int /*<<< orphan*/  sc_mtx; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTR_MPSAFE ; 
 int /*<<< orphan*/  INTR_POLARITY_LOW ; 
 int /*<<< orphan*/  INTR_TRIGGER_EDGE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getprop (scalar_t__,char*,char*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_LAST ; 
 int /*<<< orphan*/  SMU_CPUTEMP_CAL ; 
 int /*<<< orphan*/  SMU_CPUVOLT_CAL ; 
 int /*<<< orphan*/  SMU_MAILBOX ; 
 int /*<<< orphan*/  SMU_SLOTPW_CAL ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bs_le_tag ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpufreq_post_change ; 
 int /*<<< orphan*/  cpufreq_pre_change ; 
 struct smu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerpc_config_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  smu_attach_fans (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  smu_attach_i2c (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  smu_attach_sensors (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  smu_cpufreq_post_change ; 
 int /*<<< orphan*/  smu_cpufreq_pre_change ; 
 int /*<<< orphan*/  smu_doorbell ; 
 int /*<<< orphan*/  smu_doorbell_intr ; 
 int /*<<< orphan*/  smu_get_datablock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  smu_phys_callback ; 
 int /*<<< orphan*/  smu_server_mode ; 
 int /*<<< orphan*/  smu_set_sleepled ; 
 int /*<<< orphan*/  smu_shutdown ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
smu_attach(device_t dev)
{
	struct smu_softc *sc;
	phandle_t	node, child;
	uint8_t		data[12];

	sc = device_get_softc(dev);

	mtx_init(&sc->sc_mtx, "smu", NULL, MTX_DEF);
	sc->sc_cur_cmd = NULL;
	sc->sc_doorbellirqid = -1;

	sc->sc_u3 = 0;
	if (OF_finddevice("/u3") != -1)
		sc->sc_u3 = 1;

	/*
	 * Map the mailbox area. This should be determined from firmware,
	 * but I have not found a simple way to do that.
	 */
	bus_dma_tag_create(NULL, 16, 0, BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR, NULL, NULL, PAGE_SIZE, 1, PAGE_SIZE, 0, NULL,
	    NULL, &(sc->sc_dmatag));
	sc->sc_bt = &bs_le_tag;
	bus_space_map(sc->sc_bt, SMU_MAILBOX, 4, 0, &sc->sc_mailbox);

	/*
	 * Allocate the command buffer. This can be anywhere in the low 4 GB
	 * of memory.
	 */
	bus_dmamem_alloc(sc->sc_dmatag, (void **)&sc->sc_cmd, BUS_DMA_WAITOK | 
	    BUS_DMA_ZERO, &sc->sc_cmd_dmamap);
	bus_dmamap_load(sc->sc_dmatag, sc->sc_cmd_dmamap,
	    sc->sc_cmd, PAGE_SIZE, smu_phys_callback, sc, 0);
	STAILQ_INIT(&sc->sc_cmdq);

	/*
	 * Set up handlers to change CPU voltage when CPU frequency is changed.
	 */
	EVENTHANDLER_REGISTER(cpufreq_pre_change, smu_cpufreq_pre_change, dev,
	    EVENTHANDLER_PRI_ANY);
	EVENTHANDLER_REGISTER(cpufreq_post_change, smu_cpufreq_post_change, dev,
	    EVENTHANDLER_PRI_ANY);

	node = ofw_bus_get_node(dev);

	/* Some SMUs have RPM and PWM controlled fans which do not sit
	 * under the same node. So we have to attach them separately.
	 */
	smu_attach_fans(dev, node);

	/*
	 * Now detect and attach the other child devices.
	 */
	for (child = OF_child(node); child != 0; child = OF_peer(child)) {
		char name[32];
		memset(name, 0, sizeof(name));
		OF_getprop(child, "name", name, sizeof(name));

		if (strncmp(name, "sensors", 8) == 0)
			smu_attach_sensors(dev, child);

		if (strncmp(name, "smu-i2c-control", 15) == 0)
			smu_attach_i2c(dev, child);
	}

	/* Some SMUs have the I2C children directly under the bus. */
	smu_attach_i2c(dev, node);

	/*
	 * Collect calibration constants.
	 */
	smu_get_datablock(dev, SMU_CPUTEMP_CAL, data, sizeof(data));
	sc->sc_cpu_diode_scale = (data[4] << 8) + data[5];
	sc->sc_cpu_diode_offset = (data[6] << 8) + data[7];

	smu_get_datablock(dev, SMU_CPUVOLT_CAL, data, sizeof(data));
	sc->sc_cpu_volt_scale = (data[4] << 8) + data[5];
	sc->sc_cpu_volt_offset = (data[6] << 8) + data[7];
	sc->sc_cpu_curr_scale = (data[8] << 8) + data[9];
	sc->sc_cpu_curr_offset = (data[10] << 8) + data[11];

	smu_get_datablock(dev, SMU_SLOTPW_CAL, data, sizeof(data));
	sc->sc_slots_pow_scale = (data[4] << 8) + data[5];
	sc->sc_slots_pow_offset = (data[6] << 8) + data[7];

	/*
	 * Set up LED interface
	 */
	sc->sc_leddev = led_create(smu_set_sleepled, dev, "sleepled");

	/*
	 * Reset on power loss behavior
	 */

	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
            SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "server_mode", CTLTYPE_INT | CTLFLAG_RW, dev, 0,
	    smu_server_mode, "I", "Enable reboot after power failure");

	/*
	 * Set up doorbell interrupt.
	 */
	sc->sc_doorbellirqid = 0;
	sc->sc_doorbellirq = bus_alloc_resource_any(smu_doorbell, SYS_RES_IRQ,
	    &sc->sc_doorbellirqid, RF_ACTIVE);
	bus_setup_intr(smu_doorbell, sc->sc_doorbellirq,
	    INTR_TYPE_MISC | INTR_MPSAFE, NULL, smu_doorbell_intr, dev,
	    &sc->sc_doorbellirqcookie);
	powerpc_config_intr(rman_get_start(sc->sc_doorbellirq),
	    INTR_TRIGGER_EDGE, INTR_POLARITY_LOW);

	/*
	 * Connect RTC interface.
	 */
	clock_register(dev, 1000);

	/*
	 * Learn about shutdown events
	 */
	EVENTHANDLER_REGISTER(shutdown_final, smu_shutdown, dev,
	    SHUTDOWN_PRI_LAST);

	return (bus_generic_attach(dev));
}