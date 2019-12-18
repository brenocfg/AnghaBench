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
struct edma_softc {int dummy; } ;
struct edma_channel {int enabled; int /*<<< orphan*/  ih_user; int /*<<< orphan*/  (* ih ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CINT_CAIR ; 
 int /*<<< orphan*/  DMA_CINT ; 
 int /*<<< orphan*/  DMA_INT ; 
 int EDMA_NUM_CHANNELS ; 
 int READ4 (struct edma_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE1 (struct edma_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct edma_channel* edma_map ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
edma_transfer_complete_intr(void *arg)
{
	struct edma_channel *ch;
	struct edma_softc *sc;
	int interrupts;
	int i;

	sc = arg;

	interrupts = READ4(sc, DMA_INT);
	WRITE1(sc, DMA_CINT, CINT_CAIR);

	for (i = 0; i < EDMA_NUM_CHANNELS; i++) {
		if (interrupts & (0x1 << i)) {
			ch = &edma_map[i];
			if (ch->enabled == 1) {
				if (ch->ih != NULL) {
					ch->ih(ch->ih_user, i);
				}
			}
		}
	}
}