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
typedef  int /*<<< orphan*/  uint16_t ;
struct fxp_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int FXP_CB_STATUS_C ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int le16toh (int /*<<< orphan*/  volatile) ; 

__attribute__((used)) static void
fxp_dma_wait(struct fxp_softc *sc, volatile uint16_t *status,
    bus_dma_tag_t dmat, bus_dmamap_t map)
{
	int i;

	for (i = 10000; i > 0; i--) {
		DELAY(2);
		bus_dmamap_sync(dmat, map,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
		if ((le16toh(*status) & FXP_CB_STATUS_C) != 0)
			break;
	}
	if (i == 0)
		device_printf(sc->dev, "DMA timeout\n");
}