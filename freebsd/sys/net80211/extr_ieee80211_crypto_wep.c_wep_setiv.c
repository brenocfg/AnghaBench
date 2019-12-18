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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct wep_ctx {int wc_iv; struct ieee80211vap* wc_vap; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211_key {struct wep_ctx* wk_private; } ;

/* Variables and functions */
 int ieee80211_crypto_get_keyid (struct ieee80211vap*,struct ieee80211_key*) ; 

__attribute__((used)) static void
wep_setiv(struct ieee80211_key *k, uint8_t *ivp)
{
	struct wep_ctx *ctx = k->wk_private;
	struct ieee80211vap *vap = ctx->wc_vap;
	uint32_t iv;
	uint8_t keyid;

	keyid = ieee80211_crypto_get_keyid(vap, k) << 6;

	/*
	 * XXX
	 * IV must not duplicate during the lifetime of the key.
	 * But no mechanism to renew keys is defined in IEEE 802.11
	 * for WEP.  And the IV may be duplicated at other stations
	 * because the session key itself is shared.  So we use a
	 * pseudo random IV for now, though it is not the right way.
	 *
	 * NB: Rather than use a strictly random IV we select a
	 * random one to start and then increment the value for
	 * each frame.  This is an explicit tradeoff between
	 * overhead and security.  Given the basic insecurity of
	 * WEP this seems worthwhile.
	 */

	/*
	 * Skip 'bad' IVs from Fluhrer/Mantin/Shamir:
	 * (B, 255, N) with 3 <= B < 16 and 0 <= N <= 255
	 */
	iv = ctx->wc_iv;
	if ((iv & 0xff00) == 0xff00) {
		int B = (iv & 0xff0000) >> 16;
		if (3 <= B && B < 16)
			iv += 0x0100;
	}
	ctx->wc_iv = iv + 1;

	/*
	 * NB: Preserve byte order of IV for packet
	 *     sniffers; it doesn't matter otherwise.
	 */
#if _BYTE_ORDER == _BIG_ENDIAN
	ivp[0] = iv >> 0;
	ivp[1] = iv >> 8;
	ivp[2] = iv >> 16;
#else
	ivp[2] = iv >> 0;
	ivp[1] = iv >> 8;
	ivp[0] = iv >> 16;
#endif
	ivp[3] = keyid;
}