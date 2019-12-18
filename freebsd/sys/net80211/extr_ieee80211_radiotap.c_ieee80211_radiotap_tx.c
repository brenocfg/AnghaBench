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
struct mbuf {int dummy; } ;
struct ieee80211vap {int iv_flags_ext; int /*<<< orphan*/  iv_rawbpf; struct ieee80211com* iv_ic; } ;
struct ieee80211com {scalar_t__ ic_montaps; struct ieee80211_radiotap_header* ic_th; } ;
struct ieee80211_radiotap_header {int /*<<< orphan*/  it_len; } ;

/* Variables and functions */
 int IEEE80211_FEXT_BPF ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bpf_mtap2 (int /*<<< orphan*/ ,struct ieee80211_radiotap_header*,int,struct mbuf*) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spam_vaps (struct ieee80211vap*,struct mbuf*,struct ieee80211_radiotap_header*,int) ; 

void
ieee80211_radiotap_tx(struct ieee80211vap *vap0, struct mbuf *m)
{
	struct ieee80211com *ic = vap0->iv_ic;
	struct ieee80211_radiotap_header *th = ic->ic_th;
	int len;

	KASSERT(th != NULL, ("no tx radiotap header"));
	len = le16toh(th->it_len);

	if (vap0->iv_flags_ext & IEEE80211_FEXT_BPF)
		bpf_mtap2(vap0->iv_rawbpf, th, len, m);
	/*
	 * Spam monitor mode vaps.
	 */
	if (ic->ic_montaps != 0)
		spam_vaps(vap0, m, th, len);
}