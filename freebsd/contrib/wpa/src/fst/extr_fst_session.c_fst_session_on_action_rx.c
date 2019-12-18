#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t action; } ;
struct TYPE_6__ {TYPE_1__ fst_action; } ;
struct TYPE_7__ {scalar_t__ category; TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ action; } ;
struct ieee80211_mgmt {TYPE_4__ u; int /*<<< orphan*/  sa; } ;
struct fst_session {int dummy; } ;
struct fst_iface {int dummy; } ;

/* Variables and functions */
 size_t FST_ACTION_MAX_SUPPORTED ; 
 size_t FST_ACTION_SETUP_REQUEST ; 
 int IEEE80211_HDRLEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ WLAN_ACTION_FST ; 
 size_t* fst_action_names ; 
 struct fst_session* fst_find_session_in_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_iface_get_group (struct fst_iface*) ; 
 int /*<<< orphan*/  fst_printf_iface (struct fst_iface*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fst_session_handle_action (struct fst_session*,struct fst_iface*,struct ieee80211_mgmt const*,size_t) ; 
 int /*<<< orphan*/  fst_session_handle_setup_request (struct fst_iface*,struct ieee80211_mgmt const*,size_t) ; 

void fst_session_on_action_rx(struct fst_iface *iface,
			      const struct ieee80211_mgmt *mgmt,
			      size_t len)
{
	struct fst_session *s;

	if (len < IEEE80211_HDRLEN + 2 ||
	    mgmt->u.action.category != WLAN_ACTION_FST) {
		fst_printf_iface(iface, MSG_ERROR,
				 "invalid Action frame received");
		return;
	}

	if (mgmt->u.action.u.fst_action.action <= FST_ACTION_MAX_SUPPORTED) {
		fst_printf_iface(iface, MSG_DEBUG,
				 "FST Action '%s' received!",
				 fst_action_names[mgmt->u.action.u.fst_action.action]);
	} else {
		fst_printf_iface(iface, MSG_WARNING,
				 "unknown FST Action (%u) received!",
				 mgmt->u.action.u.fst_action.action);
		return;
	}

	if (mgmt->u.action.u.fst_action.action == FST_ACTION_SETUP_REQUEST) {
		fst_session_handle_setup_request(iface, mgmt, len);
		return;
	}

	s = fst_find_session_in_progress(mgmt->sa, fst_iface_get_group(iface));
	if (s) {
		fst_session_handle_action(s, iface, mgmt, len);
	} else {
		fst_printf_iface(iface, MSG_WARNING,
				 "FST Action '%s' dropped: no session in progress found",
				 fst_action_names[mgmt->u.action.u.fst_action.action]);
	}
}