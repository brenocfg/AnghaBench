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
struct ieee80211_ath_ie {int ath_capability; int /*<<< orphan*/  ath_defkeyix; } ;

/* Variables and functions */
 int ATHEROS_CAP_AR ; 
 int ATHEROS_CAP_BOOST ; 
 int ATHEROS_CAP_BURST ; 
 int ATHEROS_CAP_COMPRESSION ; 
 int ATHEROS_CAP_FAST_FRAME ; 
 int ATHEROS_CAP_TURBO_PRIME ; 
 int ATHEROS_CAP_WME ; 
 int ATHEROS_CAP_XR ; 
 int LE_READ_2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
printathie(const char *tag, const u_int8_t *ie, size_t ielen, int maxlen)
{

	printf("%s", tag);
	if (verbose) {
		const struct ieee80211_ath_ie *ath =
			(const struct ieee80211_ath_ie *)ie;

		printf("<");
		if (ath->ath_capability & ATHEROS_CAP_TURBO_PRIME)
			printf("DTURBO,");
		if (ath->ath_capability & ATHEROS_CAP_COMPRESSION)
			printf("COMP,");
		if (ath->ath_capability & ATHEROS_CAP_FAST_FRAME)
			printf("FF,");
		if (ath->ath_capability & ATHEROS_CAP_XR)
			printf("XR,");
		if (ath->ath_capability & ATHEROS_CAP_AR)
			printf("AR,");
		if (ath->ath_capability & ATHEROS_CAP_BURST)
			printf("BURST,");
		if (ath->ath_capability & ATHEROS_CAP_WME)
			printf("WME,");
		if (ath->ath_capability & ATHEROS_CAP_BOOST)
			printf("BOOST,");
		printf("0x%x>", LE_READ_2(ath->ath_defkeyix));
	}
}