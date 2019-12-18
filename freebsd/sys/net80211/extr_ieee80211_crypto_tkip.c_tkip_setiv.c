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
struct tkip_ctx {struct ieee80211vap* tc_vap; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211_key {int wk_keytsc; struct tkip_ctx* wk_private; } ;

/* Variables and functions */
 int IEEE80211_WEP_EXTIV ; 
 int ieee80211_crypto_get_keyid (struct ieee80211vap*,struct ieee80211_key*) ; 

__attribute__((used)) static void
tkip_setiv(struct ieee80211_key *k, uint8_t *ivp)
{
	struct tkip_ctx *ctx = k->wk_private;
	struct ieee80211vap *vap = ctx->tc_vap;
	uint8_t keyid;

	keyid = ieee80211_crypto_get_keyid(vap, k) << 6;

	k->wk_keytsc++;
	ivp[0] = k->wk_keytsc >> 8;		/* TSC1 */
	ivp[1] = (ivp[0] | 0x20) & 0x7f;	/* WEP seed */
	ivp[2] = k->wk_keytsc >> 0;		/* TSC0 */
	ivp[3] = keyid | IEEE80211_WEP_EXTIV;	/* KeyID | ExtID */
	ivp[4] = k->wk_keytsc >> 16;		/* TSC2 */
	ivp[5] = k->wk_keytsc >> 24;		/* TSC3 */
	ivp[6] = k->wk_keytsc >> 32;		/* TSC4 */
	ivp[7] = k->wk_keytsc >> 40;		/* TSC5 */
}