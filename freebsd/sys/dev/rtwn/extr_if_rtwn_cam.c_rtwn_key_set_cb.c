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
struct ieee80211_key {int dummy; } ;
union sec_param {struct ieee80211_key key; } ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtwn_key_set_cb0 (struct rtwn_softc*,struct ieee80211_key const*) ; 

__attribute__((used)) static void
rtwn_key_set_cb(struct rtwn_softc *sc, union sec_param *data)
{
	const struct ieee80211_key *k = &data->key;

	(void) rtwn_key_set_cb0(sc, k);
}