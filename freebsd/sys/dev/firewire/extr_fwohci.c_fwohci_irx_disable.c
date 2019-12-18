#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fwohci_softc {TYPE_2__* ir; } ;
struct firewire_comm {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  flag; } ;
struct TYPE_4__ {TYPE_1__ xferq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWXFERQ_RUNNING ; 
 int OHCI_CNTL_DMA_RUN ; 
 int /*<<< orphan*/  OHCI_IRCTLCLR (int) ; 
 int /*<<< orphan*/  OHCI_IR_MASKCLR ; 
 int /*<<< orphan*/  OHCI_IR_STATCLR ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fwohci_db_free (TYPE_2__*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fwohci_irx_disable(struct firewire_comm *fc, int dmach)
{
	struct fwohci_softc *sc = (struct fwohci_softc *)fc;

	OWRITE(sc, OHCI_IRCTLCLR(dmach), OHCI_CNTL_DMA_RUN);
	OWRITE(sc, OHCI_IR_MASKCLR, 1 << dmach);
	OWRITE(sc, OHCI_IR_STATCLR, 1 << dmach);
	/* XXX we cannot free buffers until the DMA really stops */
	pause("fwirxd", hz);
	fwohci_db_free(&sc->ir[dmach]);
	sc->ir[dmach].xferq.flag &= ~FWXFERQ_RUNNING;
	return 0;
}