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
struct ipw_softc {int dummy; } ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_1 (struct ipw_softc*,scalar_t__,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ipw_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IPW_CSR_INDIRECT_ADDR ; 
 scalar_t__ IPW_CSR_INDIRECT_DATA ; 

__attribute__((used)) static void
ipw_write_mem_1(struct ipw_softc *sc, bus_size_t offset, const uint8_t *datap,
    bus_size_t count)
{
	for (; count > 0; offset++, datap++, count--) {
		CSR_WRITE_4(sc, IPW_CSR_INDIRECT_ADDR, offset & ~3);
		CSR_WRITE_1(sc, IPW_CSR_INDIRECT_DATA + (offset & 3), *datap);
	}
}