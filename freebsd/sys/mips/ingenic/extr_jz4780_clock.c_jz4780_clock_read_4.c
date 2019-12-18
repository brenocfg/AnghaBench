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
typedef  int /*<<< orphan*/  uint32_t ;
struct jz4780_clock_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_4 (struct jz4780_clock_softc*,int /*<<< orphan*/ ) ; 
 struct jz4780_clock_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_clock_read_4(device_t dev, bus_addr_t addr, uint32_t *val)
{
	struct jz4780_clock_softc *sc;

	sc = device_get_softc(dev);
	*val = CSR_READ_4(sc, addr);
	return (0);
}