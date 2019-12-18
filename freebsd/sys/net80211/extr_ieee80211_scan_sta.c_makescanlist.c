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
struct scanlist {int mode; int /*<<< orphan*/  count; int /*<<< orphan*/ * list; } ;
struct ieee80211vap {int const iv_des_mode; int iv_flags; } ;
struct ieee80211_scan_state {scalar_t__ ss_last; } ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;

/* Variables and functions */
 int IEEE80211_F_XR ; 
#define  IEEE80211_MODE_11A 129 
#define  IEEE80211_MODE_11B 128 
 int const IEEE80211_MODE_11G ; 
 int IEEE80211_MODE_11NA ; 
 int const IEEE80211_MODE_11NG ; 
 int const IEEE80211_MODE_AUTO ; 
 int IEEE80211_MODE_STURBO_A ; 
 int IEEE80211_MODE_TURBO_A ; 
 int IEEE80211_MODE_TURBO_G ; 
 int const IEEE80211_MODE_VHT_2GHZ ; 
 int IEEE80211_MODE_VHT_5GHZ ; 
 int /*<<< orphan*/  add_channels (struct ieee80211vap*,struct ieee80211_scan_state*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sweepchannels (struct ieee80211_scan_state*,struct ieee80211vap*,struct scanlist const*) ; 

__attribute__((used)) static void
makescanlist(struct ieee80211_scan_state *ss, struct ieee80211vap *vap,
	const struct scanlist table[])
{
	const struct scanlist *scan;
	enum ieee80211_phymode mode;

	ss->ss_last = 0;
	/*
	 * Use the table of ordered channels to construct the list
	 * of channels for scanning.  Any channels in the ordered
	 * list not in the master list will be discarded.
	 */
	for (scan = table; scan->list != NULL; scan++) {
		mode = scan->mode;

		switch (mode) {
		case IEEE80211_MODE_11B:
			if (vap->iv_des_mode == IEEE80211_MODE_11B)
				break;

			/*
			 * The scan table marks 2.4Ghz channels as b
			 * so if the desired mode is 11g / 11ng / 11acg,
			 * then use the 11b channel list but upgrade the mode.
			 *
			 * NB: 11b -> AUTO lets add_channels upgrade an
			 * 11b channel to 11g if available.
			 */
			if (vap->iv_des_mode == IEEE80211_MODE_AUTO ||
			    vap->iv_des_mode == IEEE80211_MODE_11G ||
			    vap->iv_des_mode == IEEE80211_MODE_11NG ||
			    vap->iv_des_mode == IEEE80211_MODE_VHT_2GHZ) {
				mode = vap->iv_des_mode;
				break;
			}

			continue;
		case IEEE80211_MODE_11A:
			/* Use 11a channel list for 11na / 11ac modes */
			if (vap->iv_des_mode == IEEE80211_MODE_11NA ||
			    vap->iv_des_mode == IEEE80211_MODE_VHT_5GHZ) {
				mode = vap->iv_des_mode;
				break;
			}

			/* FALLTHROUGH */
		default:
			/*
			 * If a desired mode was specified, scan only
			 * channels that satisfy that constraint.
			 */
			if (vap->iv_des_mode != IEEE80211_MODE_AUTO &&
			    vap->iv_des_mode != mode)
				continue;
		}

#ifdef IEEE80211_F_XR
		/* XR does not operate on turbo channels */
		if ((vap->iv_flags & IEEE80211_F_XR) &&
		    (mode == IEEE80211_MODE_TURBO_A ||
		     mode == IEEE80211_MODE_TURBO_G ||
		     mode == IEEE80211_MODE_STURBO_A))
			continue;
#endif
		/*
		 * Add the list of the channels; any that are not
		 * in the master channel list will be discarded.
		 */
		add_channels(vap, ss, mode, scan->list, scan->count);
	}

	/*
	 * Add the channels from the ic that are not present
	 * in the table.
	 */
	sweepchannels(ss, vap, table);
}