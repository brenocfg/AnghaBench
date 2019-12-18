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

/* Variables and functions */
 int IEEE80211_CHAN_A ; 
 int IEEE80211_CHAN_B ; 
 int IEEE80211_CHAN_G ; 
 int IEEE80211_CHAN_HALF ; 
 int IEEE80211_CHAN_HT ; 
 int IEEE80211_CHAN_QUARTER ; 
 int IEEE80211_CHAN_STURBO ; 
 int IEEE80211_CHAN_TURBO ; 
 int IEEE80211_CHAN_VHT ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char const) ; 
 scalar_t__ isalpha (int) ; 
 scalar_t__ isupper (int) ; 
 char* strchr (char const*,char) ; 
 int tolower (int) ; 

__attribute__((used)) static int
getmodeflags(const char *val)
{
	const char *cp;
	int flags;

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
			case 'n':		/* 802.11n */
				flags |= IEEE80211_CHAN_HT;
				break;
			case 'd':		/* dt = Atheros Dynamic Turbo */
				flags |= IEEE80211_CHAN_TURBO;
				break;
			case 't':		/* ht, dt, st, t */
				/* dt and unadorned t specify Dynamic Turbo */
				if ((flags & (IEEE80211_CHAN_STURBO|IEEE80211_CHAN_HT)) == 0)
					flags |= IEEE80211_CHAN_TURBO;
				break;
			case 's':		/* st = Atheros Static Turbo */
				flags |= IEEE80211_CHAN_STURBO;
				break;
			case 'h':		/* 1/2-width channels */
				flags |= IEEE80211_CHAN_HALF;
				break;
			case 'q':		/* 1/4-width channels */
				flags |= IEEE80211_CHAN_QUARTER;
				break;
			case 'v':
				/* XXX set HT too? */
				flags |= IEEE80211_CHAN_VHT;
				break;
			default:
				errx(-1, "%s: Invalid mode attribute %c\n",
				    val, *cp);
			}
		}
	}
	return flags;
}