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
struct wpabuf {int dummy; } ;
struct upnp_wps_device_sm {int /*<<< orphan*/  multicast_sd; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct advertisement_state_machine {int /*<<< orphan*/  state; TYPE_1__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int,void (*) (void*,void*),struct upnp_wps_device_sm*,struct advertisement_state_machine*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msearchreply_state_machine_stop (struct advertisement_state_machine*) ; 
 struct wpabuf* next_advertisement (struct upnp_wps_device_sm*,struct advertisement_state_machine*,int*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static void msearchreply_state_machine_handler(void *eloop_data,
					       void *user_ctx)
{
	struct advertisement_state_machine *a = user_ctx;
	struct upnp_wps_device_sm *sm = eloop_data;
	struct wpabuf *msg;
	int next_timeout_msec = 100;
	int next_timeout_sec = 0;
	int islast = 0;

	/*
	 * Each response is sent twice (in case lost) w/ 100 msec delay
	 * between; spec says no more than 3 times.
	 * One pair for rootdevice, one pair for uuid, and a pair each for
	 * each of the two urns.
	 */

	/* TODO: should only send the requested response types */

	wpa_printf(MSG_MSGDUMP, "WPS UPnP: M-SEARCH reply state=%d (%s:%d)",
		   a->state, inet_ntoa(a->client.sin_addr),
		   ntohs(a->client.sin_port));
	msg = next_advertisement(sm, a, &islast);
	if (msg == NULL)
		return;

	/*
	 * Send it on the multicast socket to avoid having to set up another
	 * socket.
	 */
	if (sendto(sm->multicast_sd, wpabuf_head(msg), wpabuf_len(msg), 0,
		   (struct sockaddr *) &a->client, sizeof(a->client)) < 0) {
		wpa_printf(MSG_DEBUG, "WPS UPnP: M-SEARCH reply sendto "
			   "errno %d (%s) for %s:%d",
			   errno, strerror(errno),
			   inet_ntoa(a->client.sin_addr),
			   ntohs(a->client.sin_port));
		/* Ignore error and hope for the best */
	}
	wpabuf_free(msg);
	if (islast) {
		wpa_printf(MSG_DEBUG, "WPS UPnP: M-SEARCH reply done");
		msearchreply_state_machine_stop(a);
		return;
	}
	a->state++;

	wpa_printf(MSG_MSGDUMP, "WPS UPnP: M-SEARCH reply in %d.%03d sec",
		   next_timeout_sec, next_timeout_msec);
	eloop_register_timeout(next_timeout_sec, next_timeout_msec,
			       msearchreply_state_machine_handler, sm, a);
}