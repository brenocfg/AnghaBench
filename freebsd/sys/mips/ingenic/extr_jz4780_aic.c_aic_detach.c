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
struct aic_softc {int /*<<< orphan*/  res; int /*<<< orphan*/  xchan; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  aic_spec ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdma_channel_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aic_detach(device_t dev)
{
	struct aic_softc *sc;

	sc = device_get_softc(dev);

	xdma_channel_free(sc->xchan);

	bus_release_resources(dev, aic_spec, sc->res);

	return (0);
}