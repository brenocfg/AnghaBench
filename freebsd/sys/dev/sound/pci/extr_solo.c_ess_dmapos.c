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
struct ess_info {int* dmasz; int /*<<< orphan*/  io; int /*<<< orphan*/  vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  ess_dmatrigger (struct ess_info*,int,int) ; 
 int port_rd (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static int
ess_dmapos(struct ess_info *sc, int ch)
{
	int p = 0, i = 0, j = 0;

	KASSERT(ch == 1 || ch == 2, ("bad ch"));
	if (ch == 1) {

/*
 * During recording, this register is known to give back
 * garbage if it's not quiescent while being read. That's
 * why we spl, stop the DMA, and try over and over until
 * adjacent reads are "close", in the right order and not
 * bigger than is otherwise possible.
 */
		ess_dmatrigger(sc, ch, 0);
		DELAY(20);
		do {
			DELAY(10);
			if (j > 1)
				printf("DMA count reg bogus: %04x & %04x\n",
					i, p);
			i = port_rd(sc->vc, 0x4, 2) + 1;
			p = port_rd(sc->vc, 0x4, 2) + 1;
		} while ((p > sc->dmasz[ch - 1] || i < p || (p - i) > 0x8) && j++ < 1000);
		ess_dmatrigger(sc, ch, 1);
	}
	else if (ch == 2)
		p = port_rd(sc->io, 0x4, 2);
	return sc->dmasz[ch - 1] - p;
}