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
 int /*<<< orphan*/  IEEE80211_IOC_POWERSAVE ; 
 int IEEE80211_POWERSAVE_CAM ; 
 int IEEE80211_POWERSAVE_OFF ; 
 int IEEE80211_POWERSAVE_ON ; 
 int IEEE80211_POWERSAVE_PSP ; 
 int IEEE80211_POWERSAVE_PSP_CAM ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  set80211 (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static void
set80211powersavemode(const char *val, int d, int s, const struct afswtch *rafp)
{
	int	mode;

	if (strcasecmp(val, "off") == 0) {
		mode = IEEE80211_POWERSAVE_OFF;
	} else if (strcasecmp(val, "on") == 0) {
		mode = IEEE80211_POWERSAVE_ON;
	} else if (strcasecmp(val, "cam") == 0) {
		mode = IEEE80211_POWERSAVE_CAM;
	} else if (strcasecmp(val, "psp") == 0) {
		mode = IEEE80211_POWERSAVE_PSP;
	} else if (strcasecmp(val, "psp-cam") == 0) {
		mode = IEEE80211_POWERSAVE_PSP_CAM;
	} else {
		errx(1, "unknown powersavemode");
	}

	set80211(s, IEEE80211_IOC_POWERSAVE, mode, 0, NULL);
}