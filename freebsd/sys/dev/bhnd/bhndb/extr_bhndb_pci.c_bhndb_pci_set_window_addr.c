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
struct bhndb_regwin {int dummy; } ;
struct bhndb_pci_softc {int (* set_regwin ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhndb_regwin const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  parent; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_addr_t ;

/* Variables and functions */
 struct bhndb_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhndb_regwin const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhndb_pci_set_window_addr(device_t dev, const struct bhndb_regwin *rw,
    bhnd_addr_t addr)
{
	struct bhndb_pci_softc *sc = device_get_softc(dev);
	return (sc->set_regwin(sc->dev, sc->parent, rw, addr));
}