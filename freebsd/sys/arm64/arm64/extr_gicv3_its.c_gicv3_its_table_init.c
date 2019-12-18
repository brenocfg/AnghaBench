#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int uint64_t ;
struct gicv3_its_softc {int sc_its_flags; TYPE_1__* sc_its_ptab; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {size_t ptab_size; scalar_t__ ptab_vaddr; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GITS_BASER (int) ; 
 int GITS_BASER_CACHE_MASK ; 
 int GITS_BASER_CACHE_SHIFT ; 
 int GITS_BASER_CACHE_WAWB ; 
 size_t GITS_BASER_ESIZE (int) ; 
 int GITS_BASER_ESIZE_MASK ; 
 size_t GITS_BASER_ESIZE_SHIFT ; 
 int GITS_BASER_NUM ; 
 int GITS_BASER_PA_MASK ; 
 int GITS_BASER_PSZ_16K ; 
 int GITS_BASER_PSZ_4K ; 
 int GITS_BASER_PSZ_64K ; 
 int GITS_BASER_PSZ_MASK ; 
 int GITS_BASER_PSZ_SHIFT ; 
 int GITS_BASER_SHARE_IS ; 
 int GITS_BASER_SHARE_MASK ; 
 int GITS_BASER_SHARE_SHIFT ; 
 int GITS_BASER_SIZE_MASK ; 
 int GITS_BASER_TYPE (int) ; 
#define  GITS_BASER_TYPE_DEV 134 
#define  GITS_BASER_TYPE_IC 133 
 int GITS_BASER_TYPE_MASK ; 
#define  GITS_BASER_TYPE_PP 132 
 int GITS_BASER_TYPE_SHIFT ; 
#define  GITS_BASER_TYPE_VP 131 
 int GITS_BASER_VALID ; 
 int /*<<< orphan*/  GITS_TYPER ; 
 int GITS_TYPER_DEVB (int) ; 
 int ITS_FLAGS_ERRATA_CAVIUM_22375 ; 
 int /*<<< orphan*/  M_GICV3_ITS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
#define  PAGE_SIZE 130 
#define  PAGE_SIZE_16K 129 
#define  PAGE_SIZE_64K 128 
 scalar_t__ contigmalloc (size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int gic_its_read_8 (struct gicv3_its_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_its_write_8 (struct gicv3_its_softc*,int /*<<< orphan*/ ,int) ; 
 size_t howmany (size_t,int) ; 
 size_t roundup2 (size_t,int) ; 
 int vtophys (scalar_t__) ; 

__attribute__((used)) static int
gicv3_its_table_init(device_t dev, struct gicv3_its_softc *sc)
{
	vm_offset_t table;
	vm_paddr_t paddr;
	uint64_t cache, reg, share, tmp, type;
	size_t esize, its_tbl_size, nidents, nitspages, npages;
	int i, page_size;
	int devbits;

	if ((sc->sc_its_flags & ITS_FLAGS_ERRATA_CAVIUM_22375) != 0) {
		/*
		 * GITS_TYPER[17:13] of ThunderX reports that device IDs
		 * are to be 21 bits in length. The entry size of the ITS
		 * table can be read from GITS_BASERn[52:48] and on ThunderX
		 * is supposed to be 8 bytes in length (for device table).
		 * Finally the page size that is to be used by ITS to access
		 * this table will be set to 64KB.
		 *
		 * This gives 0x200000 entries of size 0x8 bytes covered by
		 * 256 pages each of which 64KB in size. The number of pages
		 * (minus 1) should then be written to GITS_BASERn[7:0]. In
		 * that case this value would be 0xFF but on ThunderX the
		 * maximum value that HW accepts is 0xFD.
		 *
		 * Set an arbitrary number of device ID bits to 20 in order
		 * to limit the number of entries in ITS device table to
		 * 0x100000 and the table size to 8MB.
		 */
		devbits = 20;
		cache = 0;
	} else {
		devbits = GITS_TYPER_DEVB(gic_its_read_8(sc, GITS_TYPER));
		cache = GITS_BASER_CACHE_WAWB;
	}
	share = GITS_BASER_SHARE_IS;
	page_size = PAGE_SIZE_64K;

	for (i = 0; i < GITS_BASER_NUM; i++) {
		reg = gic_its_read_8(sc, GITS_BASER(i));
		/* The type of table */
		type = GITS_BASER_TYPE(reg);
		/* The table entry size */
		esize = GITS_BASER_ESIZE(reg);

		switch(type) {
		case GITS_BASER_TYPE_DEV:
			nidents = (1 << devbits);
			its_tbl_size = esize * nidents;
			its_tbl_size = roundup2(its_tbl_size, PAGE_SIZE_64K);
			break;
		case GITS_BASER_TYPE_VP:
		case GITS_BASER_TYPE_PP: /* Undocumented? */
		case GITS_BASER_TYPE_IC:
			its_tbl_size = page_size;
			break;
		default:
			continue;
		}
		npages = howmany(its_tbl_size, PAGE_SIZE);

		/* Allocate the table */
		table = (vm_offset_t)contigmalloc(npages * PAGE_SIZE,
		    M_GICV3_ITS, M_WAITOK | M_ZERO, 0, (1ul << 48) - 1,
		    PAGE_SIZE_64K, 0);

		sc->sc_its_ptab[i].ptab_vaddr = table;
		sc->sc_its_ptab[i].ptab_size = npages * PAGE_SIZE;

		paddr = vtophys(table);

		while (1) {
			nitspages = howmany(its_tbl_size, page_size);

			/* Clear the fields we will be setting */
			reg &= ~(GITS_BASER_VALID |
			    GITS_BASER_CACHE_MASK | GITS_BASER_TYPE_MASK |
			    GITS_BASER_ESIZE_MASK | GITS_BASER_PA_MASK |
			    GITS_BASER_SHARE_MASK | GITS_BASER_PSZ_MASK |
			    GITS_BASER_SIZE_MASK);
			/* Set the new values */
			reg |= GITS_BASER_VALID |
			    (cache << GITS_BASER_CACHE_SHIFT) |
			    (type << GITS_BASER_TYPE_SHIFT) |
			    ((esize - 1) << GITS_BASER_ESIZE_SHIFT) |
			    paddr | (share << GITS_BASER_SHARE_SHIFT) |
			    (nitspages - 1);

			switch (page_size) {
			case PAGE_SIZE:		/* 4KB */
				reg |=
				    GITS_BASER_PSZ_4K << GITS_BASER_PSZ_SHIFT;
				break;
			case PAGE_SIZE_16K:	/* 16KB */
				reg |=
				    GITS_BASER_PSZ_16K << GITS_BASER_PSZ_SHIFT;
				break;
			case PAGE_SIZE_64K:	/* 64KB */
				reg |=
				    GITS_BASER_PSZ_64K << GITS_BASER_PSZ_SHIFT;
				break;
			}

			gic_its_write_8(sc, GITS_BASER(i), reg);

			/* Read back to check */
			tmp = gic_its_read_8(sc, GITS_BASER(i));

			/* Do the shareability masks line up? */
			if ((tmp & GITS_BASER_SHARE_MASK) !=
			    (reg & GITS_BASER_SHARE_MASK)) {
				share = (tmp & GITS_BASER_SHARE_MASK) >>
				    GITS_BASER_SHARE_SHIFT;
				continue;
			}

			if ((tmp & GITS_BASER_PSZ_MASK) !=
			    (reg & GITS_BASER_PSZ_MASK)) {
				switch (page_size) {
				case PAGE_SIZE_16K:
					page_size = PAGE_SIZE;
					continue;
				case PAGE_SIZE_64K:
					page_size = PAGE_SIZE_16K;
					continue;
				}
			}

			if (tmp != reg) {
				device_printf(dev, "GITS_BASER%d: "
				    "unable to be updated: %lx != %lx\n",
				    i, reg, tmp);
				return (ENXIO);
			}

			/* We should have made all needed changes */
			break;
		}
	}

	return (0);
}