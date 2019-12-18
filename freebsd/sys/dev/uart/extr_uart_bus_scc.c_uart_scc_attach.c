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
struct uart_softc {struct mtx* sc_hwmtx; } ;
struct mtx {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  SCC_IVAR_HWMTX ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int uart_bus_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_scc_attach(device_t dev)
{
	device_t parent;
	struct uart_softc *sc;
	uintptr_t mtx;

	parent = device_get_parent(dev);
	sc = device_get_softc(dev);

	if (BUS_READ_IVAR(parent, dev, SCC_IVAR_HWMTX, &mtx))
		return (ENXIO);
	sc->sc_hwmtx = (struct mtx *)(void *)mtx;
	return (uart_bus_attach(dev));
}