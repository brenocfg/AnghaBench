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
struct mv_pcib_softc {int sc_io_base; int sc_io_size; int sc_mem_base; int sc_mem_size; int /*<<< orphan*/  sc_dev; } ;
typedef  int bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_IOBASEH_1 ; 
 int /*<<< orphan*/  PCIR_IOBASEL_1 ; 
 int /*<<< orphan*/  PCIR_IOLIMITH_1 ; 
 int /*<<< orphan*/  PCIR_IOLIMITL_1 ; 
 int /*<<< orphan*/  PCIR_MEMBASE_1 ; 
 int /*<<< orphan*/  PCIR_MEMLIMIT_1 ; 
 int /*<<< orphan*/  PCIR_PMBASEH_1 ; 
 int /*<<< orphan*/  PCIR_PMBASEL_1 ; 
 int /*<<< orphan*/  PCIR_PMLIMITH_1 ; 
 int /*<<< orphan*/  PCIR_PMLIMITL_1 ; 
 int /*<<< orphan*/  PCIR_SECBUS_1 ; 
 int /*<<< orphan*/  PCI_SLOTMAX ; 
 int /*<<< orphan*/  mv_pcib_init (struct mv_pcib_softc*,int,int /*<<< orphan*/ ) ; 
 int mv_pcib_read_config (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_pcib_write_config (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
mv_pcib_init_bridge(struct mv_pcib_softc *sc, int bus, int slot, int func)
{
	bus_addr_t io_base, mem_base;
	uint32_t io_limit, mem_limit;
	int secbus;

	io_base = sc->sc_io_base;
	io_limit = io_base + sc->sc_io_size - 1;
	mem_base = sc->sc_mem_base;
	mem_limit = mem_base + sc->sc_mem_size - 1;

	/* Configure I/O decode registers */
	mv_pcib_write_config(sc->sc_dev, bus, slot, func, PCIR_IOBASEL_1,
	    io_base >> 8, 1);
	mv_pcib_write_config(sc->sc_dev, bus, slot, func, PCIR_IOBASEH_1,
	    io_base >> 16, 2);
	mv_pcib_write_config(sc->sc_dev, bus, slot, func, PCIR_IOLIMITL_1,
	    io_limit >> 8, 1);
	mv_pcib_write_config(sc->sc_dev, bus, slot, func, PCIR_IOLIMITH_1,
	    io_limit >> 16, 2);

	/* Configure memory decode registers */
	mv_pcib_write_config(sc->sc_dev, bus, slot, func, PCIR_MEMBASE_1,
	    mem_base >> 16, 2);
	mv_pcib_write_config(sc->sc_dev, bus, slot, func, PCIR_MEMLIMIT_1,
	    mem_limit >> 16, 2);

	/* Disable memory prefetch decode */
	mv_pcib_write_config(sc->sc_dev, bus, slot, func, PCIR_PMBASEL_1,
	    0x10, 2);
	mv_pcib_write_config(sc->sc_dev, bus, slot, func, PCIR_PMBASEH_1,
	    0x0, 4);
	mv_pcib_write_config(sc->sc_dev, bus, slot, func, PCIR_PMLIMITL_1,
	    0xF, 2);
	mv_pcib_write_config(sc->sc_dev, bus, slot, func, PCIR_PMLIMITH_1,
	    0x0, 4);

	secbus = mv_pcib_read_config(sc->sc_dev, bus, slot, func,
	    PCIR_SECBUS_1, 1);

	/* Configure buses behind the bridge */
	mv_pcib_init(sc, secbus, PCI_SLOTMAX);
}