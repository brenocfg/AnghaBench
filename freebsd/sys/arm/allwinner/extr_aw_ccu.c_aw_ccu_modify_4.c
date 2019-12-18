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
struct aw_ccu_softc {int /*<<< orphan*/  bst; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ aw_ccu_check_addr (struct aw_ccu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aw_ccu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_ccu_modify_4(device_t dev, bus_addr_t addr, uint32_t clr, uint32_t set)
{
	struct aw_ccu_softc *sc;
	bus_space_handle_t bsh;
	bus_size_t reg;
	uint32_t val;

	sc = device_get_softc(dev);

	if (aw_ccu_check_addr(sc, addr, &bsh, &reg) != 0)
		return (EINVAL);

	mtx_assert(&sc->mtx, MA_OWNED);
	val = bus_space_read_4(sc->bst, bsh, reg);
	val &= ~clr;
	val |= set;
	bus_space_write_4(sc->bst, bsh, reg, val);

	return (0);
}