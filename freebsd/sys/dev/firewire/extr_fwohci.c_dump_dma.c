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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct fwohci_softc {TYPE_1__ fc; } ;

/* Variables and functions */
 int IRX_CH ; 
 scalar_t__ ITX_CH ; 
 int OHCI_ARQOFF ; 
 int OHCI_ARSOFF ; 
 int OHCI_ATQOFF ; 
 int OHCI_ATSOFF ; 
 int OHCI_CNTL_DMA_ACTIVE ; 
 int OHCI_CNTL_DMA_BAD ; 
 int OHCI_CNTL_DMA_BT ; 
 int OHCI_CNTL_DMA_DEAD ; 
 int OHCI_CNTL_DMA_RUN ; 
 int OHCI_CNTL_DMA_WAKE ; 
 int OHCI_IRCTL (int) ; 
 int OHCI_ITCTL (scalar_t__) ; 
 int OREAD (struct fwohci_softc*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/ * fwohcicode ; 

void
dump_dma(struct fwohci_softc *sc, uint32_t ch)
{
	uint32_t off, cntl, stat, cmd, match;

	if (ch == 0) {
		off = OHCI_ATQOFF;
	} else if (ch == 1) {
		off = OHCI_ATSOFF;
	} else if (ch == 2) {
		off = OHCI_ARQOFF;
	} else if (ch == 3) {
		off = OHCI_ARSOFF;
	} else if (ch < IRX_CH) {
		off = OHCI_ITCTL(ch - ITX_CH);
	} else {
		off = OHCI_IRCTL(ch - IRX_CH);
	}
	cntl = stat = OREAD(sc, off);
	cmd = OREAD(sc, off + 0xc);
	match = OREAD(sc, off + 0x10);

	device_printf(sc->fc.dev, "ch %1x cntl:0x%08x cmd:0x%08x match:0x%08x\n",
		ch,
		cntl,
		cmd,
		match);
	stat &= 0xffff;
	if (stat) {
		device_printf(sc->fc.dev, "dma %d ch:%s%s%s%s%s%s %s(%x)\n",
			ch,
			stat & OHCI_CNTL_DMA_RUN ? "RUN," : "",
			stat & OHCI_CNTL_DMA_WAKE ? "WAKE," : "",
			stat & OHCI_CNTL_DMA_DEAD ? "DEAD," : "",
			stat & OHCI_CNTL_DMA_ACTIVE ? "ACTIVE," : "",
			stat & OHCI_CNTL_DMA_BT ? "BRANCH," : "",
			stat & OHCI_CNTL_DMA_BAD ? "BADDMA," : "",
			fwohcicode[stat & 0x1f],
			stat & 0x1f
		);
	} else {
		device_printf(sc->fc.dev, "dma %d ch: Nostat\n", ch);
	}
}