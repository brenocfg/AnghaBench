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
 int /*<<< orphan*/  bus_read_1 (int /*<<< orphan*/ ,int) ; 
 struct mk48txx_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
mk48txx_def_nvrd(device_t dev, int off)
{
	struct mk48txx_softc *sc;

	sc = device_get_softc(dev);
	return (bus_read_1(sc->sc_res, off));
}