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
 int IEEE80211_RATE_MCS ; 
 int /*<<< orphan*/  LINE_CHECK (char*,char const*,int) ; 

__attribute__((used)) static void
printrate(const char *tag, int v, int defrate, int defmcs)
{
	if ((v & IEEE80211_RATE_MCS) == 0) {
		if (v != defrate) {
			if (v & 1)
				LINE_CHECK("%s %d.5", tag, v/2);
			else
				LINE_CHECK("%s %d", tag, v/2);
		}
	} else {
		if (v != defmcs)
			LINE_CHECK("%s %d", tag, v &~ 0x80);
	}
}