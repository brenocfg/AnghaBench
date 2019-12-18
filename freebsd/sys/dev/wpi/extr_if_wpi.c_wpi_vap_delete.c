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
struct wpi_buf {int /*<<< orphan*/ * m; } ;
struct wpi_vap {struct wpi_buf wv_bcbuf; } ;
struct ieee80211vap {int iv_opmode; } ;
typedef  enum ieee80211_opmode { ____Placeholder_ieee80211_opmode } ieee80211_opmode ;

/* Variables and functions */
 int IEEE80211_M_HOSTAP ; 
 int IEEE80211_M_IBSS ; 
 int /*<<< orphan*/  M_80211_VAP ; 
 struct wpi_vap* WPI_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  WPI_VAP_LOCK_DESTROY (struct wpi_vap*) ; 
 int /*<<< orphan*/  free (struct wpi_vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ratectl_deinit (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_vap_detach (struct ieee80211vap*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
wpi_vap_delete(struct ieee80211vap *vap)
{
	struct wpi_vap *wvp = WPI_VAP(vap);
	struct wpi_buf *bcn = &wvp->wv_bcbuf;
	enum ieee80211_opmode opmode = vap->iv_opmode;

	ieee80211_ratectl_deinit(vap);
	ieee80211_vap_detach(vap);

	if (opmode == IEEE80211_M_IBSS || opmode == IEEE80211_M_HOSTAP) {
		if (bcn->m != NULL)
			m_freem(bcn->m);

		WPI_VAP_LOCK_DESTROY(wvp);
	}

	free(wvp, M_80211_VAP);
}