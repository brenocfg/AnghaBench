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
struct ieee80211vap {int /*<<< orphan*/  iv_def_txkey; } ;
typedef  int /*<<< orphan*/  ieee80211_keyix ;

/* Variables and functions */

__attribute__((used)) static void
default_update_deftxkey(struct ieee80211vap *vap, ieee80211_keyix kid)
{

	/* XXX assert validity */
	/* XXX assert we're in a key update block */
	vap->iv_def_txkey = kid;
}