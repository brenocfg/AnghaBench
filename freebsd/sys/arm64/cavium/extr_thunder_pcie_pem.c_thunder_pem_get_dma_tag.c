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
struct thunder_pem_softc {int /*<<< orphan*/  dmat; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 struct thunder_pem_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bus_dma_tag_t
thunder_pem_get_dma_tag(device_t dev, device_t child)
{
	struct thunder_pem_softc *sc;

	sc = device_get_softc(dev);
	return (sc->dmat);
}