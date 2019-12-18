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
struct cas_softc {int sc_flags; int /*<<< orphan*/  sc_ifp; } ;

/* Variables and functions */
 int CAS_INITED ; 
 int /*<<< orphan*/  CAS_LOCK_ASSERT (struct cas_softc*,int /*<<< orphan*/ ) ; 
 int CAS_MAC_ADDR0 ; 
 int CAS_MAC_ADDR1 ; 
 int CAS_MAC_ADDR2 ; 
 int CAS_MAC_ADDR3 ; 
 int CAS_MAC_ADDR4 ; 
 int CAS_MAC_ADDR41 ; 
 int CAS_MAC_ADDR42 ; 
 int CAS_MAC_ADDR43 ; 
 int CAS_MAC_ADDR44 ; 
 int CAS_MAC_AFILTER0 ; 
 int CAS_MAC_AFILTER1 ; 
 int CAS_MAC_AFILTER2 ; 
 int CAS_MAC_AFILTER_MASK0 ; 
 int CAS_MAC_AFILTER_MASK1_2 ; 
 int CAS_MAC_ATTEMPT_LIMIT ; 
 int CAS_MAC_CTRL_TYPE ; 
 int CAS_MAC_DEFER_TMR_CNT ; 
 int CAS_MAC_EXCESS_COLL_CNT ; 
 int CAS_MAC_FIRST_COLL_CNT ; 
 int CAS_MAC_HASH0 ; 
 int CAS_MAC_HASH1 ; 
 int CAS_MAC_HASH15 ; 
 int CAS_MAC_IPG0 ; 
 int CAS_MAC_IPG1 ; 
 int CAS_MAC_IPG2 ; 
 int CAS_MAC_JAM_SIZE ; 
 int CAS_MAC_LATE_COLL_CNT ; 
 int CAS_MAC_MAX_BF ; 
 int CAS_MAC_MAX_BF_BST_SHFT ; 
 int CAS_MAC_MAX_BF_FRM_SHFT ; 
 int CAS_MAC_MIN_FRAME ; 
 int CAS_MAC_NORM_COLL_CNT ; 
 int CAS_MAC_PEAK_ATTEMPTS ; 
 int CAS_MAC_PREAMBLE_LEN ; 
 int CAS_MAC_RANDOM_SEED ; 
 int CAS_MAC_RX_ALIGN_ERR ; 
 int CAS_MAC_RX_CODE_VIOL ; 
 int CAS_MAC_RX_CRC_ERR_CNT ; 
 int CAS_MAC_RX_FRAME_COUNT ; 
 int CAS_MAC_RX_LEN_ERR_CNT ; 
 int CAS_MAC_SPC ; 
 int CAS_MAC_SPC_TIME_SHFT ; 
 int CAS_MAC_XIF_CONF ; 
 int const CAS_MAC_XIF_CONF_TX_OE ; 
 int /*<<< orphan*/  CAS_WRITE_4 (struct cas_softc*,int,int const) ; 
 int ETHER_MAX_LEN_JUMBO ; 
 int const ETHER_MIN_LEN ; 
 int ETHER_VLAN_ENCAP_LEN ; 
 int* IF_LLADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 

__attribute__((used)) static void
cas_init_regs(struct cas_softc *sc)
{
	int i;
	const u_char *laddr = IF_LLADDR(sc->sc_ifp);

	CAS_LOCK_ASSERT(sc, MA_OWNED);

	/* These registers are not cleared on reset. */
	if ((sc->sc_flags & CAS_INITED) == 0) {
		/* magic values */
		CAS_WRITE_4(sc, CAS_MAC_IPG0, 0);
		CAS_WRITE_4(sc, CAS_MAC_IPG1, 8);
		CAS_WRITE_4(sc, CAS_MAC_IPG2, 4);

		/* min frame length */
		CAS_WRITE_4(sc, CAS_MAC_MIN_FRAME, ETHER_MIN_LEN);
		/* max frame length and max burst size */
		CAS_WRITE_4(sc, CAS_MAC_MAX_BF,
		    ((ETHER_MAX_LEN_JUMBO + ETHER_VLAN_ENCAP_LEN) <<
		    CAS_MAC_MAX_BF_FRM_SHFT) |
		    (0x2000 << CAS_MAC_MAX_BF_BST_SHFT));

		/* more magic values */
		CAS_WRITE_4(sc, CAS_MAC_PREAMBLE_LEN, 0x7);
		CAS_WRITE_4(sc, CAS_MAC_JAM_SIZE, 0x4);
		CAS_WRITE_4(sc, CAS_MAC_ATTEMPT_LIMIT, 0x10);
		CAS_WRITE_4(sc, CAS_MAC_CTRL_TYPE, 0x8808);

		/* random number seed */
		CAS_WRITE_4(sc, CAS_MAC_RANDOM_SEED,
		    ((laddr[5] << 8) | laddr[4]) & 0x3ff);

		/* secondary MAC addresses: 0:0:0:0:0:0 */
		for (i = CAS_MAC_ADDR3; i <= CAS_MAC_ADDR41;
		    i += CAS_MAC_ADDR4 - CAS_MAC_ADDR3)
			CAS_WRITE_4(sc, i, 0);

		/* MAC control address: 01:80:c2:00:00:01 */
		CAS_WRITE_4(sc, CAS_MAC_ADDR42, 0x0001);
		CAS_WRITE_4(sc, CAS_MAC_ADDR43, 0xc200);
		CAS_WRITE_4(sc, CAS_MAC_ADDR44, 0x0180);

		/* MAC filter address: 0:0:0:0:0:0 */
		CAS_WRITE_4(sc, CAS_MAC_AFILTER0, 0);
		CAS_WRITE_4(sc, CAS_MAC_AFILTER1, 0);
		CAS_WRITE_4(sc, CAS_MAC_AFILTER2, 0);
		CAS_WRITE_4(sc, CAS_MAC_AFILTER_MASK1_2, 0);
		CAS_WRITE_4(sc, CAS_MAC_AFILTER_MASK0, 0);

		/* Zero the hash table. */
		for (i = CAS_MAC_HASH0; i <= CAS_MAC_HASH15;
		    i += CAS_MAC_HASH1 - CAS_MAC_HASH0)
			CAS_WRITE_4(sc, i, 0);

		sc->sc_flags |= CAS_INITED;
	}

	/* Counters need to be zeroed. */
	CAS_WRITE_4(sc, CAS_MAC_NORM_COLL_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_FIRST_COLL_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_EXCESS_COLL_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_LATE_COLL_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_DEFER_TMR_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_PEAK_ATTEMPTS, 0);
	CAS_WRITE_4(sc, CAS_MAC_RX_FRAME_COUNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_RX_LEN_ERR_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_RX_ALIGN_ERR, 0);
	CAS_WRITE_4(sc, CAS_MAC_RX_CRC_ERR_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_RX_CODE_VIOL, 0);

	/* Set XOFF PAUSE time. */
	CAS_WRITE_4(sc, CAS_MAC_SPC, 0x1BF0 << CAS_MAC_SPC_TIME_SHFT);

	/* Set the station address. */
	CAS_WRITE_4(sc, CAS_MAC_ADDR0, (laddr[4] << 8) | laddr[5]);
	CAS_WRITE_4(sc, CAS_MAC_ADDR1, (laddr[2] << 8) | laddr[3]);
	CAS_WRITE_4(sc, CAS_MAC_ADDR2, (laddr[0] << 8) | laddr[1]);

	/* Enable MII outputs. */
	CAS_WRITE_4(sc, CAS_MAC_XIF_CONF, CAS_MAC_XIF_CONF_TX_OE);
}