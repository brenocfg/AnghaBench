#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {TYPE_1__* global; int /*<<< orphan*/  ifname; } ;
struct os_reltime {int dummy; } ;
struct TYPE_4__ {scalar_t__ sec; } ;
struct TYPE_3__ {TYPE_2__ p2p_go_wait_client; struct wpa_supplicant* p2p_group_formation; int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  P2P_MAX_INITIAL_CONN_WAIT_GO ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 scalar_t__ os_reltime_expired (struct os_reltime*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int p2p_in_progress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 

int wpas_p2p_in_progress(struct wpa_supplicant *wpa_s)
{
	int ret;

	if (wpa_s->global->p2p_disabled || wpa_s->global->p2p == NULL)
		return 0;

	ret = p2p_in_progress(wpa_s->global->p2p);
	if (ret == 0) {
		/*
		 * Check whether there is an ongoing WPS provisioning step (or
		 * other parts of group formation) on another interface since
		 * p2p_in_progress() does not report this to avoid issues for
		 * scans during such provisioning step.
		 */
		if (wpa_s->global->p2p_group_formation &&
		    wpa_s->global->p2p_group_formation != wpa_s) {
			wpa_dbg(wpa_s, MSG_DEBUG, "P2P: Another interface (%s) "
				"in group formation",
				wpa_s->global->p2p_group_formation->ifname);
			ret = 1;
		}
	}

	if (!ret && wpa_s->global->p2p_go_wait_client.sec) {
		struct os_reltime now;
		os_get_reltime(&now);
		if (os_reltime_expired(&now, &wpa_s->global->p2p_go_wait_client,
				       P2P_MAX_INITIAL_CONN_WAIT_GO)) {
			/* Wait for the first client has expired */
			wpa_s->global->p2p_go_wait_client.sec = 0;
		} else {
			wpa_dbg(wpa_s, MSG_DEBUG, "P2P: Waiting for initial client connection during group formation");
			ret = 1;
		}
	}

	return ret;
}