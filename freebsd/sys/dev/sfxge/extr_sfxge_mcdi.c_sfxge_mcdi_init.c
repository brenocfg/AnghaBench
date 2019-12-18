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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  emt_logger; int /*<<< orphan*/  emt_exception; int /*<<< orphan*/  emt_ev_cpl; int /*<<< orphan*/  emt_execute; int /*<<< orphan*/ * emt_dma_mem; struct sfxge_softc* emt_context; } ;
struct sfxge_mcdi {scalar_t__ state; int /*<<< orphan*/  mem; TYPE_1__ transport; } ;
struct sfxge_softc {int /*<<< orphan*/  mcdi_logging; int /*<<< orphan*/  dev; struct sfxge_mcdi mcdi; int /*<<< orphan*/ * enp; } ;
typedef  int /*<<< orphan*/  efx_nic_t ;
typedef  TYPE_1__ efx_mcdi_transport_t ;
typedef  int /*<<< orphan*/  efsys_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MCDI_CTL_SDU_LEN_MAX_V2 ; 
 int /*<<< orphan*/  OID_AUTO ; 
 scalar_t__ SFXGE_MCDI_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_MCDI_LOCK_DESTROY (struct sfxge_mcdi*) ; 
 int /*<<< orphan*/  SFXGE_MCDI_LOCK_INIT (struct sfxge_mcdi*,int /*<<< orphan*/ ) ; 
 scalar_t__ SFXGE_MCDI_UNINITIALIZED ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int efx_mcdi_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int sfxge_dma_alloc (struct sfxge_softc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_mcdi_ev_cpl ; 
 int /*<<< orphan*/  sfxge_mcdi_exception ; 
 int /*<<< orphan*/  sfxge_mcdi_execute ; 
 int /*<<< orphan*/  sfxge_mcdi_logger ; 

int
sfxge_mcdi_init(struct sfxge_softc *sc)
{
	efx_nic_t *enp;
	struct sfxge_mcdi *mcdi;
	efx_mcdi_transport_t *emtp;
	efsys_mem_t *esmp;
	int max_msg_size;
	int rc;

	enp = sc->enp;
	mcdi = &sc->mcdi;
	emtp = &mcdi->transport;
	esmp = &mcdi->mem;
	max_msg_size = sizeof (uint32_t) + MCDI_CTL_SDU_LEN_MAX_V2;

	KASSERT(mcdi->state == SFXGE_MCDI_UNINITIALIZED,
	    ("MCDI already initialized"));

	SFXGE_MCDI_LOCK_INIT(mcdi, device_get_nameunit(sc->dev));

	mcdi->state = SFXGE_MCDI_INITIALIZED;

	if ((rc = sfxge_dma_alloc(sc, max_msg_size, esmp)) != 0)
		goto fail;

	emtp->emt_context = sc;
	emtp->emt_dma_mem = esmp;
	emtp->emt_execute = sfxge_mcdi_execute;
	emtp->emt_ev_cpl = sfxge_mcdi_ev_cpl;
	emtp->emt_exception = sfxge_mcdi_exception;
#if EFSYS_OPT_MCDI_LOGGING
	emtp->emt_logger = sfxge_mcdi_logger;
	SYSCTL_ADD_INT(device_get_sysctl_ctx(sc->dev),
		       SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev)),
		       OID_AUTO, "mcdi_logging", CTLFLAG_RW,
		       &sc->mcdi_logging, 0,
		       "MCDI logging");
#endif

	if ((rc = efx_mcdi_init(enp, emtp)) != 0)
		goto fail;

	return (0);

fail:
	SFXGE_MCDI_LOCK_DESTROY(mcdi);
	mcdi->state = SFXGE_MCDI_UNINITIALIZED;
	return (rc);
}