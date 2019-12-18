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
struct ieee80211_meshgann_ie {int /*<<< orphan*/  gann_interval; int /*<<< orphan*/  gann_seq; int /*<<< orphan*/  gann_addr; int /*<<< orphan*/  gann_ttl; int /*<<< orphan*/  gann_hopcount; int /*<<< orphan*/  gann_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDSHORT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADDWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ELEMID_MESHGANN ; 
 int /*<<< orphan*/  IEEE80211_MESHGANN_BASE_SZ ; 

uint8_t *
ieee80211_add_meshgate(uint8_t *frm, struct ieee80211_meshgann_ie *ie)
{
	*frm++ = IEEE80211_ELEMID_MESHGANN; /* ie */
	*frm++ = IEEE80211_MESHGANN_BASE_SZ; /* len */
	*frm++ = ie->gann_flags;
	*frm++ = ie->gann_hopcount;
	*frm++ = ie->gann_ttl;
	IEEE80211_ADDR_COPY(frm, ie->gann_addr);
	frm += 6;
	ADDWORD(frm, ie->gann_seq);
	ADDSHORT(frm, ie->gann_interval);
	return frm;
}