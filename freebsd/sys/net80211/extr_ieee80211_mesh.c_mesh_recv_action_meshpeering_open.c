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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ieee80211vap {struct ieee80211_mesh_state* iv_mesh; } ;
struct ieee80211_node {int ni_mlstate; int /*<<< orphan*/  ni_mlpid; int /*<<< orphan*/  ni_mllid; struct ieee80211vap* ni_vap; } ;
struct ieee80211_meshpeer_ie {int /*<<< orphan*/  peer_llinkid; int /*<<< orphan*/  peer_linkid; } ;
struct ieee80211_mesh_state {int /*<<< orphan*/  ms_neighbors; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ACTION_CAT_SELF_PROT ; 
 int /*<<< orphan*/  IEEE80211_ACTION_MESHPEERING_CLOSE ; 
 int /*<<< orphan*/  IEEE80211_ACTION_MESHPEERING_CONFIRM ; 
 int /*<<< orphan*/  IEEE80211_ACTION_MESHPEERING_OPEN ; 
 int /*<<< orphan*/  IEEE80211_MESH_MAX_NEIGHBORS ; 
 int IEEE80211_MSG_ACTION ; 
 int IEEE80211_MSG_MESH ; 
#define  IEEE80211_NODE_MESH_CONFIRMRCV 133 
#define  IEEE80211_NODE_MESH_ESTABLISHED 132 
#define  IEEE80211_NODE_MESH_HOLDING 131 
#define  IEEE80211_NODE_MESH_IDLE 130 
#define  IEEE80211_NODE_MESH_OPENRCV 129 
#define  IEEE80211_NODE_MESH_OPENSNT 128 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int,struct ieee80211_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_REASON_MESH_MAX_PEERS ; 
 int /*<<< orphan*/  IEEE80211_REASON_PEER_LINK_CANCELED ; 
 int /*<<< orphan*/  ieee80211_send_action (struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_generateid (struct ieee80211vap*) ; 
 int /*<<< orphan*/  mesh_linkchange (struct ieee80211_node*,int const) ; 
 struct ieee80211_meshpeer_ie* mesh_parse_meshpeering_action (struct ieee80211_node*,struct ieee80211_frame const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct ieee80211_meshpeer_ie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_peer_timeout_setup (struct ieee80211_node*) ; 
 int /*<<< orphan*/  mesh_peer_timeout_stop (struct ieee80211_node*) ; 

__attribute__((used)) static int
mesh_recv_action_meshpeering_open(struct ieee80211_node *ni,
	const struct ieee80211_frame *wh,
	const uint8_t *frm, const uint8_t *efrm)
{
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211_mesh_state *ms = vap->iv_mesh;
	struct ieee80211_meshpeer_ie ie;
	const struct ieee80211_meshpeer_ie *meshpeer;
	uint16_t args[3];

	/* +2+2 for action + code + capabilites */
	meshpeer = mesh_parse_meshpeering_action(ni, wh, frm+2+2, efrm, &ie,
	    IEEE80211_ACTION_MESHPEERING_OPEN);
	if (meshpeer == NULL) {
		return 0;
	}

	/* XXX move up */
	IEEE80211_NOTE(vap, IEEE80211_MSG_ACTION | IEEE80211_MSG_MESH, ni,
	    "recv PEER OPEN, lid 0x%x", meshpeer->peer_llinkid);

	switch (ni->ni_mlstate) {
	case IEEE80211_NODE_MESH_IDLE:
		/* Reject open request if reached our maximum neighbor count */
		if (ms->ms_neighbors >= IEEE80211_MESH_MAX_NEIGHBORS) {
			args[0] = meshpeer->peer_llinkid;
			args[1] = 0;
			args[2] = IEEE80211_REASON_MESH_MAX_PEERS;
			ieee80211_send_action(ni,
			    IEEE80211_ACTION_CAT_SELF_PROT,
			    IEEE80211_ACTION_MESHPEERING_CLOSE,
			    args);
			/* stay in IDLE state */
			return (0);
		}
		/* Open frame accepted */
		mesh_linkchange(ni, IEEE80211_NODE_MESH_OPENRCV);
		ni->ni_mllid = meshpeer->peer_llinkid;
		ni->ni_mlpid = mesh_generateid(vap);
		if (ni->ni_mlpid == 0)
			return 0;		/* XXX */
		args[0] = ni->ni_mlpid;
		/* Announce we're open too... */
		ieee80211_send_action(ni,
		    IEEE80211_ACTION_CAT_SELF_PROT,
		    IEEE80211_ACTION_MESHPEERING_OPEN, args);
		/* ...and confirm the link. */
		args[0] = ni->ni_mlpid;
		args[1] = ni->ni_mllid;
		ieee80211_send_action(ni,
		    IEEE80211_ACTION_CAT_SELF_PROT,
		    IEEE80211_ACTION_MESHPEERING_CONFIRM,
		    args);
		mesh_peer_timeout_setup(ni);
		break;
	case IEEE80211_NODE_MESH_OPENRCV:
		/* Wrong Link ID */
		if (ni->ni_mllid != meshpeer->peer_llinkid) {
			args[0] = ni->ni_mllid;
			args[1] = ni->ni_mlpid;
			args[2] = IEEE80211_REASON_PEER_LINK_CANCELED;
			ieee80211_send_action(ni,
			    IEEE80211_ACTION_CAT_SELF_PROT,
			    IEEE80211_ACTION_MESHPEERING_CLOSE,
			    args);
			mesh_linkchange(ni, IEEE80211_NODE_MESH_HOLDING);
			mesh_peer_timeout_setup(ni);
			break;
		}
		/* Duplicate open, confirm again. */
		args[0] = ni->ni_mlpid;
		args[1] = ni->ni_mllid;
		ieee80211_send_action(ni,
		    IEEE80211_ACTION_CAT_SELF_PROT,
		    IEEE80211_ACTION_MESHPEERING_CONFIRM,
		    args);
		break;
	case IEEE80211_NODE_MESH_OPENSNT:
		ni->ni_mllid = meshpeer->peer_llinkid;
		mesh_linkchange(ni, IEEE80211_NODE_MESH_OPENRCV);
		args[0] = ni->ni_mlpid;
		args[1] = ni->ni_mllid;
		ieee80211_send_action(ni,
		    IEEE80211_ACTION_CAT_SELF_PROT,
		    IEEE80211_ACTION_MESHPEERING_CONFIRM,
		    args);
		/* NB: don't setup/clear any timeout */
		break;
	case IEEE80211_NODE_MESH_CONFIRMRCV:
		if (ni->ni_mlpid != meshpeer->peer_linkid ||
		    ni->ni_mllid != meshpeer->peer_llinkid) {
			args[0] = ni->ni_mlpid;
			args[1] = ni->ni_mllid;
			args[2] = IEEE80211_REASON_PEER_LINK_CANCELED;
			ieee80211_send_action(ni,
			    IEEE80211_ACTION_CAT_SELF_PROT,
			    IEEE80211_ACTION_MESHPEERING_CLOSE,
			    args);
			mesh_linkchange(ni,
			    IEEE80211_NODE_MESH_HOLDING);
			mesh_peer_timeout_setup(ni);
			break;
		}
		mesh_linkchange(ni, IEEE80211_NODE_MESH_ESTABLISHED);
		ni->ni_mllid = meshpeer->peer_llinkid;
		args[0] = ni->ni_mlpid;
		args[1] = ni->ni_mllid;
		ieee80211_send_action(ni,
		    IEEE80211_ACTION_CAT_SELF_PROT,
		    IEEE80211_ACTION_MESHPEERING_CONFIRM,
		    args);
		mesh_peer_timeout_stop(ni);
		break;
	case IEEE80211_NODE_MESH_ESTABLISHED:
		if (ni->ni_mllid != meshpeer->peer_llinkid) {
			args[0] = ni->ni_mllid;
			args[1] = ni->ni_mlpid;
			args[2] = IEEE80211_REASON_PEER_LINK_CANCELED;
			ieee80211_send_action(ni,
			    IEEE80211_ACTION_CAT_SELF_PROT,
			    IEEE80211_ACTION_MESHPEERING_CLOSE,
			    args);
			mesh_linkchange(ni, IEEE80211_NODE_MESH_HOLDING);
			mesh_peer_timeout_setup(ni);
			break;
		}
		args[0] = ni->ni_mlpid;
		args[1] = ni->ni_mllid;
		ieee80211_send_action(ni,
		    IEEE80211_ACTION_CAT_SELF_PROT,
		    IEEE80211_ACTION_MESHPEERING_CONFIRM,
		    args);
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
	}
	return 0;
}