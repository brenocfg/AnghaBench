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
struct pccard_io_handle {int addr; int size; size_t width; } ;
struct io_map_index_st {int /*<<< orphan*/  stop_lsb; int /*<<< orphan*/  stop_msb; int /*<<< orphan*/  start_lsb; int /*<<< orphan*/  start_msb; int /*<<< orphan*/  ioenable; int /*<<< orphan*/ * ioctlbits; int /*<<< orphan*/  ioctlmask; } ;
struct exca_softc {struct pccard_io_handle* io; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  EXCA_ADDRWIN_ENABLE ; 
 int /*<<< orphan*/  EXCA_IOCTL ; 
 int /*<<< orphan*/  exca_clrb (struct exca_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int exca_getb (struct exca_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_putb (struct exca_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exca_setb (struct exca_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct io_map_index_st* io_map_index ; 

__attribute__((used)) static void
exca_do_io_map(struct exca_softc *sc, int win)
{
	struct io_map_index_st *map;

	struct pccard_io_handle *io;

	map = &io_map_index[win];
	io = &sc->io[win];
	exca_putb(sc, map->start_lsb, io->addr & 0xff);
	exca_putb(sc, map->start_msb, (io->addr >> 8) & 0xff);

	exca_putb(sc, map->stop_lsb, (io->addr + io->size - 1) & 0xff);
	exca_putb(sc, map->stop_msb, ((io->addr + io->size - 1) >> 8) & 0xff);

	exca_clrb(sc, EXCA_IOCTL, map->ioctlmask);
	exca_setb(sc, EXCA_IOCTL, map->ioctlbits[io->width]);

	exca_setb(sc, EXCA_ADDRWIN_ENABLE, map->ioenable);
#ifdef EXCA_DEBUG
	{
		int r1, r2, r3, r4;
		r1 = exca_getb(sc, map->start_msb);
		r2 = exca_getb(sc, map->start_lsb);
		r3 = exca_getb(sc, map->stop_msb);
		r4 = exca_getb(sc, map->stop_lsb);
		DPRINTF("exca_do_io_map window %d: %02x%02x %02x%02x "
		    "(%08x+%08x)\n", win, r1, r2, r3, r4,
		    io->addr, io->size);
	}
#endif
}