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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct atse_softc {int /*<<< orphan*/  atse_mem_res; } ;
typedef  int bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,char const*,int const,char const*,char*,int,int,int) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int,int) ; 
 int htole32 (int) ; 

__attribute__((used)) static inline void
pxx_write_2(struct atse_softc *sc, bus_addr_t bmcr, uint32_t reg, uint16_t val,
    const char *f, const int l, const char *s)
{
	uint32_t val4;

	val4 = htole32(val & 0x0000ffff);
	DPRINTF("[%s:%d] %s W %s 0x%08x (0x%08jx) = 0x%08x\n", f, l, s,
	    "atse_mem_res", reg, (bmcr + reg) * 4, val4);
	bus_write_4(sc->atse_mem_res, (bmcr + reg) * 4, val4);
}