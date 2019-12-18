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
struct TYPE_2__ {int fw_releasenum; int /*<<< orphan*/  regioncode; int /*<<< orphan*/  hwversion; } ;
struct malo_softc {int /*<<< orphan*/  malo_dev; TYPE_1__ malo_hwspecs; } ;

/* Variables and functions */
 scalar_t__ MALO_RXBUF ; 
 scalar_t__ MALO_TXBUF ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 scalar_t__ malo_rxbuf ; 
 scalar_t__ malo_txbuf ; 

__attribute__((used)) static void
malo_announce(struct malo_softc *sc)
{

	device_printf(sc->malo_dev,
		"versions [hw %d fw %d.%d.%d.%d] (regioncode %d)\n",
		sc->malo_hwspecs.hwversion,
		(sc->malo_hwspecs.fw_releasenum >> 24) & 0xff,
		(sc->malo_hwspecs.fw_releasenum >> 16) & 0xff,
		(sc->malo_hwspecs.fw_releasenum >> 8) & 0xff,
		(sc->malo_hwspecs.fw_releasenum >> 0) & 0xff,
		sc->malo_hwspecs.regioncode);

	if (bootverbose || malo_rxbuf != MALO_RXBUF)
		device_printf(sc->malo_dev,
		    "using %u rx buffers\n", malo_rxbuf);
	if (bootverbose || malo_txbuf != MALO_TXBUF)
		device_printf(sc->malo_dev,
		    "using %u tx buffers\n", malo_txbuf);
}