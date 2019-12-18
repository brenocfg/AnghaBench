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
struct advertisement_state_machine {scalar_t__ state; int /*<<< orphan*/  type; } ;
struct upnp_wps_device_sm {scalar_t__ multicast_sd; struct advertisement_state_machine advertisement; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  dest ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISE_DOWN ; 
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  UPNP_MULTICAST_ADDRESS ; 
 int /*<<< orphan*/  UPNP_MULTICAST_PORT ; 
 int /*<<< orphan*/  advertisement_state_machine_handler ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (int /*<<< orphan*/ ) ; 
 struct wpabuf* next_advertisement (struct upnp_wps_device_sm*,struct advertisement_state_machine*,int*) ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sendto (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

void advertisement_state_machine_stop(struct upnp_wps_device_sm *sm,
				      int send_byebye)
{
	struct advertisement_state_machine *a = &sm->advertisement;
	int islast = 0;
	struct wpabuf *msg;
	struct sockaddr_in dest;

	eloop_cancel_timeout(advertisement_state_machine_handler, NULL, sm);
	if (!send_byebye || sm->multicast_sd < 0)
		return;

	a->type = ADVERTISE_DOWN;
	a->state = 0;

	os_memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(UPNP_MULTICAST_ADDRESS);
	dest.sin_port = htons(UPNP_MULTICAST_PORT);

	while (!islast) {
		msg = next_advertisement(sm, a, &islast);
		if (msg == NULL)
			break;
		if (sendto(sm->multicast_sd, wpabuf_head(msg), wpabuf_len(msg),
			   0, (struct sockaddr *) &dest, sizeof(dest)) < 0) {
			wpa_printf(MSG_INFO, "WPS UPnP: Advertisement sendto "
				   "failed: %d (%s)", errno, strerror(errno));
		}
		wpabuf_free(msg);
		a->state++;
	}
}