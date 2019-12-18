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
struct TYPE_2__ {int se_rssi; int /*<<< orphan*/  se_chan; int /*<<< orphan*/  se_capinfo; } ;
struct sta_entry {int se_fails; TYPE_1__ base; } ;
typedef  int int8_t ;

/* Variables and functions */
 int IEEE80211_CAPINFO_PRIVACY ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_5GHZ (int /*<<< orphan*/ ) ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREFER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STA_RSSI_MAX ; 
 int abs (int) ; 
 int maxrate (TYPE_1__*) ; 

__attribute__((used)) static int
sta_compare(const struct sta_entry *a, const struct sta_entry *b)
{
#define	PREFER(_a,_b,_what) do {			\
	if (((_a) ^ (_b)) & (_what))			\
		return ((_a) & (_what)) ? 1 : -1;	\
} while (0)
	int maxa, maxb;
	int8_t rssia, rssib;
	int weight;

	/* privacy support */
	PREFER(a->base.se_capinfo, b->base.se_capinfo,
		IEEE80211_CAPINFO_PRIVACY);

	/* compare count of previous failures */
	weight = b->se_fails - a->se_fails;
	if (abs(weight) > 1)
		return weight;

	/*
	 * Compare rssi.  If the two are considered equivalent
	 * then fallback to other criteria.  We threshold the
	 * comparisons to avoid selecting an ap purely by rssi
	 * when both values may be good but one ap is otherwise
	 * more desirable (e.g. an 11b-only ap with stronger
	 * signal than an 11g ap).
	 */
	rssia = MIN(a->base.se_rssi, STA_RSSI_MAX);
	rssib = MIN(b->base.se_rssi, STA_RSSI_MAX);
	if (abs(rssib - rssia) < 5) {
		/* best/max rate preferred if signal level close enough XXX */
		maxa = maxrate(&a->base);
		maxb = maxrate(&b->base);
		if (maxa != maxb)
			return maxa - maxb;
		/* XXX use freq for channel preference */
		/* for now just prefer 5Ghz band to all other bands */
		PREFER(IEEE80211_IS_CHAN_5GHZ(a->base.se_chan),
		       IEEE80211_IS_CHAN_5GHZ(b->base.se_chan), 1);
	}
	/* all things being equal, use signal level */
	return a->base.se_rssi - b->base.se_rssi;
#undef PREFER
}