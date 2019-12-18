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
struct ieee80211_ie_htcap {int hc_param; int hc_antenna; int /*<<< orphan*/  hc_txbf; int /*<<< orphan*/  hc_extcap; int /*<<< orphan*/  hc_mcsset; int /*<<< orphan*/  hc_cap; } ;

/* Variables and functions */
 int IEEE80211_HTRATE_MAXSIZE ; 
 int LE_READ_2 (int /*<<< orphan*/ *) ; 
 int LE_READ_4 (int /*<<< orphan*/ *) ; 
 scalar_t__ isclr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
printhtcap(const char *tag, const u_int8_t *ie, size_t ielen, int maxlen)
{
	printf("%s", tag);
	if (verbose) {
		const struct ieee80211_ie_htcap *htcap =
		    (const struct ieee80211_ie_htcap *) ie;
		const char *sep;
		int i, j;

		printf("<cap 0x%x param 0x%x",
		    LE_READ_2(&htcap->hc_cap), htcap->hc_param);
		printf(" mcsset[");
		sep = "";
		for (i = 0; i < IEEE80211_HTRATE_MAXSIZE; i++)
			if (isset(htcap->hc_mcsset, i)) {
				for (j = i+1; j < IEEE80211_HTRATE_MAXSIZE; j++)
					if (isclr(htcap->hc_mcsset, j))
						break;
				j--;
				if (i == j)
					printf("%s%u", sep, i);
				else
					printf("%s%u-%u", sep, i, j);
				i += j-i;
				sep = ",";
			}
		printf("] extcap 0x%x txbf 0x%x antenna 0x%x>",
		    LE_READ_2(&htcap->hc_extcap),
		    LE_READ_4(&htcap->hc_txbf),
		    htcap->hc_antenna);
	}
}