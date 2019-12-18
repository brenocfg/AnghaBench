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
typedef  int u_long ;
struct ieee80211_channel {int ic_flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_A ; 
 int IEEE80211_CHAN_B ; 
 int IEEE80211_CHAN_G ; 
 int IEEE80211_CHAN_HALF ; 
 int IEEE80211_CHAN_HT ; 
 int IEEE80211_CHAN_HT20 ; 
 int IEEE80211_CHAN_HT40D ; 
 int IEEE80211_CHAN_HT40U ; 
 int IEEE80211_CHAN_QUARTER ; 
 int IEEE80211_CHAN_STURBO ; 
 int IEEE80211_CHAN_TURBO ; 
 int IEEE80211_CHAN_VHT ; 
 int IEEE80211_CHAN_VHT160 ; 
 int IEEE80211_CHAN_VHT20 ; 
 int IEEE80211_CHAN_VHT40D ; 
 int IEEE80211_CHAN_VHT40U ; 
 int IEEE80211_CHAN_VHT80 ; 
 int _CHAN_HT ; 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 
 scalar_t__ isalpha (int) ; 
 scalar_t__ isupper (int) ; 
 int /*<<< orphan*/  mapchan (struct ieee80211_channel*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapfreq (struct ieee80211_channel*,int,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int strtoul (char const*,char**,int) ; 
 int tolower (int) ; 

__attribute__((used)) static int
getchannelflags(const char *val, int freq)
{
#define	_CHAN_HT	0x80000000
	const char *cp;
	int flags;
	int is_vht = 0;

	flags = 0;

	cp = strchr(val, ':');
	if (cp != NULL) {
		for (cp++; isalpha((int) *cp); cp++) {
			/* accept mixed case */
			int c = *cp;
			if (isupper(c))
				c = tolower(c);
			switch (c) {
			case 'a':		/* 802.11a */
				flags |= IEEE80211_CHAN_A;
				break;
			case 'b':		/* 802.11b */
				flags |= IEEE80211_CHAN_B;
				break;
			case 'g':		/* 802.11g */
				flags |= IEEE80211_CHAN_G;
				break;
			case 'v':		/* vht: 802.11ac */
				is_vht = 1;
				/* Fallthrough */
			case 'h':		/* ht = 802.11n */
			case 'n':		/* 802.11n */
				flags |= _CHAN_HT;	/* NB: private */
				break;
			case 'd':		/* dt = Atheros Dynamic Turbo */
				flags |= IEEE80211_CHAN_TURBO;
				break;
			case 't':		/* ht, dt, st, t */
				/* dt and unadorned t specify Dynamic Turbo */
				if ((flags & (IEEE80211_CHAN_STURBO|_CHAN_HT)) == 0)
					flags |= IEEE80211_CHAN_TURBO;
				break;
			case 's':		/* st = Atheros Static Turbo */
				flags |= IEEE80211_CHAN_STURBO;
				break;
			default:
				errx(-1, "%s: Invalid channel attribute %c\n",
				    val, *cp);
			}
		}
	}
	cp = strchr(val, '/');
	if (cp != NULL) {
		char *ep;
		u_long cw = strtoul(cp+1, &ep, 10);

		switch (cw) {
		case 5:
			flags |= IEEE80211_CHAN_QUARTER;
			break;
		case 10:
			flags |= IEEE80211_CHAN_HALF;
			break;
		case 20:
			/* NB: this may be removed below */
			flags |= IEEE80211_CHAN_HT20;
			break;
		case 40:
		case 80:
		case 160:
			/* Handle the 80/160 VHT flag */
			if (cw == 80)
				flags |= IEEE80211_CHAN_VHT80;
			else if (cw == 160)
				flags |= IEEE80211_CHAN_VHT160;

			/* Fallthrough */
			if (ep != NULL && *ep == '+')
				flags |= IEEE80211_CHAN_HT40U;
			else if (ep != NULL && *ep == '-')
				flags |= IEEE80211_CHAN_HT40D;
			break;
		default:
			errx(-1, "%s: Invalid channel width\n", val);
		}
	}

	/*
	 * Cleanup specifications.
	 */ 
	if ((flags & _CHAN_HT) == 0) {
		/*
		 * If user specified freq/20 or freq/40 quietly remove
		 * HT cw attributes depending on channel use.  To give
		 * an explicit 20/40 width for an HT channel you must
		 * indicate it is an HT channel since all HT channels
		 * are also usable for legacy operation; e.g. freq:n/40.
		 */
		flags &= ~IEEE80211_CHAN_HT;
		flags &= ~IEEE80211_CHAN_VHT;
	} else {
		/*
		 * Remove private indicator that this is an HT channel
		 * and if no explicit channel width has been given
		 * provide the default settings.
		 */
		flags &= ~_CHAN_HT;
		if ((flags & IEEE80211_CHAN_HT) == 0) {
			struct ieee80211_channel chan;
			/*
			 * Consult the channel list to see if we can use
			 * HT40+ or HT40- (if both the map routines choose).
			 */
			if (freq > 255)
				mapfreq(&chan, freq, 0);
			else
				mapchan(&chan, freq, 0);
			flags |= (chan.ic_flags & IEEE80211_CHAN_HT);
		}

		/*
		 * If VHT is enabled, then also set the VHT flag and the
		 * relevant channel up/down.
		 */
		if (is_vht && (flags & IEEE80211_CHAN_HT)) {
			/*
			 * XXX yes, maybe we should just have VHT, and reuse
			 * HT20/HT40U/HT40D
			 */
			if (flags & IEEE80211_CHAN_VHT80)
				;
			else if (flags & IEEE80211_CHAN_HT20)
				flags |= IEEE80211_CHAN_VHT20;
			else if (flags & IEEE80211_CHAN_HT40U)
				flags |= IEEE80211_CHAN_VHT40U;
			else if (flags & IEEE80211_CHAN_HT40D)
				flags |= IEEE80211_CHAN_VHT40D;
		}
	}
	return flags;
#undef _CHAN_HT
}