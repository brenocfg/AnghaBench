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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
struct rum_softc {int dummy; } ;
struct ieee80211vap {struct ieee80211_key const* iv_nw_keys; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;
struct ieee80211_key {int wk_flags; scalar_t__ wk_keyix; int /*<<< orphan*/  wk_keylen; TYPE_1__* wk_cipher; } ;
struct TYPE_2__ {scalar_t__ ic_cipher; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_CIPHER_TKIP ; 
 int IEEE80211_KEY_SWCRYPT ; 
 size_t IEEE80211_WEP_NKID ; 
 scalar_t__ RT2573_SKEY_MAX ; 
 int /*<<< orphan*/  RT2573_TX_CIP_MODE (scalar_t__) ; 
 int /*<<< orphan*/  RT2573_TX_KEY_ID (scalar_t__) ; 
 int /*<<< orphan*/  RT2573_TX_KEY_PAIR ; 
 int /*<<< orphan*/  RT2573_TX_TKIPMIC ; 
 scalar_t__ rum_crypto_mode (struct rum_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
rum_tx_crypto_flags(struct rum_softc *sc, struct ieee80211_node *ni, 
    const struct ieee80211_key *k)
{
	struct ieee80211vap *vap = ni->ni_vap;
	u_int cipher;
	uint32_t flags = 0;
	uint8_t mode, pos;

	if (!(k->wk_flags & IEEE80211_KEY_SWCRYPT)) {
		cipher = k->wk_cipher->ic_cipher;
		pos = k->wk_keyix;
		mode = rum_crypto_mode(sc, cipher, k->wk_keylen);
		if (mode == 0)
			return 0;

		flags |= RT2573_TX_CIP_MODE(mode);

		/* Do not trust GROUP flag */
		if (!(k >= &vap->iv_nw_keys[0] &&
		      k < &vap->iv_nw_keys[IEEE80211_WEP_NKID]))
			flags |= RT2573_TX_KEY_PAIR;
		else
			pos += 0 * RT2573_SKEY_MAX;	/* vap id */

		flags |= RT2573_TX_KEY_ID(pos);

		if (cipher == IEEE80211_CIPHER_TKIP)
			flags |= RT2573_TX_TKIPMIC;
	}

	return flags;
}