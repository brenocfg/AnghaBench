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
typedef  int uint32_t ;
struct TYPE_2__ {struct mrsas_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct mrsas_softc {int device_id; int mrsas_gen3_ctrl; int is_ventura; int is_aero; int msix_enable; int /*<<< orphan*/ * reg_res; void* reg_res_id; int /*<<< orphan*/  mrsas_dev; int /*<<< orphan*/  stream_lock; int /*<<< orphan*/  raidmap_lock; int /*<<< orphan*/  mfi_cmd_pool_lock; int /*<<< orphan*/  mpt_cmd_pool_lock; int /*<<< orphan*/  ioctl_lock; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  pci_lock; int /*<<< orphan*/  aen_lock; int /*<<< orphan*/  sim_lock; int /*<<< orphan*/  ocr_chan; scalar_t__ ocr_thread_active; TYPE_1__ mrsas_ich; int /*<<< orphan*/  ocr_thread; scalar_t__ UnevenSpanSupport; int /*<<< orphan*/  adprecovery; scalar_t__ io_cmds_highwater; int /*<<< orphan*/  sge_holes; int /*<<< orphan*/  prp_count; int /*<<< orphan*/  target_reset_outstanding; int /*<<< orphan*/  fw_outstanding; int /*<<< orphan*/  mrsas_mfi_cmd_list_head; int /*<<< orphan*/  mrsas_mpt_cmd_list_head; int /*<<< orphan*/  bus_handle; int /*<<< orphan*/  bus_tag; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
#define  MRSAS_AERO_10E0 147 
#define  MRSAS_AERO_10E1 146 
#define  MRSAS_AERO_10E2 145 
#define  MRSAS_AERO_10E3 144 
#define  MRSAS_AERO_10E4 143 
#define  MRSAS_AERO_10E5 142 
#define  MRSAS_AERO_10E6 141 
#define  MRSAS_AERO_10E7 140 
#define  MRSAS_CRUSADER 139 
#define  MRSAS_CRUSADER_4PORT 138 
#define  MRSAS_CUTLASS_52 137 
#define  MRSAS_CUTLASS_53 136 
#define  MRSAS_FURY 135 
#define  MRSAS_HARPOON 134 
 int /*<<< orphan*/  MRSAS_HBA_OPERATIONAL ; 
#define  MRSAS_INTRUDER 133 
#define  MRSAS_INTRUDER_24 132 
#define  MRSAS_INVADER 131 
#define  MRSAS_TOMCAT 130 
#define  MRSAS_VENTURA 129 
#define  MRSAS_VENTURA_4PORT 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int PCIM_CMD_PORTEN ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 struct mrsas_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct mrsas_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrsas_atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mrsas_cam_attach (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_cam_detach (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_free_mem (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_get_tunables (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_ich_startup ; 
 int mrsas_init_fw (struct mrsas_softc*) ; 
 int mrsas_kproc_create (int /*<<< orphan*/ ,struct mrsas_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrsas_ocr_thread ; 
 int mrsas_setup_irq (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_setup_sysctl (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_teardown_intr (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mrsas_attach(device_t dev)
{
	struct mrsas_softc *sc = device_get_softc(dev);
	uint32_t cmd, error;

	memset(sc, 0, sizeof(struct mrsas_softc));

	/* Look up our softc and initialize its fields. */
	sc->mrsas_dev = dev;
	sc->device_id = pci_get_device(dev);

	switch (sc->device_id) {
	case MRSAS_INVADER:
	case MRSAS_FURY:
	case MRSAS_INTRUDER:
	case MRSAS_INTRUDER_24:
	case MRSAS_CUTLASS_52:
	case MRSAS_CUTLASS_53:
		sc->mrsas_gen3_ctrl = 1;
		break;
	case MRSAS_VENTURA:
	case MRSAS_CRUSADER:
	case MRSAS_HARPOON:
	case MRSAS_TOMCAT:
	case MRSAS_VENTURA_4PORT:
	case MRSAS_CRUSADER_4PORT:
		sc->is_ventura = true;
		break;
	case MRSAS_AERO_10E1:
	case MRSAS_AERO_10E5:
		device_printf(dev, "Adapter is in configurable secure mode\n");
	case MRSAS_AERO_10E2:
	case MRSAS_AERO_10E6:
		sc->is_aero = true;
		break;
	case MRSAS_AERO_10E0:
	case MRSAS_AERO_10E3:
	case MRSAS_AERO_10E4:
	case MRSAS_AERO_10E7:
		device_printf(dev, "Adapter is in non-secure mode\n");
		return SUCCESS;

	}

	mrsas_get_tunables(sc);

	/*
	 * Set up PCI and registers
	 */
	cmd = pci_read_config(dev, PCIR_COMMAND, 2);
	if ((cmd & PCIM_CMD_PORTEN) == 0) {
		return (ENXIO);
	}
	/* Force the busmaster enable bit on. */
	cmd |= PCIM_CMD_BUSMASTEREN;
	pci_write_config(dev, PCIR_COMMAND, cmd, 2);

	/* For Ventura/Aero system registers are mapped to BAR0 */
	if (sc->is_ventura || sc->is_aero)
		sc->reg_res_id = PCIR_BAR(0);	/* BAR0 offset */
	else
		sc->reg_res_id = PCIR_BAR(1);	/* BAR1 offset */

	if ((sc->reg_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &(sc->reg_res_id), RF_ACTIVE))
	    == NULL) {
		device_printf(dev, "Cannot allocate PCI registers\n");
		goto attach_fail;
	}
	sc->bus_tag = rman_get_bustag(sc->reg_res);
	sc->bus_handle = rman_get_bushandle(sc->reg_res);

	/* Intialize mutexes */
	mtx_init(&sc->sim_lock, "mrsas_sim_lock", NULL, MTX_DEF);
	mtx_init(&sc->pci_lock, "mrsas_pci_lock", NULL, MTX_DEF);
	mtx_init(&sc->io_lock, "mrsas_io_lock", NULL, MTX_DEF);
	mtx_init(&sc->aen_lock, "mrsas_aen_lock", NULL, MTX_DEF);
	mtx_init(&sc->ioctl_lock, "mrsas_ioctl_lock", NULL, MTX_SPIN);
	mtx_init(&sc->mpt_cmd_pool_lock, "mrsas_mpt_cmd_pool_lock", NULL, MTX_DEF);
	mtx_init(&sc->mfi_cmd_pool_lock, "mrsas_mfi_cmd_pool_lock", NULL, MTX_DEF);
	mtx_init(&sc->raidmap_lock, "mrsas_raidmap_lock", NULL, MTX_DEF);
	mtx_init(&sc->stream_lock, "mrsas_stream_lock", NULL, MTX_DEF);

	/* Intialize linked list */
	TAILQ_INIT(&sc->mrsas_mpt_cmd_list_head);
	TAILQ_INIT(&sc->mrsas_mfi_cmd_list_head);

	mrsas_atomic_set(&sc->fw_outstanding, 0);
	mrsas_atomic_set(&sc->target_reset_outstanding, 0);
	mrsas_atomic_set(&sc->prp_count, 0);
	mrsas_atomic_set(&sc->sge_holes, 0);

	sc->io_cmds_highwater = 0;

	sc->adprecovery = MRSAS_HBA_OPERATIONAL;
	sc->UnevenSpanSupport = 0;

	sc->msix_enable = 0;

	/* Initialize Firmware */
	if (mrsas_init_fw(sc) != SUCCESS) {
		goto attach_fail_fw;
	}
	/* Register mrsas to CAM layer */
	if ((mrsas_cam_attach(sc) != SUCCESS)) {
		goto attach_fail_cam;
	}
	/* Register IRQs */
	if (mrsas_setup_irq(sc) != SUCCESS) {
		goto attach_fail_irq;
	}
	error = mrsas_kproc_create(mrsas_ocr_thread, sc,
	    &sc->ocr_thread, 0, 0, "mrsas_ocr%d",
	    device_get_unit(sc->mrsas_dev));
	if (error) {
		device_printf(sc->mrsas_dev, "Error %d starting OCR thread\n", error);
		goto attach_fail_ocr_thread;
	}
	/*
	 * After FW initialization and OCR thread creation
	 * we will defer the cdev creation, AEN setup on ICH callback
	 */
	sc->mrsas_ich.ich_func = mrsas_ich_startup;
	sc->mrsas_ich.ich_arg = sc;
	if (config_intrhook_establish(&sc->mrsas_ich) != 0) {
		device_printf(sc->mrsas_dev, "Config hook is already established\n");
	}
	mrsas_setup_sysctl(sc);
	return SUCCESS;

attach_fail_ocr_thread:
	if (sc->ocr_thread_active)
		wakeup(&sc->ocr_chan);
attach_fail_irq:
	mrsas_teardown_intr(sc);
attach_fail_cam:
	mrsas_cam_detach(sc);
attach_fail_fw:
	/* if MSIX vector is allocated and FW Init FAILED then release MSIX */
	if (sc->msix_enable == 1)
		pci_release_msi(sc->mrsas_dev);
	mrsas_free_mem(sc);
	mtx_destroy(&sc->sim_lock);
	mtx_destroy(&sc->aen_lock);
	mtx_destroy(&sc->pci_lock);
	mtx_destroy(&sc->io_lock);
	mtx_destroy(&sc->ioctl_lock);
	mtx_destroy(&sc->mpt_cmd_pool_lock);
	mtx_destroy(&sc->mfi_cmd_pool_lock);
	mtx_destroy(&sc->raidmap_lock);
	mtx_destroy(&sc->stream_lock);
attach_fail:
	if (sc->reg_res) {
		bus_release_resource(sc->mrsas_dev, SYS_RES_MEMORY,
		    sc->reg_res_id, sc->reg_res);
	}
	return (ENXIO);
}