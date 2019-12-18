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
struct ieee80211vap {int dummy; } ;
struct ieee80211_meshpeer_ie {scalar_t__ peer_len; scalar_t__ peer_proto; int /*<<< orphan*/  peer_rcode; int /*<<< orphan*/  peer_linkid; } ;

/* Variables and functions */
#define  IEEE80211_ACTION_MESHPEERING_CLOSE 130 
#define  IEEE80211_ACTION_MESHPEERING_CONFIRM 129 
#define  IEEE80211_ACTION_MESHPEERING_OPEN 128 
 int /*<<< orphan*/  IEEE80211_DPRINTF (struct ieee80211vap*,int,char*,scalar_t__) ; 
 scalar_t__ IEEE80211_MPM_BASE_SZ ; 
 scalar_t__ IEEE80211_MPM_MAX_SZ ; 
 scalar_t__ IEEE80211_MPPID_MPM ; 
 int IEEE80211_MSG_ACTION ; 
 int IEEE80211_MSG_MESH ; 

__attribute__((used)) static int
mesh_verify_meshpeer(struct ieee80211vap *vap, uint8_t subtype,
    const uint8_t *ie)
{
	const struct ieee80211_meshpeer_ie *meshpeer =
	    (const struct ieee80211_meshpeer_ie *) ie;

	if (meshpeer == NULL ||
	    meshpeer->peer_len < IEEE80211_MPM_BASE_SZ ||
	    meshpeer->peer_len > IEEE80211_MPM_MAX_SZ)
		return 1;
	if (meshpeer->peer_proto != IEEE80211_MPPID_MPM) {
		IEEE80211_DPRINTF(vap,
		    IEEE80211_MSG_ACTION | IEEE80211_MSG_MESH,
		    "Only MPM protocol is supported (proto: 0x%02X)",
		    meshpeer->peer_proto);
		return 1;
	}
	switch (subtype) {
	case IEEE80211_ACTION_MESHPEERING_OPEN:
		if (meshpeer->peer_len != IEEE80211_MPM_BASE_SZ)
			return 1;
		break;
	case IEEE80211_ACTION_MESHPEERING_CONFIRM:
		if (meshpeer->peer_len != IEEE80211_MPM_BASE_SZ + 2)
			return 1;
		break;
	case IEEE80211_ACTION_MESHPEERING_CLOSE:
		if (meshpeer->peer_len < IEEE80211_MPM_BASE_SZ + 2)
			return 1;
		if (meshpeer->peer_len == (IEEE80211_MPM_BASE_SZ + 2) &&
		    meshpeer->peer_linkid != 0)
			return 1;
		if (meshpeer->peer_rcode == 0)
			return 1;
		break;
	}
	return 0;
}