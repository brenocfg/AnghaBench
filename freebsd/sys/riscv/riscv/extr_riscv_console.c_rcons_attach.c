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
struct rcons_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SIE_SSIE ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rcons_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sie ; 

__attribute__((used)) static int
rcons_attach(device_t dev)
{
	struct rcons_softc *sc;

	if (device_get_unit(dev) != 0)
		return (ENXIO);

	sc = device_get_softc(dev);
	sc->dev = dev;

	csr_set(sie, SIE_SSIE);

	bus_generic_attach(sc->dev);

	return (0);
}