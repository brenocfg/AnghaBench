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
struct bwn_pci_softc {TYPE_1__* devcfg; } ;
struct bhndb_hw_priority {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct bhndb_hw_priority const* bridge_hwprio; } ;

/* Variables and functions */
 struct bwn_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct bhndb_hw_priority *
bwn_pci_get_bhndb_hwprio(device_t dev, device_t child)
{
	struct bwn_pci_softc *sc = device_get_softc(dev);
	return (sc->devcfg->bridge_hwprio);
}