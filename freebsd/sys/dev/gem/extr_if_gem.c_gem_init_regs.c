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
typedef  int u_char ;
struct gem_softc {int sc_flags; int /*<<< orphan*/  sc_ifp; } ;

/* Variables and functions */
 int ETHER_MAX_LEN ; 
 int const ETHER_MIN_LEN ; 
 int ETHER_VLAN_ENCAP_LEN ; 
 int /*<<< orphan*/  GEM_BANK1_WRITE_4 (struct gem_softc*,int /*<<< orphan*/ ,int const) ; 
 int GEM_INITED ; 
 int /*<<< orphan*/  GEM_LOCK_ASSERT (struct gem_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_MAC_ADDR0 ; 
 int /*<<< orphan*/  GEM_MAC_ADDR1 ; 
 int /*<<< orphan*/  GEM_MAC_ADDR2 ; 
 int /*<<< orphan*/  GEM_MAC_ADDR3 ; 
 int /*<<< orphan*/  GEM_MAC_ADDR4 ; 
 int /*<<< orphan*/  GEM_MAC_ADDR5 ; 
 int /*<<< orphan*/  GEM_MAC_ADDR6 ; 
 int /*<<< orphan*/  GEM_MAC_ADDR7 ; 
 int /*<<< orphan*/  GEM_MAC_ADDR8 ; 
 int /*<<< orphan*/  GEM_MAC_ADDR_FILTER0 ; 
 int /*<<< orphan*/  GEM_MAC_ADDR_FILTER1 ; 
 int /*<<< orphan*/  GEM_MAC_ADDR_FILTER2 ; 
 int /*<<< orphan*/  GEM_MAC_ADR_FLT_MASK0 ; 
 int /*<<< orphan*/  GEM_MAC_ADR_FLT_MASK1_2 ; 
 int /*<<< orphan*/  GEM_MAC_ATTEMPT_LIMIT ; 
 int /*<<< orphan*/  GEM_MAC_CONTROL_TYPE ; 
 int /*<<< orphan*/  GEM_MAC_DEFER_TMR_CNT ; 
 int /*<<< orphan*/  GEM_MAC_EXCESS_COLL_CNT ; 
 int /*<<< orphan*/  GEM_MAC_FIRST_COLL_CNT ; 
 int /*<<< orphan*/  GEM_MAC_IPG0 ; 
 int /*<<< orphan*/  GEM_MAC_IPG1 ; 
 int /*<<< orphan*/  GEM_MAC_IPG2 ; 
 int /*<<< orphan*/  GEM_MAC_JAM_SIZE ; 
 int /*<<< orphan*/  GEM_MAC_LATE_COLL_CNT ; 
 int /*<<< orphan*/  GEM_MAC_MAC_MAX_FRAME ; 
 int /*<<< orphan*/  GEM_MAC_MAC_MIN_FRAME ; 
 int /*<<< orphan*/  GEM_MAC_NORM_COLL_CNT ; 
 int /*<<< orphan*/  GEM_MAC_PEAK_ATTEMPTS ; 
 int /*<<< orphan*/  GEM_MAC_PREAMBLE_LEN ; 
 int /*<<< orphan*/  GEM_MAC_RANDOM_SEED ; 
 int /*<<< orphan*/  GEM_MAC_RX_ALIGN_ERR ; 
 int /*<<< orphan*/  GEM_MAC_RX_CODE_VIOL ; 
 int /*<<< orphan*/  GEM_MAC_RX_CRC_ERR_CNT ; 
 int /*<<< orphan*/  GEM_MAC_RX_FRAME_COUNT ; 
 int /*<<< orphan*/  GEM_MAC_RX_LEN_ERR_CNT ; 
 int /*<<< orphan*/  GEM_MAC_SEND_PAUSE_CMD ; 
 int /*<<< orphan*/  GEM_MAC_XIF_CONFIG ; 
 int const GEM_MAC_XIF_TX_MII_ENA ; 
 int* IF_LLADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 

__attribute__((used)) static void
gem_init_regs(struct gem_softc *sc)
{
	const u_char *laddr = IF_LLADDR(sc->sc_ifp);

	GEM_LOCK_ASSERT(sc, MA_OWNED);

	/* These registers are not cleared on reset. */
	if ((sc->sc_flags & GEM_INITED) == 0) {
		/* magic values */
		GEM_BANK1_WRITE_4(sc, GEM_MAC_IPG0, 0);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_IPG1, 8);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_IPG2, 4);

		/* min frame length */
		GEM_BANK1_WRITE_4(sc, GEM_MAC_MAC_MIN_FRAME, ETHER_MIN_LEN);
		/* max frame length and max burst size */
		GEM_BANK1_WRITE_4(sc, GEM_MAC_MAC_MAX_FRAME,
		    (ETHER_MAX_LEN + ETHER_VLAN_ENCAP_LEN) | (0x2000 << 16));

		/* more magic values */
		GEM_BANK1_WRITE_4(sc, GEM_MAC_PREAMBLE_LEN, 0x7);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_JAM_SIZE, 0x4);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ATTEMPT_LIMIT, 0x10);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_CONTROL_TYPE, 0x8808);

		/* random number seed */
		GEM_BANK1_WRITE_4(sc, GEM_MAC_RANDOM_SEED,
		    ((laddr[5] << 8) | laddr[4]) & 0x3ff);

		/* secondary MAC address: 0:0:0:0:0:0 */
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR3, 0);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR4, 0);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR5, 0);

		/* MAC control address: 01:80:c2:00:00:01 */
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR6, 0x0001);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR7, 0xc200);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR8, 0x0180);

		/* MAC filter address: 0:0:0:0:0:0 */
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR_FILTER0, 0);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR_FILTER1, 0);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR_FILTER2, 0);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ADR_FLT_MASK1_2, 0);
		GEM_BANK1_WRITE_4(sc, GEM_MAC_ADR_FLT_MASK0, 0);

		sc->sc_flags |= GEM_INITED;
	}

	/* Counters need to be zeroed. */
	GEM_BANK1_WRITE_4(sc, GEM_MAC_NORM_COLL_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_FIRST_COLL_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_EXCESS_COLL_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_LATE_COLL_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_DEFER_TMR_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_PEAK_ATTEMPTS, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RX_FRAME_COUNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RX_LEN_ERR_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RX_ALIGN_ERR, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RX_CRC_ERR_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RX_CODE_VIOL, 0);

	/* Set XOFF PAUSE time. */
	GEM_BANK1_WRITE_4(sc, GEM_MAC_SEND_PAUSE_CMD, 0x1BF0);

	/* Set the station address. */
	GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR0, (laddr[4] << 8) | laddr[5]);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR1, (laddr[2] << 8) | laddr[3]);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_ADDR2, (laddr[0] << 8) | laddr[1]);

	/* Enable MII outputs. */
	GEM_BANK1_WRITE_4(sc, GEM_MAC_XIF_CONFIG, GEM_MAC_XIF_TX_MII_ENA);
}