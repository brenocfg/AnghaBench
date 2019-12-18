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
struct upnp_wps_device_sm {int /*<<< orphan*/  msearch_replies; } ;
struct sockaddr_in {int dummy; } ;
struct advertisement_state_machine {int /*<<< orphan*/  list; int /*<<< orphan*/  client; scalar_t__ state; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int MAX_MSEARCH ; 
 int /*<<< orphan*/  MSEARCH_REPLY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dl_list_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct upnp_wps_device_sm*,struct advertisement_state_machine*) ; 
 scalar_t__ eloop_register_timeout (int,int,int /*<<< orphan*/ ,struct upnp_wps_device_sm*,struct advertisement_state_machine*) ; 
 int /*<<< orphan*/  msearchreply_state_machine_handler ; 
 int /*<<< orphan*/  os_free (struct advertisement_state_machine*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,struct sockaddr_in*,int) ; 
 int os_random () ; 
 struct advertisement_state_machine* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void msearchreply_state_machine_start(struct upnp_wps_device_sm *sm,
					     struct sockaddr_in *client,
					     int mx)
{
	struct advertisement_state_machine *a;
	int next_timeout_sec;
	int next_timeout_msec;
	int replies;

	replies = dl_list_len(&sm->msearch_replies);
	wpa_printf(MSG_DEBUG, "WPS UPnP: M-SEARCH reply start (%d "
		   "outstanding)", replies);
	if (replies >= MAX_MSEARCH) {
		wpa_printf(MSG_INFO, "WPS UPnP: Too many outstanding "
			   "M-SEARCH replies");
		return;
	}

	a = os_zalloc(sizeof(*a));
	if (a == NULL)
		return;
	a->type = MSEARCH_REPLY;
	a->state = 0;
	os_memcpy(&a->client, client, sizeof(*client));
	/* Wait time depending on MX value */
	next_timeout_msec = (1000 * mx * (os_random() & 0xFF)) >> 8;
	next_timeout_sec = next_timeout_msec / 1000;
	next_timeout_msec = next_timeout_msec % 1000;
	if (eloop_register_timeout(next_timeout_sec, next_timeout_msec,
				   msearchreply_state_machine_handler, sm,
				   a)) {
		/* No way to recover (from malloc failure) */
		goto fail;
	}
	/* Remember for future cleanup */
	dl_list_add(&sm->msearch_replies, &a->list);
	return;

fail:
	wpa_printf(MSG_INFO, "WPS UPnP: M-SEARCH reply failure!");
	eloop_cancel_timeout(msearchreply_state_machine_handler, sm, a);
	os_free(a);
}