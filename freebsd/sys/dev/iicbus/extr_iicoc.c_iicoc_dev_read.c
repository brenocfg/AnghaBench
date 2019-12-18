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
typedef  int uint8_t ;
struct iicoc_softc {int reg_shift; int /*<<< orphan*/  mem_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_read_1 (int /*<<< orphan*/ ,int) ; 
 struct iicoc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
iicoc_dev_read(device_t dev, int reg)
{
	uint8_t val;
	struct iicoc_softc *sc;

	sc = device_get_softc(dev);
	val = bus_read_1(sc->mem_res, reg<<sc->reg_shift);
	return (val);
}