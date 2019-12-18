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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  is_rx_mgtdiscard; } ;
struct ieee80211vap {TYPE_1__ iv_stats; } ;
struct ieee80211_node {int ni_mlstate; int /*<<< orphan*/  ni_mllid; int /*<<< orphan*/  ni_mlpid; struct ieee80211vap* ni_vap; } ;
struct ieee80211_meshpeer_ie {int /*<<< orphan*/  peer_llinkid; int /*<<< orphan*/  peer_linkid; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ACTION_CAT_SELF_PROT ; 
 int /*<<< orphan*/  IEEE80211_ACTION_MESHPEERING_CLOSE ; 
 int /*<<< orphan*/  IEEE80211_ACTION_MESHPEERING_CONFIRM ; 
 int /*<<< orphan*/  IEEE80211_DISCARD (struct ieee80211vap*,int,struct ieee80211_frame const*,int /*<<< orphan*/ *,char*,int) ; 
 int IEEE80211_MSG_ACTION ; 
 int IEEE80211_MSG_MESH ; 
#define  IEEE80211_NODE_MESH_CONFIRMRCV 131 
 int const IEEE80211_NODE_MESH_ESTABLISHED ; 
#define  IEEE80211_NODE_MESH_HOLDING 130 
#define  IEEE80211_NODE_MESH_OPENRCV 129 
#define  IEEE80211_NODE_MESH_OPENSNT 128 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int,struct ieee80211_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_REASON_PEER_LINK_CANCELED ; 
 int /*<<< orphan*/  ieee80211_send_action (struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_linkchange (struct ieee80211_node*,int const) ; 
 struct ieee80211_meshpeer_ie* mesh_parse_meshpeering_action (struct ieee80211_node*,struct ieee80211_frame const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct ieee80211_meshpeer_ie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_peer_timeout_setup (struct ieee80211_node*) ; 
 int /*<<< orphan*/  mesh_peer_timeout_stop (struct ieee80211_node*) ; 

__attribute__((used)) static int
mesh_recv_action_meshpeering_confirm(struct ieee80211_node *ni,
	const struct ieee80211_frame *wh,
	const uint8_t *frm, const uint8_t *efrm)
{
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211_meshpeer_ie ie;
	const struct ieee80211_meshpeer_ie *meshpeer;
	uint16_t args[3];

	/* +2+2+2+2 for action + code + capabilites + status code + AID */
	meshpeer = mesh_parse_meshpeering_action(ni, wh, frm+2+2+2+2, efrm, &ie,
	    IEEE80211_ACTION_MESHPEERING_CONFIRM);
	if (meshpeer == NULL) {
		return 0;
	}

	IEEE80211_NOTE(vap, IEEE80211_MSG_ACTION | IEEE80211_MSG_MESH, ni,
	    "recv PEER CONFIRM, local id 0x%x, peer id 0x%x",
	    meshpeer->peer_llinkid, meshpeer->peer_linkid);

	switch (ni->ni_mlstate) {
	case IEEE80211_NODE_MESH_OPENRCV:
		mesh_linkchange(ni, IEEE80211_NODE_MESH_ESTABLISHED);
		mesh_peer_timeout_stop(ni);
		break;
	case IEEE80211_NODE_MESH_OPENSNT:
		mesh_linkchange(ni, IEEE80211_NODE_MESH_CONFIRMRCV);
		mesh_peer_timeout_setup(ni);
		break;
	case IEEE80211_NODE_MESH_HOLDING:
		args[0] = ni->ni_mlpid;
		args[1] = meshpeer->peer_llinkid;
		/* Standard not clear about what the reaason code should be */
		args[2] = IEEE80211_REASON_PEER_LINK_CANCELED;
		ieee80211_send_action(ni,
		    IEEE80211_ACTION_CAT_SELF_PROT,
		    IEEE80211_ACTION_MESHPEERING_CLOSE,
		    args);
		break;
	case IEEE80211_NODE_MESH_CONFIRMRCV:
		if (ni->ni_mllid != meshpeer->peer_llinkid) {
			args[0] = ni->ni_mlpid;
			args[1] = ni->ni_mllid;
			args[2] = IEEE80211_REASON_PEER_LINK_CANCELED;
			ieee80211_send_action(ni,
			    IEEE80211_ACTION_CAT_SELF_PROT,
			    IEEE80211_ACTION_MESHPEERING_CLOSE,
			    args);
			mesh_linkchange(ni, IEEE80211_NODE_MESH_HOLDING);
			mesh_peer_timeout_setup(ni);
		}
		break;
	default:
		IEEE80211_DISCARD(vap,
		    IEEE80211_MSG_ACTION | IEEE80211_MSG_MESH,
		    wh, NULL, "received confirm in invalid state %d",
		    ni->ni_mlstate);
		vap->iv_stats.is_rx_mgtdiscard++;
		break;
	}
	return 0;
}