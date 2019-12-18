#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wkey ;
typedef  int u_int16_t ;
struct wi_softc {int sc_firmware_type; int sc_encryption; int sc_sta_firmware_ver; } ;
struct wi_key {int /*<<< orphan*/  wi_keydat; int /*<<< orphan*/  wi_keylen; } ;
struct ieee80211vap {int iv_flags; int iv_def_txkey; TYPE_2__* iv_bss; TYPE_1__* iv_nw_keys; } ;
struct TYPE_4__ {int ni_authmode; } ;
struct TYPE_3__ {int wk_keylen; int /*<<< orphan*/  wk_key; } ;

/* Variables and functions */
 int HOST_DECRYPT ; 
 int HOST_ENCRYPT ; 
 int IEEE80211_AUTH_OPEN ; 
 int IEEE80211_F_PRIVACY ; 
 int IEEE80211_WEP_NKID ; 
 int PRIVACY_INVOKED ; 
#define  WI_INTERSIL 129 
#define  WI_LUCENT 128 
 int /*<<< orphan*/  WI_RID_CNFAUTHMODE ; 
 int /*<<< orphan*/  WI_RID_DEFLT_CRYPT_KEYS ; 
 int /*<<< orphan*/  WI_RID_ENCRYPTION ; 
 int /*<<< orphan*/  WI_RID_P2_ENCRYPTION ; 
 int /*<<< orphan*/  WI_RID_P2_TX_CRYPT_KEY ; 
 int /*<<< orphan*/  WI_RID_PROMISC ; 
 int /*<<< orphan*/  WI_RID_TX_CRYPT_KEY ; 
 int /*<<< orphan*/  htole16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct wi_key*,int /*<<< orphan*/ ,int) ; 
 int wi_write_rid (struct wi_softc*,int /*<<< orphan*/ ,struct wi_key*,int) ; 
 int wi_write_val (struct wi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
wi_write_wep(struct wi_softc *sc, struct ieee80211vap *vap)
{
	int error = 0;
	int i, keylen;
	u_int16_t val;
	struct wi_key wkey[IEEE80211_WEP_NKID];

	switch (sc->sc_firmware_type) {
	case WI_LUCENT:
		val = (vap->iv_flags & IEEE80211_F_PRIVACY) ? 1 : 0;
		error = wi_write_val(sc, WI_RID_ENCRYPTION, val);
		if (error)
			break;
		if ((vap->iv_flags & IEEE80211_F_PRIVACY) == 0)
			break;
		error = wi_write_val(sc, WI_RID_TX_CRYPT_KEY, vap->iv_def_txkey);
		if (error)
			break;
		memset(wkey, 0, sizeof(wkey));
		for (i = 0; i < IEEE80211_WEP_NKID; i++) {
			keylen = vap->iv_nw_keys[i].wk_keylen;
			wkey[i].wi_keylen = htole16(keylen);
			memcpy(wkey[i].wi_keydat, vap->iv_nw_keys[i].wk_key,
			    keylen);
		}
		error = wi_write_rid(sc, WI_RID_DEFLT_CRYPT_KEYS,
		    wkey, sizeof(wkey));
		sc->sc_encryption = 0;
		break;

	case WI_INTERSIL:
		val = HOST_ENCRYPT | HOST_DECRYPT;
		if (vap->iv_flags & IEEE80211_F_PRIVACY) {
			/*
			 * ONLY HWB3163 EVAL-CARD Firmware version
			 * less than 0.8 variant2
			 *
			 *   If promiscuous mode disable, Prism2 chip
			 *  does not work with WEP .
			 * It is under investigation for details.
			 * (ichiro@netbsd.org)
			 */
			if (sc->sc_sta_firmware_ver < 802 ) {
				/* firm ver < 0.8 variant 2 */
				wi_write_val(sc, WI_RID_PROMISC, 1);
			}
			wi_write_val(sc, WI_RID_CNFAUTHMODE,
			    vap->iv_bss->ni_authmode);
			val |= PRIVACY_INVOKED;
		} else {
			wi_write_val(sc, WI_RID_CNFAUTHMODE, IEEE80211_AUTH_OPEN);
		}
		error = wi_write_val(sc, WI_RID_P2_ENCRYPTION, val);
		if (error)
			break;
		sc->sc_encryption = val;
		if ((val & PRIVACY_INVOKED) == 0)
			break;
		error = wi_write_val(sc, WI_RID_P2_TX_CRYPT_KEY, vap->iv_def_txkey);
		break;
	}
	return error;
}