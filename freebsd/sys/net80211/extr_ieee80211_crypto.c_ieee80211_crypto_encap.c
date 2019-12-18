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
struct mbuf {int dummy; } ;
struct ieee80211_node {int dummy; } ;
struct ieee80211_key {struct ieee80211_cipher* wk_cipher; } ;
struct ieee80211_cipher {scalar_t__ (* ic_encap ) (struct ieee80211_key*,struct mbuf*) ;} ;

/* Variables and functions */
 struct ieee80211_key* ieee80211_crypto_get_txkey (struct ieee80211_node*,struct mbuf*) ; 
 scalar_t__ stub1 (struct ieee80211_key*,struct mbuf*) ; 

struct ieee80211_key *
ieee80211_crypto_encap(struct ieee80211_node *ni, struct mbuf *m)
{
	struct ieee80211_key *k;
	const struct ieee80211_cipher *cip;

	if ((k = ieee80211_crypto_get_txkey(ni, m)) != NULL) {
		cip = k->wk_cipher;
		return (cip->ic_encap(k, m) ? k : NULL);
	}

	return NULL;
}