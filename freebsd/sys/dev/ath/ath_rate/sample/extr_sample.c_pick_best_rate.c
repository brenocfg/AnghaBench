#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct sample_node {int ratemask; TYPE_2__** stats; } ;
struct TYPE_8__ {int ni_flags; } ;
struct ath_node {TYPE_3__ an_node; } ;
struct TYPE_9__ {TYPE_1__* info; } ;
struct TYPE_7__ {int average_tx_time; scalar_t__ total_packets; int ewma_pct; int successive_failures; int /*<<< orphan*/  packets_acked; } ;
struct TYPE_6__ {scalar_t__ phy; } ;
typedef  TYPE_4__ HAL_RATE_TABLE ;

/* Variables and functions */
 struct sample_node* ATH_NODE_SAMPLE (struct ath_node*) ; 
 int IEEE80211_NODE_HT ; 
 scalar_t__ IEEE80211_T_HT ; 

__attribute__((used)) static __inline int
pick_best_rate(struct ath_node *an, const HAL_RATE_TABLE *rt,
    int size_bin, int require_acked_before)
{
	struct sample_node *sn = ATH_NODE_SAMPLE(an);
        int best_rate_rix, best_rate_tt, best_rate_pct;
	uint64_t mask;
	int rix, tt, pct;

        best_rate_rix = 0;
        best_rate_tt = 0;
	best_rate_pct = 0;
	for (mask = sn->ratemask, rix = 0; mask != 0; mask >>= 1, rix++) {
		if ((mask & 1) == 0)		/* not a supported rate */
			continue;

		/* Don't pick a non-HT rate for a HT node */
		if ((an->an_node.ni_flags & IEEE80211_NODE_HT) &&
		    (rt->info[rix].phy != IEEE80211_T_HT)) {
			continue;
		}

		tt = sn->stats[size_bin][rix].average_tx_time;
		if (tt <= 0 ||
		    (require_acked_before &&
		     !sn->stats[size_bin][rix].packets_acked))
			continue;

		/* Calculate percentage if possible */
		if (sn->stats[size_bin][rix].total_packets > 0) {
			pct = sn->stats[size_bin][rix].ewma_pct;
		} else {
			/* XXX for now, assume 95% ok */
			pct = 95;
		}

		/* don't use a bit-rate that has been failing */
		if (sn->stats[size_bin][rix].successive_failures > 3)
			continue;

		/*
		 * For HT, Don't use a bit rate that is much more
		 * lossy than the best.
		 *
		 * XXX this isn't optimal; it's just designed to
		 * eliminate rates that are going to be obviously
		 * worse.
		 */
		if (an->an_node.ni_flags & IEEE80211_NODE_HT) {
			if (best_rate_pct > (pct + 50))
				continue;
		}

		/*
		 * For non-MCS rates, use the current average txtime for
		 * comparison.
		 */
		if (! (an->an_node.ni_flags & IEEE80211_NODE_HT)) {
			if (best_rate_tt == 0 || tt <= best_rate_tt) {
				best_rate_tt = tt;
				best_rate_rix = rix;
				best_rate_pct = pct;
			}
		}

		/*
		 * Since 2 stream rates have slightly higher TX times,
		 * allow a little bit of leeway. This should later
		 * be abstracted out and properly handled.
		 */
		if (an->an_node.ni_flags & IEEE80211_NODE_HT) {
			if (best_rate_tt == 0 || (tt * 8 <= best_rate_tt * 10)) {
				best_rate_tt = tt;
				best_rate_rix = rix;
				best_rate_pct = pct;
			}
		}
        }
        return (best_rate_tt ? best_rate_rix : -1);
}