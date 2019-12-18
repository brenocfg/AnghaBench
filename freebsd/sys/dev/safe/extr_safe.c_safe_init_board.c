#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_6__ {int dma_paddr; } ;
struct TYPE_5__ {int dma_paddr; } ;
struct TYPE_4__ {int dma_paddr; } ;
struct safe_softc {scalar_t__ sc_chiprev; TYPE_3__ sc_dpalloc; TYPE_2__ sc_spalloc; TYPE_1__ sc_ringalloc; int /*<<< orphan*/  sc_dev; } ;
struct safe_ringentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int READ_REG (struct safe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_DMA_CFG ; 
 int /*<<< orphan*/  SAFE_ENDIAN ; 
 int /*<<< orphan*/  SAFE_HI_CFG ; 
 int SAFE_HI_CFG_LEVEL ; 
 int /*<<< orphan*/  SAFE_HI_DESC_CNT ; 
 int /*<<< orphan*/  SAFE_HI_MASK ; 
 int SAFE_INT_PE_DDONE ; 
 int SAFE_INT_PE_ERROR ; 
 int SAFE_MAX_DSIZE ; 
 int SAFE_MAX_NQUEUE ; 
 int /*<<< orphan*/  SAFE_PE_DMACFG ; 
 int SAFE_PE_DMACFG_ESDESC ; 
 int SAFE_PE_DMACFG_ESPDESC ; 
 int SAFE_PE_DMACFG_ESSA ; 
 int SAFE_PE_DMACFG_FSENA ; 
 int SAFE_PE_DMACFG_GPRPCI ; 
 int SAFE_PE_DMACFG_PEMODE ; 
 int SAFE_PE_DMACFG_SPRPCI ; 
 int /*<<< orphan*/  SAFE_PE_GRNGBASE ; 
 int /*<<< orphan*/  SAFE_PE_PARTCFG ; 
 int /*<<< orphan*/  SAFE_PE_PARTSIZE ; 
 int /*<<< orphan*/  SAFE_PE_PDRBASE ; 
 int /*<<< orphan*/  SAFE_PE_RDRBASE ; 
 int /*<<< orphan*/  SAFE_PE_RINGCFG ; 
 int SAFE_PE_RINGCFG_OFFSET_S ; 
 int /*<<< orphan*/  SAFE_PE_RINGPOLL ; 
 int /*<<< orphan*/  SAFE_PE_SRNGBASE ; 
 scalar_t__ SAFE_REV (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_REV_MAJ (scalar_t__) ; 
 int /*<<< orphan*/  SAFE_REV_MIN (scalar_t__) ; 
 int SAFE_TOTAL_DPART ; 
 int SAFE_TOTAL_SPART ; 
 int /*<<< orphan*/  WRITE_REG (struct safe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
safe_init_board(struct safe_softc *sc)
{
	u_int32_t v, dwords;

	v = READ_REG(sc, SAFE_PE_DMACFG);
	v &=~ SAFE_PE_DMACFG_PEMODE;
	v |= SAFE_PE_DMACFG_FSENA		/* failsafe enable */
	  |  SAFE_PE_DMACFG_GPRPCI		/* gather ring on PCI */
	  |  SAFE_PE_DMACFG_SPRPCI		/* scatter ring on PCI */
	  |  SAFE_PE_DMACFG_ESDESC		/* endian-swap descriptors */
	  |  SAFE_PE_DMACFG_ESSA		/* endian-swap SA's */
	  |  SAFE_PE_DMACFG_ESPDESC		/* endian-swap part. desc's */
	  ;
	WRITE_REG(sc, SAFE_PE_DMACFG, v);
#if 0
	/* XXX select byte swap based on host byte order */
	WRITE_REG(sc, SAFE_ENDIAN, 0x1b);
#endif
	if (sc->sc_chiprev == SAFE_REV(1,0)) {
		/*
		 * Avoid large PCI DMA transfers.  Rev 1.0 has a bug where
		 * "target mode transfers" done while the chip is DMA'ing
		 * >1020 bytes cause the hardware to lockup.  To avoid this
		 * we reduce the max PCI transfer size and use small source
		 * particle descriptors (<= 256 bytes).
		 */
		WRITE_REG(sc, SAFE_DMA_CFG, 256);
		device_printf(sc->sc_dev,
			"Reduce max DMA size to %u words for rev %u.%u WAR\n",
			(READ_REG(sc, SAFE_DMA_CFG)>>2) & 0xff,
			SAFE_REV_MAJ(sc->sc_chiprev),
			SAFE_REV_MIN(sc->sc_chiprev));
	}

	/* NB: operands+results are overlaid */
	WRITE_REG(sc, SAFE_PE_PDRBASE, sc->sc_ringalloc.dma_paddr);
	WRITE_REG(sc, SAFE_PE_RDRBASE, sc->sc_ringalloc.dma_paddr);
	/*
	 * Configure ring entry size and number of items in the ring.
	 */
	KASSERT((sizeof(struct safe_ringentry) % sizeof(u_int32_t)) == 0,
		("PE ring entry not 32-bit aligned!"));
	dwords = sizeof(struct safe_ringentry) / sizeof(u_int32_t);
	WRITE_REG(sc, SAFE_PE_RINGCFG,
		(dwords << SAFE_PE_RINGCFG_OFFSET_S) | SAFE_MAX_NQUEUE);
	WRITE_REG(sc, SAFE_PE_RINGPOLL, 0);	/* disable polling */

	WRITE_REG(sc, SAFE_PE_GRNGBASE, sc->sc_spalloc.dma_paddr);
	WRITE_REG(sc, SAFE_PE_SRNGBASE, sc->sc_dpalloc.dma_paddr);
	WRITE_REG(sc, SAFE_PE_PARTSIZE,
		(SAFE_TOTAL_DPART<<16) | SAFE_TOTAL_SPART);
	/*
	 * NB: destination particles are fixed size.  We use
	 *     an mbuf cluster and require all results go to
	 *     clusters or smaller.
	 */
	WRITE_REG(sc, SAFE_PE_PARTCFG, SAFE_MAX_DSIZE);

	/* it's now safe to enable PE mode, do it */
	WRITE_REG(sc, SAFE_PE_DMACFG, v | SAFE_PE_DMACFG_PEMODE);

	/*
	 * Configure hardware to use level-triggered interrupts and
	 * to interrupt after each descriptor is processed.
	 */
	WRITE_REG(sc, SAFE_HI_CFG, SAFE_HI_CFG_LEVEL);
	WRITE_REG(sc, SAFE_HI_DESC_CNT, 1);
	WRITE_REG(sc, SAFE_HI_MASK, SAFE_INT_PE_DDONE | SAFE_INT_PE_ERROR);
}