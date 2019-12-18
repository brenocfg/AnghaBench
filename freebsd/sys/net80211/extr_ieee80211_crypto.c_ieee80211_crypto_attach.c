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
struct ieee80211com {int dummy; } ;

/* Variables and functions */
 size_t IEEE80211_CIPHER_NONE ; 
 int /*<<< orphan*/ ** ciphers ; 
 int /*<<< orphan*/  ieee80211_cipher_none ; 

void
ieee80211_crypto_attach(struct ieee80211com *ic)
{
	/* NB: we assume everything is pre-zero'd */
	ciphers[IEEE80211_CIPHER_NONE] = &ieee80211_cipher_none;
}