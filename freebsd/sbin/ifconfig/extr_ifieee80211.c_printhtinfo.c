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
struct ieee80211_ie_htinfo {int hi_ctrlchannel; int hi_byte1; int hi_byte2; int hi_byte3; int /*<<< orphan*/  hi_basicmcsset; int /*<<< orphan*/  hi_byte45; } ;

/* Variables and functions */
 int IEEE80211_HTRATE_MAXSIZE ; 
 int LE_READ_2 (int /*<<< orphan*/ *) ; 
 scalar_t__ isclr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
printhtinfo(const char *tag, const u_int8_t *ie, size_t ielen, int maxlen)
{
	printf("%s", tag);
	if (verbose) {
		const struct ieee80211_ie_htinfo *htinfo =
		    (const struct ieee80211_ie_htinfo *) ie;
		const char *sep;
		int i, j;

		printf("<ctl %u, %x,%x,%x,%x", htinfo->hi_ctrlchannel,
		    htinfo->hi_byte1, htinfo->hi_byte2, htinfo->hi_byte3,
		    LE_READ_2(&htinfo->hi_byte45));
		printf(" basicmcs[");
		sep = "";
		for (i = 0; i < IEEE80211_HTRATE_MAXSIZE; i++)
			if (isset(htinfo->hi_basicmcsset, i)) {
				for (j = i+1; j < IEEE80211_HTRATE_MAXSIZE; j++)
					if (isclr(htinfo->hi_basicmcsset, j))
						break;
				j--;
				if (i == j)
					printf("%s%u", sep, i);
				else
					printf("%s%u-%u", sep, i, j);
				i += j-i;
				sep = ",";
			}
		printf("]>");
	}
}