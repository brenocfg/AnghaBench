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
typedef  int uint64_t ;
struct vtpci_softc {int vtpci_features; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct vtpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtpci_with_feature(device_t dev, uint64_t feature)
{
	struct vtpci_softc *sc;

	sc = device_get_softc(dev);

	return ((sc->vtpci_features & feature) != 0);
}