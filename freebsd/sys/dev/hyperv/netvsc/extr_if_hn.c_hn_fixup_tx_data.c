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
typedef  int /*<<< orphan*/  uint64_t ;
struct hn_softc {scalar_t__ hn_chim_szmax; int hn_caps; int hn_tx_ring_cnt; TYPE_1__* hn_tx_ring; int /*<<< orphan*/  hn_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  hn_tx_flags; int /*<<< orphan*/  hn_csum_assist; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSUM_IP ; 
 int /*<<< orphan*/  CSUM_IP6_TCP ; 
 int /*<<< orphan*/  CSUM_IP6_UDP ; 
 int /*<<< orphan*/  CSUM_IP_TCP ; 
 int /*<<< orphan*/  CSUM_IP_UDP ; 
 int HN_CAP_HASHVAL ; 
 int HN_CAP_IPCS ; 
 int HN_CAP_TCP4CS ; 
 int HN_CAP_TCP6CS ; 
 int HN_CAP_UDP4CS ; 
 int HN_CAP_UDP6CS ; 
 int /*<<< orphan*/  HN_TX_FLAG_HASHVAL ; 
 scalar_t__ bootverbose ; 
 scalar_t__ hn_enable_udp4cs ; 
 scalar_t__ hn_enable_udp6cs ; 
 int /*<<< orphan*/  hn_set_chim_size (struct hn_softc*,scalar_t__) ; 
 scalar_t__ hn_tx_chimney_size ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
hn_fixup_tx_data(struct hn_softc *sc)
{
	uint64_t csum_assist;
	int i;

	hn_set_chim_size(sc, sc->hn_chim_szmax);
	if (hn_tx_chimney_size > 0 &&
	    hn_tx_chimney_size < sc->hn_chim_szmax)
		hn_set_chim_size(sc, hn_tx_chimney_size);

	csum_assist = 0;
	if (sc->hn_caps & HN_CAP_IPCS)
		csum_assist |= CSUM_IP;
	if (sc->hn_caps & HN_CAP_TCP4CS)
		csum_assist |= CSUM_IP_TCP;
	if ((sc->hn_caps & HN_CAP_UDP4CS) && hn_enable_udp4cs)
		csum_assist |= CSUM_IP_UDP;
	if (sc->hn_caps & HN_CAP_TCP6CS)
		csum_assist |= CSUM_IP6_TCP;
	if ((sc->hn_caps & HN_CAP_UDP6CS) && hn_enable_udp6cs)
		csum_assist |= CSUM_IP6_UDP;
	for (i = 0; i < sc->hn_tx_ring_cnt; ++i)
		sc->hn_tx_ring[i].hn_csum_assist = csum_assist;

	if (sc->hn_caps & HN_CAP_HASHVAL) {
		/*
		 * Support HASHVAL pktinfo on TX path.
		 */
		if (bootverbose)
			if_printf(sc->hn_ifp, "support HASHVAL pktinfo\n");
		for (i = 0; i < sc->hn_tx_ring_cnt; ++i)
			sc->hn_tx_ring[i].hn_tx_flags |= HN_TX_FLAG_HASHVAL;
	}
}