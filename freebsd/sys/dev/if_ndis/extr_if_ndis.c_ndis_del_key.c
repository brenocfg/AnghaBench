#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ndis_softc {int dummy; } ;
struct ieee80211vap {TYPE_1__* iv_ifp; TYPE_2__* iv_ic; } ;
struct ieee80211_key {int /*<<< orphan*/  wk_keyix; } ;
typedef  int /*<<< orphan*/  rkey ;
struct TYPE_7__ {int nk_len; int /*<<< orphan*/  nk_bssid; int /*<<< orphan*/  nk_keyidx; } ;
typedef  TYPE_3__ ndis_80211_key ;
struct TYPE_6__ {struct ndis_softc* ic_softc; } ;
struct TYPE_5__ {int /*<<< orphan*/  if_broadcastaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  OID_802_11_REMOVE_KEY ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int ndis_set_info (struct ndis_softc*,int /*<<< orphan*/ ,TYPE_3__*,int*) ; 

int
ndis_del_key(struct ieee80211vap *vap, const struct ieee80211_key *key)
{
	struct ndis_softc	*sc = vap->iv_ic->ic_softc;
	ndis_80211_key		rkey;
	int			len, error = 0;

	bzero((char *)&rkey, sizeof(rkey));
	len = sizeof(rkey);

	rkey.nk_len = len;
	rkey.nk_keyidx = key->wk_keyix;

	bcopy(vap->iv_ifp->if_broadcastaddr,
	    rkey.nk_bssid, IEEE80211_ADDR_LEN);

	error = ndis_set_info(sc, OID_802_11_REMOVE_KEY, &rkey, &len);

	if (error)
		return (0);

	return (1);
}