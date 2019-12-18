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
typedef  int u32 ;
struct bce_softc {int bce_flags; int /*<<< orphan*/ * rx_bd_chain_paddr; } ;

/* Variables and functions */
 int BCE_ADDR_HI (int /*<<< orphan*/ ) ; 
 int BCE_ADDR_LO (int /*<<< orphan*/ ) ; 
 scalar_t__ BCE_CHIP_NUM (struct bce_softc*) ; 
 scalar_t__ BCE_CHIP_NUM_5709 ; 
 int BCE_L2CTX_RX_BD_PRE_READ_SHIFT ; 
 int /*<<< orphan*/  BCE_L2CTX_RX_CTX_TYPE ; 
 int BCE_L2CTX_RX_CTX_TYPE_CTX_BD_CHN_TYPE_VALUE ; 
 int BCE_L2CTX_RX_CTX_TYPE_SIZE_L2 ; 
 int BCE_L2CTX_RX_HI_WATER_MARK_SCALE ; 
 int BCE_L2CTX_RX_HI_WATER_MARK_SHIFT ; 
 int BCE_L2CTX_RX_LO_WATER_MARK_DEFAULT ; 
 int BCE_L2CTX_RX_LO_WATER_MARK_SCALE ; 
 int BCE_L2CTX_RX_LO_WATER_MARK_SHIFT ; 
 int /*<<< orphan*/  BCE_L2CTX_RX_NX_BDHADDR_HI ; 
 int /*<<< orphan*/  BCE_L2CTX_RX_NX_BDHADDR_LO ; 
 int /*<<< orphan*/  BCE_MQ_MAP_L2_5 ; 
 int BCE_MQ_MAP_L2_5_ARM ; 
 int BCE_USING_TX_FLOW_CONTROL ; 
 int BCE_VERBOSE_CTX ; 
 int BCE_VERBOSE_RECV ; 
 int BCE_VERBOSE_RESET ; 
 int /*<<< orphan*/  CTX_WR (struct bce_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DBENTER (int) ; 
 int /*<<< orphan*/  DBEXIT (int) ; 
 int /*<<< orphan*/  GET_CID_ADDR (int /*<<< orphan*/ ) ; 
 int REG_RD (struct bce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bce_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RX_CID ; 
 int USABLE_RX_BD_ALLOC ; 

__attribute__((used)) static void
bce_init_rx_context(struct bce_softc *sc)
{
	u32 val;

	DBENTER(BCE_VERBOSE_RESET | BCE_VERBOSE_RECV | BCE_VERBOSE_CTX);

	/* Init the type, size, and BD cache levels for the RX context. */
	val = BCE_L2CTX_RX_CTX_TYPE_CTX_BD_CHN_TYPE_VALUE |
	    BCE_L2CTX_RX_CTX_TYPE_SIZE_L2 |
	    (0x02 << BCE_L2CTX_RX_BD_PRE_READ_SHIFT);

	/*
	 * Set the level for generating pause frames
	 * when the number of available rx_bd's gets
	 * too low (the low watermark) and the level
	 * when pause frames can be stopped (the high
	 * watermark).
	 */
	if (BCE_CHIP_NUM(sc) == BCE_CHIP_NUM_5709) {
		u32 lo_water, hi_water;

		if (sc->bce_flags & BCE_USING_TX_FLOW_CONTROL) {
			lo_water = BCE_L2CTX_RX_LO_WATER_MARK_DEFAULT;
		} else {
			lo_water = 0;
		}

		if (lo_water >= USABLE_RX_BD_ALLOC) {
			lo_water = 0;
		}

		hi_water = USABLE_RX_BD_ALLOC / 4;

		if (hi_water <= lo_water) {
			lo_water = 0;
		}

		lo_water /= BCE_L2CTX_RX_LO_WATER_MARK_SCALE;
		hi_water /= BCE_L2CTX_RX_HI_WATER_MARK_SCALE;

		if (hi_water > 0xf)
			hi_water = 0xf;
		else if (hi_water == 0)
			lo_water = 0;

		val |= (lo_water << BCE_L2CTX_RX_LO_WATER_MARK_SHIFT) |
		    (hi_water << BCE_L2CTX_RX_HI_WATER_MARK_SHIFT);
	}

	CTX_WR(sc, GET_CID_ADDR(RX_CID), BCE_L2CTX_RX_CTX_TYPE, val);

	/* Setup the MQ BIN mapping for l2_ctx_host_bseq. */
	if (BCE_CHIP_NUM(sc) == BCE_CHIP_NUM_5709) {
		val = REG_RD(sc, BCE_MQ_MAP_L2_5);
		REG_WR(sc, BCE_MQ_MAP_L2_5, val | BCE_MQ_MAP_L2_5_ARM);
	}

	/* Point the hardware to the first page in the chain. */
	val = BCE_ADDR_HI(sc->rx_bd_chain_paddr[0]);
	CTX_WR(sc, GET_CID_ADDR(RX_CID), BCE_L2CTX_RX_NX_BDHADDR_HI, val);
	val = BCE_ADDR_LO(sc->rx_bd_chain_paddr[0]);
	CTX_WR(sc, GET_CID_ADDR(RX_CID), BCE_L2CTX_RX_NX_BDHADDR_LO, val);

	DBEXIT(BCE_VERBOSE_RESET | BCE_VERBOSE_RECV | BCE_VERBOSE_CTX);
}