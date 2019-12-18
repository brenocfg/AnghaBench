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
struct vge_hw_stats {int rx_frames; int rx_good_frames; int rx_fifo_oflows; int rx_runts; int rx_runts_errs; int rx_pkts_64; int rx_pkts_65_127; int rx_pkts_128_255; int rx_pkts_256_511; int rx_pkts_512_1023; int rx_pkts_1024_1518; int rx_pkts_1519_max; int rx_pkts_1519_max_errs; int rx_jumbos; int rx_crcerrs; int rx_pause_frames; int rx_alignerrs; int rx_nobufs; int rx_symerrs; int rx_lenerrs; int tx_good_frames; int tx_pkts_64; int tx_pkts_65_127; int tx_pkts_128_255; int tx_pkts_256_511; int tx_pkts_512_1023; int tx_pkts_1024_1518; int tx_jumbos; int tx_colls; int tx_pause; int tx_sqeerrs; int tx_latecolls; } ;
struct vge_softc {int /*<<< orphan*/  vge_dev; struct ifnet* vge_ifp; struct vge_hw_stats vge_stats; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  mib ;

/* Variables and functions */
 int CSR_READ_1 (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  VGE_LOCK_ASSERT (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_MIBCSR ; 
 int VGE_MIBCSR_FLUSH ; 
 int VGE_MIBCSR_RINI ; 
 int /*<<< orphan*/  VGE_MIBDATA ; 
 int VGE_MIB_CNT ; 
 int VGE_MIB_DATA_IDX (int) ; 
 int VGE_MIB_DATA_MASK ; 
 size_t VGE_MIB_RX_ALIGNERRS ; 
 size_t VGE_MIB_RX_CRCERRS ; 
 size_t VGE_MIB_RX_FIFO_OVERRUNS ; 
 size_t VGE_MIB_RX_FRAMES ; 
 size_t VGE_MIB_RX_GOOD_FRAMES ; 
 size_t VGE_MIB_RX_JUMBOS ; 
 size_t VGE_MIB_RX_LENERRS ; 
 size_t VGE_MIB_RX_NOBUFS ; 
 size_t VGE_MIB_RX_PAUSE ; 
 size_t VGE_MIB_RX_PKTS_1024_1518 ; 
 size_t VGE_MIB_RX_PKTS_128_255 ; 
 size_t VGE_MIB_RX_PKTS_1519_MAX ; 
 size_t VGE_MIB_RX_PKTS_1519_MAX_ERRS ; 
 size_t VGE_MIB_RX_PKTS_256_511 ; 
 size_t VGE_MIB_RX_PKTS_512_1023 ; 
 size_t VGE_MIB_RX_PKTS_64 ; 
 size_t VGE_MIB_RX_PKTS_65_127 ; 
 size_t VGE_MIB_RX_RUNTS ; 
 size_t VGE_MIB_RX_RUNTS_ERRS ; 
 size_t VGE_MIB_RX_SYMERRS ; 
 size_t VGE_MIB_TX_COLLS ; 
 size_t VGE_MIB_TX_GOOD_FRAMES ; 
 size_t VGE_MIB_TX_JUMBOS ; 
 size_t VGE_MIB_TX_LATECOLLS ; 
 size_t VGE_MIB_TX_PAUSE ; 
 size_t VGE_MIB_TX_PKTS_1024_1518 ; 
 size_t VGE_MIB_TX_PKTS_128_255 ; 
 size_t VGE_MIB_TX_PKTS_256_511 ; 
 size_t VGE_MIB_TX_PKTS_512_1023 ; 
 size_t VGE_MIB_TX_PKTS_64 ; 
 size_t VGE_MIB_TX_PKTS_65_127 ; 
 size_t VGE_MIB_TX_SQEERRS ; 
 int VGE_TIMEOUT ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vge_stats_clear (struct vge_softc*) ; 

__attribute__((used)) static void
vge_stats_update(struct vge_softc *sc)
{
	struct vge_hw_stats *stats;
	struct ifnet *ifp;
	uint32_t mib[VGE_MIB_CNT], val;
	int i;

	VGE_LOCK_ASSERT(sc);

	stats = &sc->vge_stats;
	ifp = sc->vge_ifp;

	CSR_WRITE_1(sc, VGE_MIBCSR,
	    CSR_READ_1(sc, VGE_MIBCSR) | VGE_MIBCSR_FLUSH);
	for (i = VGE_TIMEOUT; i > 0; i--) {
		DELAY(1);
		if ((CSR_READ_1(sc, VGE_MIBCSR) & VGE_MIBCSR_FLUSH) == 0)
			break;
	}
	if (i == 0) {
		device_printf(sc->vge_dev, "MIB counter dump timed out!\n");
		vge_stats_clear(sc);
		return;
	}

	bzero(mib, sizeof(mib));
reset_idx:
	/* Set MIB read index to 0. */
	CSR_WRITE_1(sc, VGE_MIBCSR,
	    CSR_READ_1(sc, VGE_MIBCSR) | VGE_MIBCSR_RINI);
	for (i = 0; i < VGE_MIB_CNT; i++) {
		val = CSR_READ_4(sc, VGE_MIBDATA);
		if (i != VGE_MIB_DATA_IDX(val)) {
			/* Reading interrupted. */
			goto reset_idx;
		}
		mib[i] = val & VGE_MIB_DATA_MASK;
	}

	/* Rx stats. */
	stats->rx_frames += mib[VGE_MIB_RX_FRAMES];
	stats->rx_good_frames += mib[VGE_MIB_RX_GOOD_FRAMES];
	stats->rx_fifo_oflows += mib[VGE_MIB_RX_FIFO_OVERRUNS];
	stats->rx_runts += mib[VGE_MIB_RX_RUNTS];
	stats->rx_runts_errs += mib[VGE_MIB_RX_RUNTS_ERRS];
	stats->rx_pkts_64 += mib[VGE_MIB_RX_PKTS_64];
	stats->rx_pkts_65_127 += mib[VGE_MIB_RX_PKTS_65_127];
	stats->rx_pkts_128_255 += mib[VGE_MIB_RX_PKTS_128_255];
	stats->rx_pkts_256_511 += mib[VGE_MIB_RX_PKTS_256_511];
	stats->rx_pkts_512_1023 += mib[VGE_MIB_RX_PKTS_512_1023];
	stats->rx_pkts_1024_1518 += mib[VGE_MIB_RX_PKTS_1024_1518];
	stats->rx_pkts_1519_max += mib[VGE_MIB_RX_PKTS_1519_MAX];
	stats->rx_pkts_1519_max_errs += mib[VGE_MIB_RX_PKTS_1519_MAX_ERRS];
	stats->rx_jumbos += mib[VGE_MIB_RX_JUMBOS];
	stats->rx_crcerrs += mib[VGE_MIB_RX_CRCERRS];
	stats->rx_pause_frames += mib[VGE_MIB_RX_PAUSE];
	stats->rx_alignerrs += mib[VGE_MIB_RX_ALIGNERRS];
	stats->rx_nobufs += mib[VGE_MIB_RX_NOBUFS];
	stats->rx_symerrs += mib[VGE_MIB_RX_SYMERRS];
	stats->rx_lenerrs += mib[VGE_MIB_RX_LENERRS];

	/* Tx stats. */
	stats->tx_good_frames += mib[VGE_MIB_TX_GOOD_FRAMES];
	stats->tx_pkts_64 += mib[VGE_MIB_TX_PKTS_64];
	stats->tx_pkts_65_127 += mib[VGE_MIB_TX_PKTS_65_127];
	stats->tx_pkts_128_255 += mib[VGE_MIB_TX_PKTS_128_255];
	stats->tx_pkts_256_511 += mib[VGE_MIB_TX_PKTS_256_511];
	stats->tx_pkts_512_1023 += mib[VGE_MIB_TX_PKTS_512_1023];
	stats->tx_pkts_1024_1518 += mib[VGE_MIB_TX_PKTS_1024_1518];
	stats->tx_jumbos += mib[VGE_MIB_TX_JUMBOS];
	stats->tx_colls += mib[VGE_MIB_TX_COLLS];
	stats->tx_pause += mib[VGE_MIB_TX_PAUSE];
#ifdef VGE_ENABLE_SQEERR
	stats->tx_sqeerrs += mib[VGE_MIB_TX_SQEERRS];
#endif
	stats->tx_latecolls += mib[VGE_MIB_TX_LATECOLLS];

	/* Update counters in ifnet. */
	if_inc_counter(ifp, IFCOUNTER_OPACKETS, mib[VGE_MIB_TX_GOOD_FRAMES]);

	if_inc_counter(ifp, IFCOUNTER_COLLISIONS,
	    mib[VGE_MIB_TX_COLLS] + mib[VGE_MIB_TX_LATECOLLS]);

	if_inc_counter(ifp, IFCOUNTER_OERRORS,
	    mib[VGE_MIB_TX_COLLS] + mib[VGE_MIB_TX_LATECOLLS]);

	if_inc_counter(ifp, IFCOUNTER_IPACKETS, mib[VGE_MIB_RX_GOOD_FRAMES]);

	if_inc_counter(ifp, IFCOUNTER_IERRORS,
	    mib[VGE_MIB_RX_FIFO_OVERRUNS] +
	    mib[VGE_MIB_RX_RUNTS] +
	    mib[VGE_MIB_RX_RUNTS_ERRS] +
	    mib[VGE_MIB_RX_CRCERRS] +
	    mib[VGE_MIB_RX_ALIGNERRS] +
	    mib[VGE_MIB_RX_NOBUFS] +
	    mib[VGE_MIB_RX_SYMERRS] +
	    mib[VGE_MIB_RX_LENERRS]);
}