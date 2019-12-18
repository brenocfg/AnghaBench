#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_9__ {scalar_t__ tdma_ie; } ;
struct ieee80211_scan_entry {int se_capinfo; scalar_t__* se_meshid; scalar_t__* se_cc; int se_rssi; int /*<<< orphan*/ * se_ssid; TYPE_3__* se_chan; int /*<<< orphan*/  se_bssid; int /*<<< orphan*/  se_macaddr; TYPE_1__ se_ies; } ;
struct sta_entry {scalar_t__ se_fails; scalar_t__ se_notseen; int /*<<< orphan*/  se_flags; struct ieee80211_scan_entry base; } ;
struct ieee80211vap {size_t iv_des_mode; scalar_t__ iv_opmode; int iv_caps; int iv_flags_ext; int iv_flags; int /*<<< orphan*/  iv_des_bssid; struct ieee80211_mesh_state* iv_mesh; struct ieee80211_tdma_state* iv_tdma; struct ieee80211com* iv_ic; } ;
struct TYPE_10__ {scalar_t__ country; int /*<<< orphan*/  isocc; } ;
struct ieee80211com {TYPE_2__ ic_regdomain; int /*<<< orphan*/  ic_chan_active; } ;
struct ieee80211_tdma_state {scalar_t__ tdma_version; } ;
struct ieee80211_tdma_param {scalar_t__ tdma_version; scalar_t__ tdma_slot; } ;
struct ieee80211_scan_state {int /*<<< orphan*/  ss_ssid; int /*<<< orphan*/  ss_nssid; } ;
struct ieee80211_mesh_state {scalar_t__ ms_idlen; int /*<<< orphan*/  ms_id; } ;
struct TYPE_11__ {int ic_flags; } ;

