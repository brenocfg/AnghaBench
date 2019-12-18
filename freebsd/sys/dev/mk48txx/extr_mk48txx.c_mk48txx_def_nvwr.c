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
typedef  int /*<<< orphan*/  uint8_t ;
struct mk48txx_softc {int /*<<< orphan*/  sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mk48txx_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mk48txx_def_nvwr(device_t dev, int off, uint8_t v)
{
	struct mk48txx_softc *sc;

	sc = device_get_softc(dev);
	bus_write_1(sc->sc_res, off, v);
}