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
struct jz4780_clock_softc {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGU_LOCK_DESTROY (struct jz4780_clock_softc*) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jz4780_clock_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_clock_spec ; 

__attribute__((used)) static int
jz4780_clock_detach(device_t dev)
{
	struct jz4780_clock_softc *sc;

	sc = device_get_softc(dev);
	bus_release_resources(dev, jz4780_clock_spec, sc->res);
	CGU_LOCK_DESTROY(sc);

	return (0);
}