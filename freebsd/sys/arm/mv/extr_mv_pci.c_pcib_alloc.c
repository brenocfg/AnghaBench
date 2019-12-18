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
struct mv_pcib_softc {int sc_io_size; int* sc_io_map; int sc_mem_size; int* sc_mem_map; scalar_t__ sc_mem_base; scalar_t__ sc_io_base; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int PCI_MIN_IO_ALLOC ; 
 int PCI_MIN_MEM_ALLOC ; 
 scalar_t__ pcib_map_check (int*,int,int) ; 
 int /*<<< orphan*/  pcib_map_set (int*,int,int) ; 

__attribute__((used)) static bus_addr_t
pcib_alloc(struct mv_pcib_softc *sc, uint32_t smask)
{
	uint32_t bits, bits_limit, i, *map, min_alloc, size;
	bus_addr_t addr = 0;
	bus_addr_t base;

	if (smask & 1) {
		base = sc->sc_io_base;
		min_alloc = PCI_MIN_IO_ALLOC;
		bits_limit = sc->sc_io_size / min_alloc;
		map = sc->sc_io_map;
		smask &= ~0x3;
	} else {
		base = sc->sc_mem_base;
		min_alloc = PCI_MIN_MEM_ALLOC;
		bits_limit = sc->sc_mem_size / min_alloc;
		map = sc->sc_mem_map;
		smask &= ~0xF;
	}

	size = ~smask + 1;
	bits = size / min_alloc;

	for (i = 0; i + bits <= bits_limit; i += bits)
		if (pcib_map_check(map, i, bits)) {
			pcib_map_set(map, i, bits);
			addr = base + (i * min_alloc);
			return (addr);
		}

	return (addr);
}