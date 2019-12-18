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
struct ieee80211vap {int /*<<< orphan*/  iv_rawbpf; int /*<<< orphan*/  iv_ifp; struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/ * ic_rh; struct ieee80211_radiotap_header* ic_th; } ;
struct ieee80211_radiotap_header {int /*<<< orphan*/  it_len; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_IEEE802_11_RADIO ; 
 int /*<<< orphan*/  bpfattach2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ le16toh (int /*<<< orphan*/ ) ; 

void
ieee80211_radiotap_vattach(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_radiotap_header *th = ic->ic_th;

	if (th != NULL && ic->ic_rh != NULL) {
		/* radiotap DLT for raw 802.11 frames */
		bpfattach2(vap->iv_ifp, DLT_IEEE802_11_RADIO,
		    sizeof(struct ieee80211_frame) + le16toh(th->it_len),
		    &vap->iv_rawbpf);
	}
}