/* Variables and functions */
 scalar_t__ CTRY_DEFAULT ; 
 int /*<<< orphan*/  IEEE80211_ADDR_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_CAPINFO_ESS ; 
 int IEEE80211_CAPINFO_IBSS ; 
 int IEEE80211_CAPINFO_PRIVACY ; 
 int IEEE80211_CHAN_ALLTURBO ; 
 int IEEE80211_C_TDMA ; 
 scalar_t__ IEEE80211_ELEMID_MESHID ; 
 int IEEE80211_FEXT_DOTD ; 
 int IEEE80211_F_DESBSSID ; 
 int IEEE80211_F_PRIVACY ; 
 scalar_t__ IEEE80211_IS_CHAN_11D (TYPE_3__*) ; 
 scalar_t__ IEEE80211_IS_CHAN_ANYG (TYPE_3__*) ; 
 size_t IEEE80211_MODE_11B ; 
 size_t IEEE80211_MODE_AUTO ; 
 scalar_t__ IEEE80211_M_AHDEMO ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 int IEEE80211_RATE_BASIC ; 
 int IEEE80211_RATE_VAL ; 
 int MATCH_BSSID ; 
 int MATCH_CAPINFO ; 
 int MATCH_CC ; 
 int MATCH_CHANNEL ; 
 int MATCH_FAILS ; 
 int MATCH_MESHID ; 
 int MATCH_MESH_NOID ; 
 int MATCH_NOTSEEN ; 
 int MATCH_PRIVACY ; 
 int MATCH_RATE ; 
 int MATCH_RSSI ; 
 int MATCH_SSID ; 
 int MATCH_TDMA_LOCAL ; 
 int MATCH_TDMA_NOIE ; 
 int MATCH_TDMA_NOSLOT ; 
 int MATCH_TDMA_NOTMASTER ; 
 int MATCH_TDMA_VERSION ; 
 int /*<<< orphan*/  STA_DEMOTE11B ; 
 scalar_t__ STA_FAILS_MAX ; 
 scalar_t__ STA_PURGE_SCANS ; 
 int STA_RSSI_MIN ; 
 int* chanflags ; 
 int check_rate (struct ieee80211vap*,TYPE_3__*,struct ieee80211_scan_entry*) ; 
 TYPE_3__* demote11b (struct ieee80211vap*,TYPE_3__*) ; 
 char* ether_sprintf (int /*<<< orphan*/ ) ; 
 int ieee80211_chan2ieee (struct ieee80211com*,TYPE_3__*) ; 
 scalar_t__ ieee80211_local_address (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_msg (struct ieee80211vap*,int) ; 
 int /*<<< orphan*/  ieee80211_print_essid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isclr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isocmp (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ match_id (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  match_ssid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ tdma_isfull (struct ieee80211_tdma_param const*) ; 

__attribute__((used)) static int
match_bss(struct ieee80211vap *vap,
	const struct ieee80211_scan_state *ss, struct sta_entry *se0,
	int debug)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_scan_entry *se = &se0->base;
        uint8_t rate;
        int fail;

	fail = 0;
	if (isclr(ic->ic_chan_active, ieee80211_chan2ieee(ic, se->se_chan)))
		fail |= MATCH_CHANNEL;
	/*
	 * NB: normally the desired mode is used to construct
	 * the channel list, but it's possible for the scan
	 * cache to include entries for stations outside this
	 * list so we check the desired mode here to weed them
	 * out.
	 */
	if (vap->iv_des_mode != IEEE80211_MODE_AUTO &&
	    (se->se_chan->ic_flags & IEEE80211_CHAN_ALLTURBO) !=
	    chanflags[vap->iv_des_mode])
		fail |= MATCH_CHANNEL;
	if (vap->iv_opmode == IEEE80211_M_IBSS) {
		if ((se->se_capinfo & IEEE80211_CAPINFO_IBSS) == 0)
			fail |= MATCH_CAPINFO;
#ifdef IEEE80211_SUPPORT_TDMA
	} else if (vap->iv_opmode == IEEE80211_M_AHDEMO) {
		/*
		 * Adhoc demo network setup shouldn't really be scanning
		 * but just in case skip stations operating in IBSS or
		 * BSS mode.
		 */
		if (se->se_capinfo & (IEEE80211_CAPINFO_IBSS|IEEE80211_CAPINFO_ESS))
			fail |= MATCH_CAPINFO;
		/*
		 * TDMA operation cannot coexist with a normal 802.11 network;
		 * skip if IBSS or ESS capabilities are marked and require
		 * the beacon have a TDMA ie present.
		 */
		if (vap->iv_caps & IEEE80211_C_TDMA) {
			const struct ieee80211_tdma_param *tdma =
			    (const struct ieee80211_tdma_param *)se->se_ies.tdma_ie;
			const struct ieee80211_tdma_state *ts = vap->iv_tdma;

			if (tdma == NULL)
				fail |= MATCH_TDMA_NOIE;
			else if (tdma->tdma_version != ts->tdma_version)
				fail |= MATCH_TDMA_VERSION;
			else if (tdma->tdma_slot != 0)
				fail |= MATCH_TDMA_NOTMASTER;
			else if (tdma_isfull(tdma))
				fail |= MATCH_TDMA_NOSLOT;
#if 0
			else if (ieee80211_local_address(se->se_macaddr))
				fail |= MATCH_TDMA_LOCAL;
#endif
		}
#endif /* IEEE80211_SUPPORT_TDMA */
#ifdef IEEE80211_SUPPORT_MESH
	} else if (vap->iv_opmode == IEEE80211_M_MBSS) {
		const struct ieee80211_mesh_state *ms = vap->iv_mesh;
		/*
		 * Mesh nodes have IBSS & ESS bits in capinfo turned off
		 * and two special ie's that must be present.
		 */
		if (se->se_capinfo & (IEEE80211_CAPINFO_IBSS|IEEE80211_CAPINFO_ESS))
			fail |= MATCH_CAPINFO;
		else if (se->se_meshid[0] != IEEE80211_ELEMID_MESHID)
			fail |= MATCH_MESH_NOID;
		else if (ms->ms_idlen != 0 &&
		    match_id(se->se_meshid, ms->ms_id, ms->ms_idlen))
			fail |= MATCH_MESHID;
#endif
	} else {
		if ((se->se_capinfo & IEEE80211_CAPINFO_ESS) == 0)
			fail |= MATCH_CAPINFO;
		/*
		 * If 11d is enabled and we're attempting to join a bss
		 * that advertises it's country code then compare our
		 * current settings to what we fetched from the country ie.
		 * If our country code is unspecified or different then do
		 * not attempt to join the bss.  We should have already
		 * dispatched an event to user space that identifies the
		 * new country code so our regdomain config should match.
		 */
		if ((IEEE80211_IS_CHAN_11D(se->se_chan) ||
		    (vap->iv_flags_ext & IEEE80211_FEXT_DOTD)) &&
		    se->se_cc[0] != 0 &&
		    (ic->ic_regdomain.country == CTRY_DEFAULT ||
		     !isocmp(se->se_cc, ic->ic_regdomain.isocc)))
			fail |= MATCH_CC;
	}
	if (vap->iv_flags & IEEE80211_F_PRIVACY) {
		if ((se->se_capinfo & IEEE80211_CAPINFO_PRIVACY) == 0)
			fail |= MATCH_PRIVACY;
	} else {
		/* XXX does this mean privacy is supported or required? */
		if (se->se_capinfo & IEEE80211_CAPINFO_PRIVACY)
			fail |= MATCH_PRIVACY;
	}
	se0->se_flags &= ~STA_DEMOTE11B;
	rate = check_rate(vap, se->se_chan, se);
	if (rate & IEEE80211_RATE_BASIC) {
		fail |= MATCH_RATE;
		/*
		 * An 11b-only ap will give a rate mismatch if there is an
		 * OFDM fixed tx rate for 11g.  Try downgrading the channel
		 * in the scan list to 11b and retry the rate check.
		 */
		if (IEEE80211_IS_CHAN_ANYG(se->se_chan)) {
			rate = check_rate(vap, demote11b(vap, se->se_chan), se);
			if ((rate & IEEE80211_RATE_BASIC) == 0) {
				fail &= ~MATCH_RATE;
				se0->se_flags |= STA_DEMOTE11B;
			}
		}
	} else if (rate < 2*24) {
		/*
		 * This is an 11b-only ap.  Check the desired mode in
		 * case that needs to be honored (mode 11g filters out
		 * 11b-only ap's).  Otherwise force any 11g channel used
		 * in scanning to be demoted.
		 *
		 * NB: we cheat a bit here by looking at the max rate;
		 *     we could/should check the rates.
		 */
		if (!(vap->iv_des_mode == IEEE80211_MODE_AUTO ||
		      vap->iv_des_mode == IEEE80211_MODE_11B))
			fail |= MATCH_RATE;
		else
			se0->se_flags |= STA_DEMOTE11B;
	}
	if (ss->ss_nssid != 0 &&
	    !match_ssid(se->se_ssid, ss->ss_nssid, ss->ss_ssid))
		fail |= MATCH_SSID;
	if ((vap->iv_flags & IEEE80211_F_DESBSSID) &&
	    !IEEE80211_ADDR_EQ(vap->iv_des_bssid, se->se_bssid))
		fail |= MATCH_BSSID;
	if (se0->se_fails >= STA_FAILS_MAX)
		fail |= MATCH_FAILS;
	if (se0->se_notseen >= STA_PURGE_SCANS)
		fail |= MATCH_NOTSEEN;
	if (se->se_rssi < STA_RSSI_MIN)
		fail |= MATCH_RSSI;
#ifdef IEEE80211_DEBUG
	if (ieee80211_msg(vap, debug)) {
		printf(" %c %s",
		    fail & MATCH_FAILS ? '=' :
		    fail & MATCH_NOTSEEN ? '^' :
		    fail & MATCH_CC ? '$' :
#ifdef IEEE80211_SUPPORT_TDMA
		    fail & MATCH_TDMA_NOIE ? '&' :
		    fail & MATCH_TDMA_VERSION ? 'v' :
		    fail & MATCH_TDMA_NOTMASTER ? 's' :
		    fail & MATCH_TDMA_NOSLOT ? 'f' :
		    fail & MATCH_TDMA_LOCAL ? 'l' :
#endif
		    fail & MATCH_MESH_NOID ? 'm' :
		    fail ? '-' : '+', ether_sprintf(se->se_macaddr));
		printf(" %s%c", ether_sprintf(se->se_bssid),
		    fail & MATCH_BSSID ? '!' : ' ');
		printf(" %3d%c", ieee80211_chan2ieee(ic, se->se_chan),
			fail & MATCH_CHANNEL ? '!' : ' ');
		printf(" %+4d%c", se->se_rssi, fail & MATCH_RSSI ? '!' : ' ');
		printf(" %2dM%c", (rate & IEEE80211_RATE_VAL) / 2,
		    fail & MATCH_RATE ? '!' : ' ');
		printf(" %4s%c",
		    (se->se_capinfo & IEEE80211_CAPINFO_ESS) ? "ess" :
		    (se->se_capinfo & IEEE80211_CAPINFO_IBSS) ? "ibss" : "",
		    fail & MATCH_CAPINFO ? '!' : ' ');
		printf(" %3s%c ",
		    (se->se_capinfo & IEEE80211_CAPINFO_PRIVACY) ?
		    "wep" : "no",
		    fail & MATCH_PRIVACY ? '!' : ' ');
		ieee80211_print_essid(se->se_ssid+2, se->se_ssid[1]);
		printf("%s\n", fail & (MATCH_SSID | MATCH_MESHID) ? "!" : "");
	}
#endif
	return fail;
}