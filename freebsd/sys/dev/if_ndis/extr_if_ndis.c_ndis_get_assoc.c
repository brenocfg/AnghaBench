#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ieee80211com {scalar_t__ ic_opmode; int /*<<< orphan*/  ic_vaps; } ;
struct ndis_softc {int /*<<< orphan*/  ndis_dev; int /*<<< orphan*/  ndis_link; struct ieee80211com ndis_ic; } ;
struct ieee80211vap {struct ieee80211_node* iv_bss; } ;
struct ieee80211_node {int ni_associd; } ;
struct TYPE_7__ {int nwbx_len; int /*<<< orphan*/  nwbx_macaddr; } ;
typedef  TYPE_1__ ndis_wlan_bssid_ex ;
typedef  int /*<<< orphan*/  ndis_80211_macaddr ;
struct TYPE_8__ {int nblx_items; int /*<<< orphan*/ * nblx_bssid; } ;
typedef  TYPE_2__ ndis_80211_bssid_list_ex ;
typedef  int /*<<< orphan*/  bssid ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ IEEE80211_M_STA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  OID_802_11_BSSID ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ndis_get_bssid_list (struct ndis_softc*,TYPE_2__**) ; 
 int ndis_get_info (struct ndis_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
ndis_get_assoc(struct ndis_softc *sc, ndis_wlan_bssid_ex **assoc)
{
	struct ieee80211com *ic = &sc->ndis_ic;
	struct ieee80211vap     *vap;
	struct ieee80211_node   *ni;
	ndis_80211_bssid_list_ex	*bl;
	ndis_wlan_bssid_ex	*bs;
	ndis_80211_macaddr	bssid;
	int			i, len, error;

	if (!sc->ndis_link)
		return (ENOENT);

	len = sizeof(bssid);
	error = ndis_get_info(sc, OID_802_11_BSSID, &bssid, &len);
	if (error) {
		device_printf(sc->ndis_dev, "failed to get bssid\n");
		return (ENOENT);
	}

	vap = TAILQ_FIRST(&ic->ic_vaps);
	ni = vap->iv_bss;

	error = ndis_get_bssid_list(sc, &bl);
	if (error)
		return (error);

	bs = (ndis_wlan_bssid_ex *)&bl->nblx_bssid[0];
	for (i = 0; i < bl->nblx_items; i++) {
		if (bcmp(bs->nwbx_macaddr, bssid, sizeof(bssid)) == 0) {
			*assoc = malloc(bs->nwbx_len, M_TEMP, M_NOWAIT);
			if (*assoc == NULL) {
				free(bl, M_TEMP);
				return (ENOMEM);
			}
			bcopy((char *)bs, (char *)*assoc, bs->nwbx_len);
			free(bl, M_TEMP);
			if (ic->ic_opmode == IEEE80211_M_STA)
				ni->ni_associd = 1 | 0xc000; /* fake associd */
			return (0);
		}
		bs = (ndis_wlan_bssid_ex *)((char *)bs + bs->nwbx_len);
	}

	free(bl, M_TEMP);
	return (ENOENT);
}