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
struct ieee80211com {int ic_max_keyix; int /*<<< orphan*/  ic_flags_ext; int /*<<< orphan*/  ic_node_getmimoinfo; int /*<<< orphan*/  ic_node_getsignal; int /*<<< orphan*/  ic_node_getrssi; void* ic_node_drain; void* ic_node_age; int /*<<< orphan*/  ic_node_cleanup; int /*<<< orphan*/  ic_node_free; int /*<<< orphan*/  ic_node_alloc; int /*<<< orphan*/  ic_inact; int /*<<< orphan*/  ic_sta; int /*<<< orphan*/  ic_stageq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FEXT_INACT ; 
 int /*<<< orphan*/  IEEE80211_INACT_INIT ; 
 int IEEE80211_INACT_WAIT ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct ieee80211com*) ; 
 int hz ; 
 int /*<<< orphan*/  ieee80211_ageq_init (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ieee80211_node_table_init (struct ieee80211com*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_node_timeout ; 
 void* node_age ; 
 int /*<<< orphan*/  node_alloc ; 
 int /*<<< orphan*/  node_cleanup ; 
 int /*<<< orphan*/  node_free ; 
 int /*<<< orphan*/  node_getmimoinfo ; 
 int /*<<< orphan*/  node_getrssi ; 
 int /*<<< orphan*/  node_getsignal ; 

void
ieee80211_node_attach(struct ieee80211com *ic)
{
	/* XXX really want maxlen enforced per-sta */
	ieee80211_ageq_init(&ic->ic_stageq, ic->ic_max_keyix * 8,
	    "802.11 staging q");
	ieee80211_node_table_init(ic, &ic->ic_sta, "station",
		IEEE80211_INACT_INIT, ic->ic_max_keyix);
	callout_init(&ic->ic_inact, 1);
	callout_reset(&ic->ic_inact, IEEE80211_INACT_WAIT*hz,
		ieee80211_node_timeout, ic);

	ic->ic_node_alloc = node_alloc;
	ic->ic_node_free = node_free;
	ic->ic_node_cleanup = node_cleanup;
	ic->ic_node_age = node_age;
	ic->ic_node_drain = node_age;		/* NB: same as age */
	ic->ic_node_getrssi = node_getrssi;
	ic->ic_node_getsignal = node_getsignal;
	ic->ic_node_getmimoinfo = node_getmimoinfo;

	/*
	 * Set flags to be propagated to all vap's;
	 * these define default behaviour/configuration.
	 */
	ic->ic_flags_ext |= IEEE80211_FEXT_INACT; /* inactivity processing */
}