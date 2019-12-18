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
struct aw_ccung_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCU_WRITE4 (struct aw_ccung_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aw_ccung_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_ccung_write_4(device_t dev, bus_addr_t addr, uint32_t val)
{
	struct aw_ccung_softc *sc;

	sc = device_get_softc(dev);
	dprintf("offset=%lx write %x\n", addr, val);
	CCU_WRITE4(sc, addr, val);
	return (0);
}