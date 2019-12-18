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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211_meshperr_ie {int perr_ndests; int /*<<< orphan*/  perr_ttl; int /*<<< orphan*/  perr_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDSHORT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADDWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ELEMID_MESHPERR ; 
 int IEEE80211_MESHPERR_FLAGS_AE ; 
 int /*<<< orphan*/  PERR_DADDR (int) ; 
 int PERR_DFLAGS (int) ; 
 int /*<<< orphan*/  PERR_DRCODE (int) ; 
 int /*<<< orphan*/  PERR_DSEQ (int) ; 
 int /*<<< orphan*/  PERR_EXTADDR (int) ; 

__attribute__((used)) static uint8_t *
hwmp_add_meshperr(uint8_t *frm, const struct ieee80211_meshperr_ie *perr)
{
	int i;

	*frm++ = IEEE80211_ELEMID_MESHPERR;
	*frm++ = perr->perr_len;	/* len already calculated */
	*frm++ = perr->perr_ttl;
	*frm++ = perr->perr_ndests;
	for (i = 0; i < perr->perr_ndests; i++) {
		*frm++ = PERR_DFLAGS(i);
		IEEE80211_ADDR_COPY(frm, PERR_DADDR(i));
		frm += 6;
		ADDWORD(frm, PERR_DSEQ(i));
		if (PERR_DFLAGS(i) & IEEE80211_MESHPERR_FLAGS_AE) {
			IEEE80211_ADDR_COPY(frm, PERR_EXTADDR(i));
			frm += 6;
		}
		ADDSHORT(frm, PERR_DRCODE(i));
	}
	return frm;
}