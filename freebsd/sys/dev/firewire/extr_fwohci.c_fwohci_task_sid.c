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
struct firewire_comm {int /*<<< orphan*/  dev; } ;
struct fwohci_softc {int /*<<< orphan*/  arrq; int /*<<< orphan*/  arrs; int /*<<< orphan*/  atrs; int /*<<< orphan*/  atrq; int /*<<< orphan*/ * sid_buf; struct firewire_comm fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWOHCI_DMA_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_FW ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int OHCI_SIDSIZE ; 
 int /*<<< orphan*/  OHCI_SID_CNT ; 
 int OHCI_SID_CNT_MASK ; 
 int OHCI_SID_ERR ; 
 int OREAD (struct fwohci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_drain_txq (struct firewire_comm*) ; 
 int /*<<< orphan*/  fw_sidrcv (struct firewire_comm*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fwohci_arcv (struct fwohci_softc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fwohci_txd (struct fwohci_softc*,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fwohci_task_sid(void *arg, int pending)
{
	struct fwohci_softc *sc = (struct fwohci_softc *)arg;
	struct firewire_comm *fc = &sc->fc;
	uint32_t *buf;
	int i, plen;


	/*
	 * We really should have locking
	 * here.  Not sure why it's not
	 */
	plen = OREAD(sc, OHCI_SID_CNT);

	if (plen & OHCI_SID_ERR) {
		device_printf(fc->dev, "SID Error\n");
		return;
	}
	plen &= OHCI_SID_CNT_MASK;
	if (plen < 4 || plen > OHCI_SIDSIZE) {
		device_printf(fc->dev, "invalid SID len = %d\n", plen);
		return;
	}
	plen -= 4; /* chop control info */
	buf = (uint32_t *)malloc(OHCI_SIDSIZE, M_FW, M_NOWAIT);
	if (buf == NULL) {
		device_printf(fc->dev, "malloc failed\n");
		return;
	}
	for (i = 0; i < plen / 4; i++)
		buf[i] = FWOHCI_DMA_READ(sc->sid_buf[i + 1]);

	/* pending all pre-bus_reset packets */
	fwohci_txd(sc, &sc->atrq);
	fwohci_txd(sc, &sc->atrs);
	fwohci_arcv(sc, &sc->arrs, -1);
	fwohci_arcv(sc, &sc->arrq, -1);
	fw_drain_txq(fc);
	fw_sidrcv(fc, buf, plen);
	free(buf, M_FW);
}