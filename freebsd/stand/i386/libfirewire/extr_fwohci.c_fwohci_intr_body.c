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
struct fwohci_softc {scalar_t__ state; int /*<<< orphan*/ * config_rom; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWOHCI_INTMASK ; 
 int /*<<< orphan*/  FWOHCI_INTMASKCLR ; 
 scalar_t__ FWOHCI_STATE_BUSRESET ; 
 int /*<<< orphan*/  OHCI_BUS_OPT ; 
 int OHCI_CNTL_CYCSRC ; 
 int /*<<< orphan*/  OHCI_CROMHDR ; 
 int OHCI_INT_CYC_64SECOND ; 
 int OHCI_INT_CYC_ERR ; 
 int OHCI_INT_CYC_LONG ; 
 int OHCI_INT_CYC_LOST ; 
 int OHCI_INT_CYC_START ; 
 int OHCI_INT_DMA_ARRQ ; 
 int OHCI_INT_DMA_ARRS ; 
 int OHCI_INT_DMA_ATRQ ; 
 int OHCI_INT_DMA_ATRS ; 
 int OHCI_INT_DMA_IR ; 
 int OHCI_INT_DMA_IT ; 
 int OHCI_INT_DMA_PRRQ ; 
 int OHCI_INT_DMA_PRRS ; 
 int OHCI_INT_EN ; 
 int OHCI_INT_ERR ; 
 int OHCI_INT_LR_ERR ; 
 int OHCI_INT_PHY_BUS_R ; 
 int OHCI_INT_PHY_INT ; 
 int OHCI_INT_PHY_REG ; 
 int OHCI_INT_PHY_SID ; 
 int OHCI_INT_PW_ERR ; 
 int /*<<< orphan*/  OHCI_LNKCTLCLR ; 
 int OREAD (struct fwohci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* fc ; 
 int /*<<< orphan*/  fwohci_sid (struct fwohci_softc*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fwohci_intr_body(struct fwohci_softc *sc, uint32_t stat, int count)
{
#undef OHCI_DEBUG
#ifdef OHCI_DEBUG
#if 0
	if(stat & OREAD(sc, FWOHCI_INTMASK))
#else
	if (1)
#endif
		device_printf(fc->dev, "INTERRUPT < %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s> 0x%08x, 0x%08x\n",
			stat & OHCI_INT_EN ? "DMA_EN ":"",
			stat & OHCI_INT_PHY_REG ? "PHY_REG ":"",
			stat & OHCI_INT_CYC_LONG ? "CYC_LONG ":"",
			stat & OHCI_INT_ERR ? "INT_ERR ":"",
			stat & OHCI_INT_CYC_ERR ? "CYC_ERR ":"",
			stat & OHCI_INT_CYC_LOST ? "CYC_LOST ":"",
			stat & OHCI_INT_CYC_64SECOND ? "CYC_64SECOND ":"",
			stat & OHCI_INT_CYC_START ? "CYC_START ":"",
			stat & OHCI_INT_PHY_INT ? "PHY_INT ":"",
			stat & OHCI_INT_PHY_BUS_R ? "BUS_RESET ":"",
			stat & OHCI_INT_PHY_SID ? "SID ":"",
			stat & OHCI_INT_LR_ERR ? "DMA_LR_ERR ":"",
			stat & OHCI_INT_PW_ERR ? "DMA_PW_ERR ":"",
			stat & OHCI_INT_DMA_IR ? "DMA_IR ":"",
			stat & OHCI_INT_DMA_IT  ? "DMA_IT " :"",
			stat & OHCI_INT_DMA_PRRS  ? "DMA_PRRS " :"",
			stat & OHCI_INT_DMA_PRRQ  ? "DMA_PRRQ " :"",
			stat & OHCI_INT_DMA_ARRS  ? "DMA_ARRS " :"",
			stat & OHCI_INT_DMA_ARRQ  ? "DMA_ARRQ " :"",
			stat & OHCI_INT_DMA_ATRS  ? "DMA_ATRS " :"",
			stat & OHCI_INT_DMA_ATRQ  ? "DMA_ATRQ " :"",
			stat, OREAD(sc, FWOHCI_INTMASK) 
		);
#endif
/* Bus reset */
	if(stat & OHCI_INT_PHY_BUS_R ){
		device_printf(fc->dev, "BUS reset\n");
		if (sc->state == FWOHCI_STATE_BUSRESET)
			goto busresetout;
		sc->state = FWOHCI_STATE_BUSRESET;
		/* Disable bus reset interrupt until sid recv. */
		OWRITE(sc, FWOHCI_INTMASKCLR,  OHCI_INT_PHY_BUS_R);
	
		OWRITE(sc, FWOHCI_INTMASKCLR,  OHCI_INT_CYC_LOST);
		OWRITE(sc, OHCI_LNKCTLCLR, OHCI_CNTL_CYCSRC);

		OWRITE(sc, OHCI_CROMHDR, ntohl(sc->config_rom[0]));
		OWRITE(sc, OHCI_BUS_OPT, ntohl(sc->config_rom[2]));
	} else if (sc->state == FWOHCI_STATE_BUSRESET) {
		fwohci_sid(sc);
	}
busresetout:
	return;
}