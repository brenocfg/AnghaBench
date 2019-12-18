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
typedef  scalar_t__ uint32_t ;
struct fwohci_softc {int /*<<< orphan*/  intstat; } ;

/* Variables and functions */
 scalar_t__ atomic_readandclear_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwohci_intr_dma (struct fwohci_softc*,scalar_t__,int) ; 

__attribute__((used)) static void
fwohci_task_dma(void *arg, int pending)
{
	struct fwohci_softc *sc = (struct fwohci_softc *)arg;
	uint32_t stat;

again:
	stat = atomic_readandclear_int(&sc->intstat);
	if (stat)
		fwohci_intr_dma(sc, stat, -1);
	else
		return;
	goto again;
}