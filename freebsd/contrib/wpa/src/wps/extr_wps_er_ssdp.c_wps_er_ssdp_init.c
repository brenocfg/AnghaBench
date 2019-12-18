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
struct wps_er {scalar_t__ multicast_sd; scalar_t__ ssdp_sd; int /*<<< orphan*/ * ifname; scalar_t__ forced_ifname; int /*<<< orphan*/  ip_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ add_ssdp_network (int /*<<< orphan*/ *) ; 
 scalar_t__ eloop_register_sock (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wps_er*,int /*<<< orphan*/ *) ; 
 scalar_t__ ssdp_listener_open () ; 
 scalar_t__ ssdp_open_multicast_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_er_send_ssdp_msearch (struct wps_er*) ; 
 int /*<<< orphan*/  wps_er_ssdp_rx ; 

int wps_er_ssdp_init(struct wps_er *er)
{
	if (add_ssdp_network(er->ifname)) {
		wpa_printf(MSG_INFO, "WPS ER: Failed to add routing entry for "
			   "SSDP");
		return -1;
	}

	er->multicast_sd = ssdp_open_multicast_sock(er->ip_addr,
						    er->forced_ifname ?
						    er->ifname : NULL);
	if (er->multicast_sd < 0) {
		wpa_printf(MSG_INFO, "WPS ER: Failed to open multicast socket "
			   "for SSDP");
		return -1;
	}

	er->ssdp_sd = ssdp_listener_open();
	if (er->ssdp_sd < 0) {
		wpa_printf(MSG_INFO, "WPS ER: Failed to open SSDP listener "
			   "socket");
		return -1;
	}

	if (eloop_register_sock(er->multicast_sd, EVENT_TYPE_READ,
				wps_er_ssdp_rx, er, NULL) ||
	    eloop_register_sock(er->ssdp_sd, EVENT_TYPE_READ,
				wps_er_ssdp_rx, er, NULL))
		return -1;

	wps_er_send_ssdp_msearch(er);

	return 0;
}