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
struct ieee80211_channel {int /*<<< orphan*/  ic_freq; } ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  IEEE80211_CHAN_ANY ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  getchaninfo (int) ; 
 int getchannelflags (char const*,int) ; 
 scalar_t__ isanyarg (char const*) ; 
 int /*<<< orphan*/  mapchan (struct ieee80211_channel*,int,int) ; 
 int /*<<< orphan*/  mapfreq (struct ieee80211_channel*,int,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_channel*,int /*<<< orphan*/ ,int) ; 
 int strtol (char const*,char**,int) ; 

__attribute__((used)) static void
getchannel(int s, struct ieee80211_channel *chan, const char *val)
{
	int v, flags;
	char *eptr;

	memset(chan, 0, sizeof(*chan));
	if (isanyarg(val)) {
		chan->ic_freq = IEEE80211_CHAN_ANY;
		return;
	}
	getchaninfo(s);
	errno = 0;
	v = strtol(val, &eptr, 10);
	if (val[0] == '\0' || val == eptr || errno == ERANGE ||
	    /* channel may be suffixed with nothing, :flag, or /width */
	    (eptr[0] != '\0' && eptr[0] != ':' && eptr[0] != '/'))
		errx(1, "invalid channel specification%s",
		    errno == ERANGE ? " (out of range)" : "");
	flags = getchannelflags(val, v);
	if (v > 255) {		/* treat as frequency */
		mapfreq(chan, v, flags);
	} else {
		mapchan(chan, v, flags);
	}
}