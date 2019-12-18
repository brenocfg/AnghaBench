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
struct afswtch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_HTPROTMODE ; 
 int IEEE80211_PROTMODE_OFF ; 
 int IEEE80211_PROTMODE_RTSCTS ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  set80211 (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static void
set80211htprotmode(const char *val, int d, int s, const struct afswtch *rafp)
{
	int	mode;

	if (strcasecmp(val, "off") == 0) {
		mode = IEEE80211_PROTMODE_OFF;
	} else if (strncasecmp(val, "rts", 3) == 0) {
		mode = IEEE80211_PROTMODE_RTSCTS;
	} else {
		errx(1, "unknown protection mode");
	}

	set80211(s, IEEE80211_IOC_HTPROTMODE, mode, 0, NULL);
}