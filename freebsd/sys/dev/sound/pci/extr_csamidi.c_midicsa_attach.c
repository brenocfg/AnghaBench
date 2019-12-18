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
struct sndcard_func {int dummy; } ;
struct csa_midi_softc {int /*<<< orphan*/ * io; int /*<<< orphan*/  io_rid; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * mpu; int /*<<< orphan*/  mpu_intr; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_HICR ; 
 int /*<<< orphan*/  BA0_MIDCR ; 
 int ENOMEM ; 
 int ENXIO ; 
 int HICR_CHGM ; 
 int HICR_IEV ; 
 int MIDCR_MRST ; 
 int MIDCR_RXE ; 
 int MIDCR_TXE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct csa_midi_softc*,int) ; 
 int /*<<< orphan*/  csamidi_midi_intr ; 
 int /*<<< orphan*/  csamidi_mpu_class ; 
 int /*<<< orphan*/  csamidi_writeio (struct csa_midi_softc*,int /*<<< orphan*/ ,int) ; 
 struct sndcard_func* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct csa_midi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpu401_init (int /*<<< orphan*/ *,struct csa_midi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
midicsa_attach(device_t dev)
{
	struct csa_midi_softc *scp;
	struct sndcard_func *func;
	int rc = ENXIO;

	scp = device_get_softc(dev);
	func = device_get_ivars(dev);

	bzero(scp, sizeof(struct csa_midi_softc));
	scp->dev = dev;

	/* allocate the required resources */
	scp->io_rid = PCIR_BAR(0);
	scp->io = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &scp->io_rid, RF_ACTIVE);
	if (scp->io == NULL)
		goto err0;

	/* init the fake MPU401 interface. */
	scp->mpu = mpu401_init(&csamidi_mpu_class, scp, csamidi_midi_intr,
	    &scp->mpu_intr);
	if (scp->mpu == NULL) {
		rc = ENOMEM;
		goto err1;
	}

	mtx_init(&scp->mtx, device_get_nameunit(dev), "csamidi softc",
	    MTX_DEF);

	/* reset the MIDI port */
	csamidi_writeio(scp, BA0_MIDCR, MIDCR_MRST);
	/* MIDI transmit enable, no interrupt */
	csamidi_writeio(scp, BA0_MIDCR, MIDCR_TXE | MIDCR_RXE);
	csamidi_writeio(scp, BA0_HICR, HICR_IEV | HICR_CHGM);

	return (0);
err1:
	bus_release_resource(dev, SYS_RES_MEMORY, scp->io_rid, scp->io);
	scp->io = NULL;
err0:
	return (rc);
}