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
struct ata_kauai_softc {int /*<<< orphan*/ * pioconf; int /*<<< orphan*/ * wdmaconf; int /*<<< orphan*/ * udmaconf; scalar_t__ shasta; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_DMA_MASK ; 
 int ATA_MODE_MASK ; 
 int /*<<< orphan*/  ATA_PIO0 ; 
#define  ATA_UDMA0 129 
 int /*<<< orphan*/  ATA_UDMA5 ; 
 int /*<<< orphan*/  ATA_UDMA6 ; 
#define  ATA_WDMA0 128 
 struct ata_kauai_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_timing_kauai ; 
 int /*<<< orphan*/ * dma_timing_shasta ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pio_timing_kauai ; 
 int /*<<< orphan*/ * pio_timing_shasta ; 
 int /*<<< orphan*/ * udma_timing_kauai ; 
 int /*<<< orphan*/ * udma_timing_shasta ; 

__attribute__((used)) static int
ata_kauai_setmode(device_t dev, int target, int mode)
{
	struct ata_kauai_softc *sc = device_get_softc(dev);

	mode = min(mode,sc->shasta ? ATA_UDMA6 : ATA_UDMA5);

	if (sc->shasta) {
		switch (mode & ATA_DMA_MASK) {
		    case ATA_UDMA0:
			sc->udmaconf[target] 
			    = udma_timing_shasta[mode & ATA_MODE_MASK];
			break;
		    case ATA_WDMA0:
			sc->udmaconf[target] = 0;
			sc->wdmaconf[target] 
			    = dma_timing_shasta[mode & ATA_MODE_MASK];
			break;
		    default:
			sc->pioconf[target] 
			    = pio_timing_shasta[(mode & ATA_MODE_MASK) - 
			    ATA_PIO0];
			break;
		}
	} else {
		switch (mode & ATA_DMA_MASK) {
		    case ATA_UDMA0:
			sc->udmaconf[target] 
			    = udma_timing_kauai[mode & ATA_MODE_MASK];
			break;
		    case ATA_WDMA0:
			sc->udmaconf[target] = 0;
			sc->wdmaconf[target]
			    = dma_timing_kauai[mode & ATA_MODE_MASK];
			break;
		    default:
			sc->pioconf[target] 
			    = pio_timing_kauai[(mode & ATA_MODE_MASK)
			    - ATA_PIO0];
			break;
		}
	}

	return (mode);
}