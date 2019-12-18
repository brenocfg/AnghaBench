#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ata_macio_softc {int rev; int* udmaconf; int* wdmaconf; int* pioconf; int /*<<< orphan*/  max_mode; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int cycle; int active; } ;
struct TYPE_5__ {int cycle; int active; } ;
struct TYPE_4__ {int cycle; int active; } ;

/* Variables and functions */
 int ATA_DMA_MASK ; 
 int ATA_MODE_MASK ; 
 int ATA_PIO0 ; 
 int ATA_TIME_TO_TICK (int,int) ; 
 int ATA_UDMA0 ; 
 int ATA_WDMA0 ; 
 int DMA_REC_MIN ; 
 int DMA_REC_OFFSET ; 
 int PIO_ACT_MIN ; 
 int PIO_REC_MIN ; 
 int PIO_REC_OFFSET ; 
 struct ata_macio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_3__* dma_timings ; 
 int min (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* pio_timings ; 
 TYPE_1__* udma_timings ; 

__attribute__((used)) static int
ata_macio_setmode(device_t dev, int target, int mode)
{
	struct ata_macio_softc *sc = device_get_softc(dev);

	int min_cycle = 0, min_active = 0;
        int cycle_tick = 0, act_tick = 0, inact_tick = 0, half_tick;

	mode = min(mode, sc->max_mode);

	if ((mode & ATA_DMA_MASK) == ATA_UDMA0) {
		min_cycle = udma_timings[mode & ATA_MODE_MASK].cycle;
		min_active = udma_timings[mode & ATA_MODE_MASK].active;
	
		cycle_tick = ATA_TIME_TO_TICK(sc->rev,min_cycle);
		act_tick = ATA_TIME_TO_TICK(sc->rev,min_active);

		/* mask: 0x1ff00000 */
		sc->udmaconf[target] =
		    (cycle_tick << 21) | (act_tick << 25) | 0x100000;
	} else if ((mode & ATA_DMA_MASK) == ATA_WDMA0) {
		min_cycle = dma_timings[mode & ATA_MODE_MASK].cycle;
		min_active = dma_timings[mode & ATA_MODE_MASK].active;
	
		cycle_tick = ATA_TIME_TO_TICK(sc->rev,min_cycle);
		act_tick = ATA_TIME_TO_TICK(sc->rev,min_active);

		if (sc->rev == 4) {
			inact_tick = cycle_tick - act_tick;
			/* mask: 0x001ffc00 */
			sc->wdmaconf[target] = 
			    (act_tick << 10) | (inact_tick << 15);
		} else {
			inact_tick = cycle_tick - act_tick - DMA_REC_OFFSET;
			if (inact_tick < DMA_REC_MIN)
				inact_tick = DMA_REC_MIN;
			half_tick = 0;  /* XXX */

			/* mask: 0xfffff800 */
			sc->wdmaconf[target] = (half_tick << 21) 
			    | (inact_tick << 16) | (act_tick << 11);
		}
	} else {
		min_cycle = 
		    pio_timings[(mode & ATA_MODE_MASK) - ATA_PIO0].cycle;
		min_active = 
		    pio_timings[(mode & ATA_MODE_MASK) - ATA_PIO0].active;
	
		cycle_tick = ATA_TIME_TO_TICK(sc->rev,min_cycle);
		act_tick = ATA_TIME_TO_TICK(sc->rev,min_active);

		if (sc->rev == 4) {
			inact_tick = cycle_tick - act_tick;

			/* mask: 0x000003ff */
			sc->pioconf[target] =
			    (inact_tick << 5) | act_tick;
		} else {
			if (act_tick < PIO_ACT_MIN)
				act_tick = PIO_ACT_MIN;

			inact_tick = cycle_tick - act_tick - PIO_REC_OFFSET;
			if (inact_tick < PIO_REC_MIN)
				inact_tick = PIO_REC_MIN;

			/* mask: 0x000007ff */
			sc->pioconf[target] = 
			    (inact_tick << 5) | act_tick;
		}
	}

	return (mode);
}