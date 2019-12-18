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
struct dwmmc_softc {int bus_hz; int use_pio; int desc_count; int /*<<< orphan*/  hwtype; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HWTYPE_HISILICON ; 
 struct dwmmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int dwmmc_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hisi_dwmmc_attach(device_t dev)
{
	struct dwmmc_softc *sc;

	sc = device_get_softc(dev);
	sc->hwtype = HWTYPE_HISILICON;
	/* TODO: Calculate this from a clock driver */
	sc->bus_hz = 24000000; /* 24MHz */

	/*
	 * ARM64TODO: This is likely because we lack support for
	 * DMA when the controller is not cache-coherent on arm64.
	 */
	sc->use_pio = 1;
	sc->desc_count = 1;

	return (dwmmc_attach(dev));
}