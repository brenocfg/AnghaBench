#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct mwl_softc {int (* sc_recv_action ) (struct ieee80211_node*,struct ieee80211_frame const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  sc_mh; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_macaddr; TYPE_1__* ni_ic; } ;
struct ieee80211_frame {int dummy; } ;
struct ieee80211_action_ht_mimopowersave {int am_control; } ;
struct ieee80211_action {scalar_t__ ia_category; scalar_t__ ia_action; } ;
struct TYPE_2__ {struct mwl_softc* ic_softc; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_ACTION_CAT_HT ; 
 scalar_t__ IEEE80211_ACTION_HT_MIMOPWRSAVE ; 
 int IEEE80211_A_HT_MIMOPWRSAVE_ENA ; 
 int /*<<< orphan*/  IEEE80211_A_HT_MIMOPWRSAVE_MODE ; 
 int /*<<< orphan*/  MS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl_hal_setmimops (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct ieee80211_node*,struct ieee80211_frame const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
mwl_recv_action(struct ieee80211_node *ni, const struct ieee80211_frame *wh,
	const uint8_t *frm, const uint8_t *efrm)
{
	struct mwl_softc *sc = ni->ni_ic->ic_softc;
	const struct ieee80211_action *ia;

	ia = (const struct ieee80211_action *) frm;
	if (ia->ia_category == IEEE80211_ACTION_CAT_HT &&
	    ia->ia_action == IEEE80211_ACTION_HT_MIMOPWRSAVE) {
		const struct ieee80211_action_ht_mimopowersave *mps =
		    (const struct ieee80211_action_ht_mimopowersave *) ia;

		mwl_hal_setmimops(sc->sc_mh, ni->ni_macaddr,
		    mps->am_control & IEEE80211_A_HT_MIMOPWRSAVE_ENA,
		    MS(mps->am_control, IEEE80211_A_HT_MIMOPWRSAVE_MODE));
		return 0;
	} else
		return sc->sc_recv_action(ni, wh, frm, efrm);
}