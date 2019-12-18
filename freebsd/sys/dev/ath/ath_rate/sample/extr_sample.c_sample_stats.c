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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
struct sample_node {int static_rix; int ratemask; int* current_rix; int* packets_since_switch; int* ticks_since_switch; int* last_sample_rix; int* current_sample_rix; int* packets_sent; int* packets_since_sample; int* sample_tt; TYPE_1__** stats; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_macaddr; } ;
struct ath_softc {int /*<<< orphan*/ * sc_currates; } ;
struct TYPE_2__ {unsigned long long total_packets; unsigned long long packets_acked; int ewma_pct; scalar_t__ last_tx; int /*<<< orphan*/  average_tx_time; int /*<<< orphan*/  successive_failures; scalar_t__ tries; } ;
typedef  int /*<<< orphan*/  HAL_RATE_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_NODE (struct ieee80211_node*) ; 
 struct sample_node* ATH_NODE_SAMPLE (int /*<<< orphan*/ ) ; 
 int NUM_PACKET_SIZE_BINS ; 
 int bin_to_size (int) ; 
 int dot11rate (int /*<<< orphan*/  const*,int) ; 
 char* dot11rate_label (int /*<<< orphan*/  const*,int) ; 
 char* ether_sprintf (int /*<<< orphan*/ ) ; 
 int ieee80211_node_refcnt (struct ieee80211_node*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ ticks ; 

__attribute__((used)) static void
sample_stats(void *arg, struct ieee80211_node *ni)
{
	struct ath_softc *sc = arg;
	const HAL_RATE_TABLE *rt = sc->sc_currates;
	struct sample_node *sn = ATH_NODE_SAMPLE(ATH_NODE(ni));
	uint64_t mask;
	int rix, y;

	printf("\n[%s] refcnt %d static_rix (%d %s) ratemask 0x%jx\n",
	    ether_sprintf(ni->ni_macaddr), ieee80211_node_refcnt(ni),
	    dot11rate(rt, sn->static_rix),
	    dot11rate_label(rt, sn->static_rix),
	    (uintmax_t)sn->ratemask);
	for (y = 0; y < NUM_PACKET_SIZE_BINS; y++) {
		printf("[%4u] cur rix %d (%d %s) since switch: packets %d ticks %u\n",
		    bin_to_size(y), sn->current_rix[y],
		    dot11rate(rt, sn->current_rix[y]),
		    dot11rate_label(rt, sn->current_rix[y]),
		    sn->packets_since_switch[y], sn->ticks_since_switch[y]);
		printf("[%4u] last sample (%d %s) cur sample (%d %s) packets sent %d\n",
		    bin_to_size(y),
		    dot11rate(rt, sn->last_sample_rix[y]),
		    dot11rate_label(rt, sn->last_sample_rix[y]),
		    dot11rate(rt, sn->current_sample_rix[y]),
		    dot11rate_label(rt, sn->current_sample_rix[y]),
		    sn->packets_sent[y]);
		printf("[%4u] packets since sample %d sample tt %u\n",
		    bin_to_size(y), sn->packets_since_sample[y],
		    sn->sample_tt[y]);
	}
	for (mask = sn->ratemask, rix = 0; mask != 0; mask >>= 1, rix++) {
		if ((mask & 1) == 0)
				continue;
		for (y = 0; y < NUM_PACKET_SIZE_BINS; y++) {
			if (sn->stats[y][rix].total_packets == 0)
				continue;
			printf("[%2u %s:%4u] %8ju:%-8ju (%3d%%) (EWMA %3d.%1d%%) T %8ju F %4d avg %5u last %u\n",
			    dot11rate(rt, rix), dot11rate_label(rt, rix),
			    bin_to_size(y),
			    (uintmax_t) sn->stats[y][rix].total_packets,
			    (uintmax_t) sn->stats[y][rix].packets_acked,
			    (int) ((sn->stats[y][rix].packets_acked * 100ULL) /
			     sn->stats[y][rix].total_packets),
			    sn->stats[y][rix].ewma_pct / 10,
			    sn->stats[y][rix].ewma_pct % 10,
			    (uintmax_t) sn->stats[y][rix].tries,
			    sn->stats[y][rix].successive_failures,
			    sn->stats[y][rix].average_tx_time,
			    ticks - sn->stats[y][rix].last_tx);
		}
	}
}