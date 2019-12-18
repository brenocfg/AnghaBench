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
typedef  int /*<<< orphan*/  u_int8_t ;
struct ieee80211_wme_info {int wme_version; int wme_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
printwmeinfo(const char *tag, const u_int8_t *ie, size_t ielen, int maxlen)
{
	printf("%s", tag);
	if (verbose) {
		const struct ieee80211_wme_info *wme =
		    (const struct ieee80211_wme_info *) ie;
		printf("<version 0x%x info 0x%x>",
		    wme->wme_version, wme->wme_info);
	}
}