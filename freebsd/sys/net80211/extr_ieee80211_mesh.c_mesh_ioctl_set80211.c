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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  tmpproto ;
struct ieee80211vap {scalar_t__ iv_opmode; int /*<<< orphan*/  iv_myaddr; struct ieee80211_mesh_state* iv_mesh; } ;
struct ieee80211req {int i_type; int i_len; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_val; } ;
struct ieee80211_mesh_state {int ms_idlen; char ms_ttl; int /*<<< orphan*/  ms_flags; int /*<<< orphan*/  ms_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETRESET ; 
 int ENOSYS ; 
 int /*<<< orphan*/  IEEE80211_ADDR_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_ADDR_LEN ; 
#define  IEEE80211_IOC_MESH_AP 139 
#define  IEEE80211_IOC_MESH_FWRD 138 
#define  IEEE80211_IOC_MESH_GATE 137 
#define  IEEE80211_IOC_MESH_ID 136 
#define  IEEE80211_IOC_MESH_PR_METRIC 135 
#define  IEEE80211_IOC_MESH_PR_PATH 134 
#define  IEEE80211_IOC_MESH_RTCMD 133 
#define  IEEE80211_IOC_MESH_TTL 132 
 int /*<<< orphan*/  IEEE80211_MESHFLAGS_AP ; 
 int /*<<< orphan*/  IEEE80211_MESHFLAGS_FWD ; 
 int /*<<< orphan*/  IEEE80211_MESHFLAGS_GATE ; 
 int IEEE80211_MESHID_LEN ; 
 int IEEE80211_MESH_PROTO_DSZ ; 
#define  IEEE80211_MESH_RTCMD_ADD 131 
#define  IEEE80211_MESH_RTCMD_DELETE 130 
#define  IEEE80211_MESH_RTCMD_FLUSH 129 
#define  IEEE80211_MESH_RTCMD_LIST 128 
 scalar_t__ IEEE80211_M_MBSS ; 
 int IEEE80211_NWID_LEN ; 
 int /*<<< orphan*/  broadcastaddr ; 
 int copyin (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ieee80211_mesh_discover (struct ieee80211vap*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_mesh_rt_del (struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_mesh_rt_flush (struct ieee80211vap*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mesh_gatemode_setup (struct ieee80211vap*) ; 
 int mesh_select_proto_metric (struct ieee80211vap*,char*) ; 
 int mesh_select_proto_path (struct ieee80211vap*,char*) ; 

__attribute__((used)) static int
mesh_ioctl_set80211(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211_mesh_state *ms = vap->iv_mesh;
	uint8_t tmpmeshid[IEEE80211_NWID_LEN];
	uint8_t tmpaddr[IEEE80211_ADDR_LEN];
	char tmpproto[IEEE80211_MESH_PROTO_DSZ];
	int error;

	if (vap->iv_opmode != IEEE80211_M_MBSS)
		return ENOSYS;

	error = 0;
	switch (ireq->i_type) {
	case IEEE80211_IOC_MESH_ID:
		if (ireq->i_val != 0 || ireq->i_len > IEEE80211_MESHID_LEN)
			return EINVAL;
		error = copyin(ireq->i_data, tmpmeshid, ireq->i_len);
		if (error != 0)
			break;
		memset(ms->ms_id, 0, IEEE80211_NWID_LEN);
		ms->ms_idlen = ireq->i_len;
		memcpy(ms->ms_id, tmpmeshid, ireq->i_len);
		error = ENETRESET;
		break;
	case IEEE80211_IOC_MESH_AP:
		if (ireq->i_val)
			ms->ms_flags |= IEEE80211_MESHFLAGS_AP;
		else
			ms->ms_flags &= ~IEEE80211_MESHFLAGS_AP;
		error = ENETRESET;
		break;
	case IEEE80211_IOC_MESH_FWRD:
		if (ireq->i_val)
			ms->ms_flags |= IEEE80211_MESHFLAGS_FWD;
		else
			ms->ms_flags &= ~IEEE80211_MESHFLAGS_FWD;
		mesh_gatemode_setup(vap);
		break;
	case IEEE80211_IOC_MESH_GATE:
		if (ireq->i_val)
			ms->ms_flags |= IEEE80211_MESHFLAGS_GATE;
		else
			ms->ms_flags &= ~IEEE80211_MESHFLAGS_GATE;
		break;
	case IEEE80211_IOC_MESH_TTL:
		ms->ms_ttl = (uint8_t) ireq->i_val;
		break;
	case IEEE80211_IOC_MESH_RTCMD:
		switch (ireq->i_val) {
		case IEEE80211_MESH_RTCMD_LIST:
			return EINVAL;
		case IEEE80211_MESH_RTCMD_FLUSH:
			ieee80211_mesh_rt_flush(vap);
			break;
		case IEEE80211_MESH_RTCMD_ADD:
			if (IEEE80211_ADDR_EQ(vap->iv_myaddr, ireq->i_data) ||
			    IEEE80211_ADDR_EQ(broadcastaddr, ireq->i_data))
				return EINVAL;
			error = copyin(ireq->i_data, &tmpaddr,
			    IEEE80211_ADDR_LEN);
			if (error == 0)
				ieee80211_mesh_discover(vap, tmpaddr, NULL);
			break;
		case IEEE80211_MESH_RTCMD_DELETE:
			ieee80211_mesh_rt_del(vap, ireq->i_data);
			break;
		default:
			return ENOSYS;
		}
		break;
	case IEEE80211_IOC_MESH_PR_METRIC:
		error = copyin(ireq->i_data, tmpproto, sizeof(tmpproto));
		if (error == 0) {
			error = mesh_select_proto_metric(vap, tmpproto);
			if (error == 0)
				error = ENETRESET;
		}
		break;
	case IEEE80211_IOC_MESH_PR_PATH:
		error = copyin(ireq->i_data, tmpproto, sizeof(tmpproto));
		if (error == 0) {
			error = mesh_select_proto_path(vap, tmpproto);
			if (error == 0)
				error = ENETRESET;
		}
		break;
	default:
		return ENOSYS;
	}
	return error;
}