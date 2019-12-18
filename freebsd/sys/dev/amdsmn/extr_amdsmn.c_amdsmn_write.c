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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdsmn_softc {int /*<<< orphan*/  smn_lock; TYPE_1__* smn_pciid; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  amdsmn_data_reg; int /*<<< orphan*/  amdsmn_addr_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct amdsmn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
amdsmn_write(device_t dev, uint32_t addr, uint32_t value)
{
	struct amdsmn_softc *sc = device_get_softc(dev);
	device_t parent;

	parent = device_get_parent(dev);

	mtx_lock(&sc->smn_lock);
	pci_write_config(parent, sc->smn_pciid->amdsmn_addr_reg, addr, 4);
	pci_write_config(parent, sc->smn_pciid->amdsmn_data_reg, value, 4);
	mtx_unlock(&sc->smn_lock);

	return (0);
}