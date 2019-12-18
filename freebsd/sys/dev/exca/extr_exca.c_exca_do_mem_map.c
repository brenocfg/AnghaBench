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
struct pccard_mem_handle {int kind; int cardaddr; int addr; int realsize; int size; } ;
struct mem_map_index_st {int memenable; int /*<<< orphan*/  sysmem_win; int /*<<< orphan*/  cardmem_lsb; int /*<<< orphan*/  cardmem_msb; int /*<<< orphan*/  sysmem_stop_lsb; int /*<<< orphan*/  sysmem_stop_msb; int /*<<< orphan*/  sysmem_start_lsb; int /*<<< orphan*/  sysmem_start_msb; } ;
struct exca_softc {struct pccard_mem_handle* mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPRINTF (char*,char*,int) ; 
 int /*<<< orphan*/  EXCA_ADDRWIN_ENABLE ; 
 int EXCA_ADDRWIN_ENABLE_MEMCS16 ; 
 int EXCA_CARDMEM_ADDRX_MSB_ADDR_MASK ; 
 int EXCA_CARDMEM_ADDRX_MSB_REGACTIVE_ATTR ; 
 int EXCA_CARDMEM_ADDRX_SHIFT ; 
 int EXCA_MEMREG_WIN_SHIFT ; 
 int EXCA_SYSMEM_ADDRX_SHIFT ; 
 int EXCA_SYSMEM_ADDRX_START_MSB_ADDR_MASK ; 
 int EXCA_SYSMEM_ADDRX_START_MSB_DATASIZE_16BIT ; 
 int EXCA_SYSMEM_ADDRX_STOP_MSB_ADDR_MASK ; 
 int EXCA_SYSMEM_ADDRX_STOP_MSB_WAIT2 ; 
 int PCCARD_MEM_16BIT ; 
 int PCCARD_MEM_ATTR ; 
 int exca_getb (struct exca_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_putb (struct exca_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exca_setb (struct exca_softc*,int /*<<< orphan*/ ,int) ; 
 struct mem_map_index_st* mem_map_index ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void
exca_do_mem_map(struct exca_softc *sc, int win)
{
	struct mem_map_index_st *map;
	struct pccard_mem_handle *mem;
	uint32_t offset;
	uint32_t mem16;
	uint32_t attrmem;
	
	map = &mem_map_index[win];
	mem = &sc->mem[win];
	mem16 = (mem->kind & PCCARD_MEM_16BIT) ? 
	    EXCA_SYSMEM_ADDRX_START_MSB_DATASIZE_16BIT : 0;
	attrmem = (mem->kind & PCCARD_MEM_ATTR) ?
	    EXCA_CARDMEM_ADDRX_MSB_REGACTIVE_ATTR : 0;
	offset = ((mem->cardaddr >> EXCA_CARDMEM_ADDRX_SHIFT) -
	  (mem->addr >> EXCA_SYSMEM_ADDRX_SHIFT)) & 0x3fff;
	exca_putb(sc, map->sysmem_start_lsb,
	    mem->addr >> EXCA_SYSMEM_ADDRX_SHIFT);
	exca_putb(sc, map->sysmem_start_msb,
	    ((mem->addr >> (EXCA_SYSMEM_ADDRX_SHIFT + 8)) &
	    EXCA_SYSMEM_ADDRX_START_MSB_ADDR_MASK) | mem16);

	exca_putb(sc, map->sysmem_stop_lsb,
	    (mem->addr + mem->realsize - 1) >> EXCA_SYSMEM_ADDRX_SHIFT);
	exca_putb(sc, map->sysmem_stop_msb,
	    (((mem->addr + mem->realsize - 1) >>
	    (EXCA_SYSMEM_ADDRX_SHIFT + 8)) &
	    EXCA_SYSMEM_ADDRX_STOP_MSB_ADDR_MASK) |
	    EXCA_SYSMEM_ADDRX_STOP_MSB_WAIT2);
	exca_putb(sc, map->sysmem_win, mem->addr >> EXCA_MEMREG_WIN_SHIFT);

	exca_putb(sc, map->cardmem_lsb, offset & 0xff);
	exca_putb(sc, map->cardmem_msb, ((offset >> 8) &
	    EXCA_CARDMEM_ADDRX_MSB_ADDR_MASK) | attrmem);

	DPRINTF("%s %d-bit memory",
	    mem->kind & PCCARD_MEM_ATTR ? "attribute" : "common",
	    mem->kind & PCCARD_MEM_16BIT ? 16 : 8);
	exca_setb(sc, EXCA_ADDRWIN_ENABLE, map->memenable |
	    EXCA_ADDRWIN_ENABLE_MEMCS16);

	DELAY(100);
#ifdef EXCA_DEBUG
	{
		int r1, r2, r3, r4, r5, r6, r7;
		r1 = exca_getb(sc, map->sysmem_start_msb);
		r2 = exca_getb(sc, map->sysmem_start_lsb);
		r3 = exca_getb(sc, map->sysmem_stop_msb);
		r4 = exca_getb(sc, map->sysmem_stop_lsb);
		r5 = exca_getb(sc, map->cardmem_msb);
		r6 = exca_getb(sc, map->cardmem_lsb);
		r7 = exca_getb(sc, map->sysmem_win);
		printf("exca_do_mem_map win %d: %#02x%#02x %#02x%#02x "
		    "%#02x%#02x %#02x (%#08x+%#06x.%#06x*%#06x) flags %#x\n",
		    win, r1, r2, r3, r4, r5, r6, r7,
		    mem->addr, mem->size, mem->realsize,
		    mem->cardaddr, mem->kind);
	}
#endif
}