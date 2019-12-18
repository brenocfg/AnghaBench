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
struct ieee80211req_chanlist {int /*<<< orphan*/  ic_channels; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  chanlist ;

/* Variables and functions */
 int IEEE80211_CHAN_MAX ; 
 int /*<<< orphan*/  IEEE80211_IOC_CHANLIST ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isdigit (int) ; 
 scalar_t__ isspace (int) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ieee80211req_chanlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set80211 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ieee80211req_chanlist*) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,int*,int*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
set80211chanlist(const char *val, int d, int s, const struct afswtch *rafp)
{
	struct ieee80211req_chanlist chanlist;
	char *temp, *cp, *tp;

	temp = malloc(strlen(val) + 1);
	if (temp == NULL)
		errx(1, "malloc failed");
	strcpy(temp, val);
	memset(&chanlist, 0, sizeof(chanlist));
	cp = temp;
	for (;;) {
		int first, last, f, c;

		tp = strchr(cp, ',');
		if (tp != NULL)
			*tp++ = '\0';
		switch (sscanf(cp, "%u-%u", &first, &last)) {
		case 1:
			if (first > IEEE80211_CHAN_MAX)
				errx(-1, "channel %u out of range, max %u",
					first, IEEE80211_CHAN_MAX);
			setbit(chanlist.ic_channels, first);
			break;
		case 2:
			if (first > IEEE80211_CHAN_MAX)
				errx(-1, "channel %u out of range, max %u",
					first, IEEE80211_CHAN_MAX);
			if (last > IEEE80211_CHAN_MAX)
				errx(-1, "channel %u out of range, max %u",
					last, IEEE80211_CHAN_MAX);
			if (first > last)
				errx(-1, "void channel range, %u > %u",
					first, last);
			for (f = first; f <= last; f++)
				setbit(chanlist.ic_channels, f);
			break;
		}
		if (tp == NULL)
			break;
		c = *tp;
		while (isspace(c))
			tp++;
		if (!isdigit(c))
			break;
		cp = tp;
	}
	set80211(s, IEEE80211_IOC_CHANLIST, 0, sizeof(chanlist), &chanlist);
	free(temp);
}