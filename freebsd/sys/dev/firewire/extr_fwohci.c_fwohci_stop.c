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
typedef  scalar_t__ u_int ;
struct TYPE_2__ {scalar_t__ nisodma; } ;
struct fwohci_softc {TYPE_1__ fc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FWOHCI_INTMASKCLR ; 
 int /*<<< orphan*/  OHCI_ARQCTLCLR ; 
 int /*<<< orphan*/  OHCI_ARSCTLCLR ; 
 int /*<<< orphan*/  OHCI_ATQCTLCLR ; 
 int /*<<< orphan*/  OHCI_ATSCTLCLR ; 
 int OHCI_CNTL_DMA_RUN ; 
 int /*<<< orphan*/  OHCI_HCCCTL ; 
 int OHCI_HCC_RESET ; 
 int OHCI_INT_DMA_ARRQ ; 
 int OHCI_INT_DMA_ARRS ; 
 int OHCI_INT_DMA_ATRQ ; 
 int OHCI_INT_DMA_ATRS ; 
 int OHCI_INT_DMA_PRRQ ; 
 int OHCI_INT_DMA_PRRS ; 
 int OHCI_INT_EN ; 
 int OHCI_INT_ERR ; 
 int OHCI_INT_PHY_BUS_R ; 
 int OHCI_INT_PHY_INT ; 
 int OHCI_INT_PHY_SID ; 
 int /*<<< orphan*/  OHCI_IRCTLCLR (scalar_t__) ; 
 int /*<<< orphan*/  OHCI_ITCTLCLR (scalar_t__) ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fwohci_set_intr (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
fwohci_stop(struct fwohci_softc *sc, device_t dev)
{
	u_int i;

	fwohci_set_intr(&sc->fc, 0);

/* Now stopping all DMA channel */
	OWRITE(sc, OHCI_ARQCTLCLR, OHCI_CNTL_DMA_RUN);
	OWRITE(sc, OHCI_ARSCTLCLR, OHCI_CNTL_DMA_RUN);
	OWRITE(sc, OHCI_ATQCTLCLR, OHCI_CNTL_DMA_RUN);
	OWRITE(sc, OHCI_ATSCTLCLR, OHCI_CNTL_DMA_RUN);

	for (i = 0; i < sc->fc.nisodma; i++) {
		OWRITE(sc, OHCI_IRCTLCLR(i), OHCI_CNTL_DMA_RUN);
		OWRITE(sc, OHCI_ITCTLCLR(i), OHCI_CNTL_DMA_RUN);
	}

#if 0 /* Let dcons(4) be accessed */
/* Stop interrupt */
	OWRITE(sc, FWOHCI_INTMASKCLR,
			OHCI_INT_EN | OHCI_INT_ERR | OHCI_INT_PHY_SID
			| OHCI_INT_PHY_INT
			| OHCI_INT_DMA_ATRQ | OHCI_INT_DMA_ATRS
			| OHCI_INT_DMA_PRRQ | OHCI_INT_DMA_PRRS
			| OHCI_INT_DMA_ARRQ | OHCI_INT_DMA_ARRS
			| OHCI_INT_PHY_BUS_R);

/* FLUSH FIFO and reset Transmitter/Receiver */
	OWRITE(sc, OHCI_HCCCTL, OHCI_HCC_RESET);
#endif

/* XXX Link down?  Bus reset? */
	return 0;
}