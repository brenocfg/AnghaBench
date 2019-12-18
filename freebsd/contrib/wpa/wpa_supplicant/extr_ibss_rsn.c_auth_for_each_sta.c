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
struct ibss_rsn_peer {struct wpa_state_machine* auth; struct ibss_rsn_peer* next; } ;
struct ibss_rsn {struct ibss_rsn_peer* peers; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int auth_for_each_sta(void *ctx, int (*cb)(struct wpa_state_machine *sm,
						  void *ctx),
			     void *cb_ctx)
{
	struct ibss_rsn *ibss_rsn = ctx;
	struct ibss_rsn_peer *peer;

	wpa_printf(MSG_DEBUG, "AUTH: for_each_sta");

	for (peer = ibss_rsn->peers; peer; peer = peer->next) {
		if (peer->auth && cb(peer->auth, cb_ctx))
			return 1;
	}

	return 0;
}