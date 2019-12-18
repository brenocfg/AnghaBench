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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int tx_bytes; int rx_bytes; int /*<<< orphan*/  rx_udp_csum_errs; int /*<<< orphan*/  rx_tcp_csum_errs; int /*<<< orphan*/  rx_ip_hdr_csum_errs; int /*<<< orphan*/  rx_overrun_errs; int /*<<< orphan*/  rx_resource_errs; int /*<<< orphan*/  rx_align_errs; int /*<<< orphan*/  rx_symbol_errs; int /*<<< orphan*/  rx_frames_length_errs; int /*<<< orphan*/  rx_frames_fcs_errs; int /*<<< orphan*/  rx_frames_jabber; int /*<<< orphan*/  rx_frames_oversize; int /*<<< orphan*/  rx_frames_undersize; int /*<<< orphan*/  rx_frames_1024to1536b; int /*<<< orphan*/  rx_frames_512to1023b; int /*<<< orphan*/  rx_frames_256to511b; int /*<<< orphan*/  rx_frames_128to255b; int /*<<< orphan*/  rx_frames_65to127b; int /*<<< orphan*/  rx_frames_64b; int /*<<< orphan*/  rx_frames_pause; int /*<<< orphan*/  rx_frames_multi; int /*<<< orphan*/  rx_frames_bcast; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  tx_carrier_sense_errs; int /*<<< orphan*/  tx_deferred_frames; int /*<<< orphan*/  tx_late_collisn; int /*<<< orphan*/  tx_excsv_collisn; int /*<<< orphan*/  tx_multi_collisn; int /*<<< orphan*/  tx_single_collisn; int /*<<< orphan*/  tx_under_runs; int /*<<< orphan*/  tx_frames_1024to1536b; int /*<<< orphan*/  tx_frames_512to1023b; int /*<<< orphan*/  tx_frames_256to511b; int /*<<< orphan*/  tx_frames_128to255b; int /*<<< orphan*/  tx_frames_65to127b; int /*<<< orphan*/  tx_frames_64b; int /*<<< orphan*/  tx_frames_pause; int /*<<< orphan*/  tx_frames_multi; int /*<<< orphan*/  tx_frames_bcast; int /*<<< orphan*/  tx_frames; } ;
struct cgem_softc {TYPE_1__ stats; int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGEM_ALIGN_ERRS ; 
 int /*<<< orphan*/  CGEM_ASSERT_LOCKED (struct cgem_softc*) ; 
 int /*<<< orphan*/  CGEM_BCAST_FRAMES_RX ; 
 int /*<<< orphan*/  CGEM_BCAST_FRAMES_TX ; 
 int /*<<< orphan*/  CGEM_CARRIER_SENSE_ERRS ; 
 int /*<<< orphan*/  CGEM_DEFERRED_TX_FRAMES ; 
 int /*<<< orphan*/  CGEM_EXCESSIVE_COLL_FRAMES ; 
 int /*<<< orphan*/  CGEM_FCS_ERRS ; 
 int /*<<< orphan*/  CGEM_FRAMES_1024_1518B_RX ; 
 int /*<<< orphan*/  CGEM_FRAMES_1024_1518B_TX ; 
 int /*<<< orphan*/  CGEM_FRAMES_128_255B_RX ; 
 int /*<<< orphan*/  CGEM_FRAMES_128_255B_TX ; 
 int /*<<< orphan*/  CGEM_FRAMES_256_511B_RX ; 
 int /*<<< orphan*/  CGEM_FRAMES_256_511B_TX ; 
 int /*<<< orphan*/  CGEM_FRAMES_512_1023B_RX ; 
 int /*<<< orphan*/  CGEM_FRAMES_512_1023B_TX ; 
 int /*<<< orphan*/  CGEM_FRAMES_64B_RX ; 
 int /*<<< orphan*/  CGEM_FRAMES_64B_TX ; 
 int /*<<< orphan*/  CGEM_FRAMES_65_127B_RX ; 
 int /*<<< orphan*/  CGEM_FRAMES_65_127B_TX ; 
 int /*<<< orphan*/  CGEM_FRAMES_RX ; 
 int /*<<< orphan*/  CGEM_FRAMES_TX ; 
 int /*<<< orphan*/  CGEM_IP_HDR_CKSUM_ERRS ; 
 int /*<<< orphan*/  CGEM_JABBERS_RX ; 
 int /*<<< orphan*/  CGEM_LATE_COLL ; 
 int /*<<< orphan*/  CGEM_LENGTH_FIELD_ERRS ; 
 int /*<<< orphan*/  CGEM_MULTI_COLL_FRAMES ; 
 int /*<<< orphan*/  CGEM_MULTI_FRAMES_RX ; 
 int /*<<< orphan*/  CGEM_MULTI_FRAMES_TX ; 
 int /*<<< orphan*/  CGEM_OCTETS_RX_BOT ; 
 int /*<<< orphan*/  CGEM_OCTETS_RX_TOP ; 
 int /*<<< orphan*/  CGEM_OCTETS_TX_BOT ; 
 int /*<<< orphan*/  CGEM_OCTETS_TX_TOP ; 
 int /*<<< orphan*/  CGEM_OVERSZ_RX ; 
 int /*<<< orphan*/  CGEM_PAUSE_FRAMES_RX ; 
 int /*<<< orphan*/  CGEM_PAUSE_FRAMES_TX ; 
 int /*<<< orphan*/  CGEM_RX_OVERRUN_ERRS ; 
 int /*<<< orphan*/  CGEM_RX_RESOURCE_ERRS ; 
 int /*<<< orphan*/  CGEM_RX_SYMBOL_ERRS ; 
 int /*<<< orphan*/  CGEM_SINGLE_COLL_FRAMES ; 
 int /*<<< orphan*/  CGEM_TCP_CKSUM_ERRS ; 
 int /*<<< orphan*/  CGEM_TX_UNDERRUNS ; 
 int /*<<< orphan*/  CGEM_UDP_CKSUM_ERRS ; 
 int /*<<< orphan*/  CGEM_UNDERSZ_RX ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 scalar_t__ RD4 (struct cgem_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
cgem_poll_hw_stats(struct cgem_softc *sc)
{
	uint32_t n;

	CGEM_ASSERT_LOCKED(sc);

	sc->stats.tx_bytes += RD4(sc, CGEM_OCTETS_TX_BOT);
	sc->stats.tx_bytes += (uint64_t)RD4(sc, CGEM_OCTETS_TX_TOP) << 32;

	sc->stats.tx_frames += RD4(sc, CGEM_FRAMES_TX);
	sc->stats.tx_frames_bcast += RD4(sc, CGEM_BCAST_FRAMES_TX);
	sc->stats.tx_frames_multi += RD4(sc, CGEM_MULTI_FRAMES_TX);
	sc->stats.tx_frames_pause += RD4(sc, CGEM_PAUSE_FRAMES_TX);
	sc->stats.tx_frames_64b += RD4(sc, CGEM_FRAMES_64B_TX);
	sc->stats.tx_frames_65to127b += RD4(sc, CGEM_FRAMES_65_127B_TX);
	sc->stats.tx_frames_128to255b += RD4(sc, CGEM_FRAMES_128_255B_TX);
	sc->stats.tx_frames_256to511b += RD4(sc, CGEM_FRAMES_256_511B_TX);
	sc->stats.tx_frames_512to1023b += RD4(sc, CGEM_FRAMES_512_1023B_TX);
	sc->stats.tx_frames_1024to1536b += RD4(sc, CGEM_FRAMES_1024_1518B_TX);
	sc->stats.tx_under_runs += RD4(sc, CGEM_TX_UNDERRUNS);

	n = RD4(sc, CGEM_SINGLE_COLL_FRAMES);
	sc->stats.tx_single_collisn += n;
	if_inc_counter(sc->ifp, IFCOUNTER_COLLISIONS, n);
	n = RD4(sc, CGEM_MULTI_COLL_FRAMES);
	sc->stats.tx_multi_collisn += n;
	if_inc_counter(sc->ifp, IFCOUNTER_COLLISIONS, n);
	n = RD4(sc, CGEM_EXCESSIVE_COLL_FRAMES);
	sc->stats.tx_excsv_collisn += n;
	if_inc_counter(sc->ifp, IFCOUNTER_COLLISIONS, n);
	n = RD4(sc, CGEM_LATE_COLL);
	sc->stats.tx_late_collisn += n;
	if_inc_counter(sc->ifp, IFCOUNTER_COLLISIONS, n);

	sc->stats.tx_deferred_frames += RD4(sc, CGEM_DEFERRED_TX_FRAMES);
	sc->stats.tx_carrier_sense_errs += RD4(sc, CGEM_CARRIER_SENSE_ERRS);

	sc->stats.rx_bytes += RD4(sc, CGEM_OCTETS_RX_BOT);
	sc->stats.rx_bytes += (uint64_t)RD4(sc, CGEM_OCTETS_RX_TOP) << 32;

	sc->stats.rx_frames += RD4(sc, CGEM_FRAMES_RX);
	sc->stats.rx_frames_bcast += RD4(sc, CGEM_BCAST_FRAMES_RX);
	sc->stats.rx_frames_multi += RD4(sc, CGEM_MULTI_FRAMES_RX);
	sc->stats.rx_frames_pause += RD4(sc, CGEM_PAUSE_FRAMES_RX);
	sc->stats.rx_frames_64b += RD4(sc, CGEM_FRAMES_64B_RX);
	sc->stats.rx_frames_65to127b += RD4(sc, CGEM_FRAMES_65_127B_RX);
	sc->stats.rx_frames_128to255b += RD4(sc, CGEM_FRAMES_128_255B_RX);
	sc->stats.rx_frames_256to511b += RD4(sc, CGEM_FRAMES_256_511B_RX);
	sc->stats.rx_frames_512to1023b += RD4(sc, CGEM_FRAMES_512_1023B_RX);
	sc->stats.rx_frames_1024to1536b += RD4(sc, CGEM_FRAMES_1024_1518B_RX);
	sc->stats.rx_frames_undersize += RD4(sc, CGEM_UNDERSZ_RX);
	sc->stats.rx_frames_oversize += RD4(sc, CGEM_OVERSZ_RX);
	sc->stats.rx_frames_jabber += RD4(sc, CGEM_JABBERS_RX);
	sc->stats.rx_frames_fcs_errs += RD4(sc, CGEM_FCS_ERRS);
	sc->stats.rx_frames_length_errs += RD4(sc, CGEM_LENGTH_FIELD_ERRS);
	sc->stats.rx_symbol_errs += RD4(sc, CGEM_RX_SYMBOL_ERRS);
	sc->stats.rx_align_errs += RD4(sc, CGEM_ALIGN_ERRS);
	sc->stats.rx_resource_errs += RD4(sc, CGEM_RX_RESOURCE_ERRS);
	sc->stats.rx_overrun_errs += RD4(sc, CGEM_RX_OVERRUN_ERRS);
	sc->stats.rx_ip_hdr_csum_errs += RD4(sc, CGEM_IP_HDR_CKSUM_ERRS);
	sc->stats.rx_tcp_csum_errs += RD4(sc, CGEM_TCP_CKSUM_ERRS);
	sc->stats.rx_udp_csum_errs += RD4(sc, CGEM_UDP_CKSUM_ERRS);
}