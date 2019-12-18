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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct ifnet {int /*<<< orphan*/  if_mtu; } ;
struct et_softc {struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,scalar_t__,int) ; 
 int ETHER_MIN_LEN ; 
 scalar_t__ ET_FRAMELEN (int /*<<< orphan*/ ) ; 
 scalar_t__ ET_PKTFILT ; 
 int ET_PKTFILT_FRAG ; 
 int ET_PKTFILT_MINLEN_MASK ; 
 int ET_PKTFILT_MINLEN_SHIFT ; 
 scalar_t__ ET_RXMAC_CTRL ; 
 int ET_RXMAC_CTRL_ENABLE ; 
 int ET_RXMAC_CTRL_WOL_DISABLE ; 
 scalar_t__ ET_RXMAC_CUT_THRU_FRMLEN ; 
 scalar_t__ ET_RXMAC_MC_SEGSZ ; 
 int ET_RXMAC_MC_SEGSZ_ENABLE ; 
 int ET_RXMAC_MC_SEGSZ_MAX_MASK ; 
 scalar_t__ ET_RXMAC_MC_WATERMARK ; 
 scalar_t__ ET_RXMAC_MGT ; 
 int ET_RXMAC_MGT_CHECK_PKT ; 
 int ET_RXMAC_MGT_PASS_ECRC ; 
 int ET_RXMAC_MGT_PASS_ELEN ; 
 int ET_RXMAC_MGT_PASS_ETRUNC ; 
 int ET_RXMAC_SEGSZ (int) ; 
 scalar_t__ ET_RXMAC_SPACE_AVL ; 
 scalar_t__ ET_UCAST_FILTADDR1 ; 
 scalar_t__ ET_UCAST_FILTADDR2 ; 
 scalar_t__ ET_UCAST_FILTADDR3 ; 
 scalar_t__ ET_WOL_CRC ; 
 scalar_t__ ET_WOL_MASK ; 
 scalar_t__ ET_WOL_SA_HI ; 
 scalar_t__ ET_WOL_SA_LO ; 
 int* IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  et_setmulti (struct et_softc*) ; 

__attribute__((used)) static void
et_init_rxmac(struct et_softc *sc)
{
	struct ifnet *ifp;
	const uint8_t *eaddr;
	uint32_t val;
	int i;

	/* Disable RX MAC and WOL */
	CSR_WRITE_4(sc, ET_RXMAC_CTRL, ET_RXMAC_CTRL_WOL_DISABLE);

	/*
	 * Clear all WOL related registers
	 */
	for (i = 0; i < 3; ++i)
		CSR_WRITE_4(sc, ET_WOL_CRC + (i * 4), 0);
	for (i = 0; i < 20; ++i)
		CSR_WRITE_4(sc, ET_WOL_MASK + (i * 4), 0);

	/*
	 * Set WOL source address.  XXX is this necessary?
	 */
	ifp = sc->ifp;
	eaddr = IF_LLADDR(ifp);
	val = (eaddr[2] << 24) | (eaddr[3] << 16) | (eaddr[4] << 8) | eaddr[5];
	CSR_WRITE_4(sc, ET_WOL_SA_LO, val);
	val = (eaddr[0] << 8) | eaddr[1];
	CSR_WRITE_4(sc, ET_WOL_SA_HI, val);

	/* Clear packet filters */
	CSR_WRITE_4(sc, ET_PKTFILT, 0);

	/* No ucast filtering */
	CSR_WRITE_4(sc, ET_UCAST_FILTADDR1, 0);
	CSR_WRITE_4(sc, ET_UCAST_FILTADDR2, 0);
	CSR_WRITE_4(sc, ET_UCAST_FILTADDR3, 0);

	if (ET_FRAMELEN(ifp->if_mtu) > ET_RXMAC_CUT_THRU_FRMLEN) {
		/*
		 * In order to transmit jumbo packets greater than
		 * ET_RXMAC_CUT_THRU_FRMLEN bytes, the FIFO between
		 * RX MAC and RX DMA needs to be reduced in size to
		 * (ET_MEM_SIZE - ET_MEM_TXSIZE_EX - framelen).  In
		 * order to implement this, we must use "cut through"
		 * mode in the RX MAC, which chops packets down into
		 * segments.  In this case we selected 256 bytes,
		 * since this is the size of the PCI-Express TLP's
		 * that the ET1310 uses.
		 */
		val = (ET_RXMAC_SEGSZ(256) & ET_RXMAC_MC_SEGSZ_MAX_MASK) |
		      ET_RXMAC_MC_SEGSZ_ENABLE;
	} else {
		val = 0;
	}
	CSR_WRITE_4(sc, ET_RXMAC_MC_SEGSZ, val);

	CSR_WRITE_4(sc, ET_RXMAC_MC_WATERMARK, 0);

	/* Initialize RX MAC management register */
	CSR_WRITE_4(sc, ET_RXMAC_MGT, 0);

	CSR_WRITE_4(sc, ET_RXMAC_SPACE_AVL, 0);

	CSR_WRITE_4(sc, ET_RXMAC_MGT,
		    ET_RXMAC_MGT_PASS_ECRC |
		    ET_RXMAC_MGT_PASS_ELEN |
		    ET_RXMAC_MGT_PASS_ETRUNC |
		    ET_RXMAC_MGT_CHECK_PKT);

	/*
	 * Configure runt filtering (may not work on certain chip generation)
	 */
	val = (ETHER_MIN_LEN << ET_PKTFILT_MINLEN_SHIFT) &
	    ET_PKTFILT_MINLEN_MASK;
	val |= ET_PKTFILT_FRAG;
	CSR_WRITE_4(sc, ET_PKTFILT, val);

	/* Enable RX MAC but leave WOL disabled */
	CSR_WRITE_4(sc, ET_RXMAC_CTRL,
		    ET_RXMAC_CTRL_WOL_DISABLE | ET_RXMAC_CTRL_ENABLE);

	/*
	 * Setup multicast hash and allmulti/promisc mode
	 */
	et_setmulti(sc);
}