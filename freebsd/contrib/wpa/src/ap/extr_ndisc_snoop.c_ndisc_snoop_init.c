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
struct hostapd_data {int /*<<< orphan*/ * sock_ndisc; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2_PACKET_FILTER_NDISC ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  handle_ndisc ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * x_snoop_get_l2_packet (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ndisc_snoop_init(struct hostapd_data *hapd)
{
	hapd->sock_ndisc = x_snoop_get_l2_packet(hapd, handle_ndisc,
						 L2_PACKET_FILTER_NDISC);
	if (hapd->sock_ndisc == NULL) {
		wpa_printf(MSG_DEBUG,
			   "ndisc_snoop: Failed to initialize L2 packet processing for NDISC packets: %s",
			   strerror(errno));
		return -1;
	}

	return 0;
}