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
struct aw_ccu_softc {int /*<<< orphan*/  bsh; } ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  scalar_t__ bus_size_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 scalar_t__ CCU_BASE ; 
 scalar_t__ CCU_SIZE ; 
 int EINVAL ; 

__attribute__((used)) static int
aw_ccu_check_addr(struct aw_ccu_softc *sc, bus_addr_t addr,
    bus_space_handle_t *pbsh, bus_size_t *poff)
{
	if (addr >= CCU_BASE && addr < (CCU_BASE + CCU_SIZE)) {
		*poff = addr - CCU_BASE;
		*pbsh = sc->bsh;
		return (0);
	}
	return (EINVAL);
}