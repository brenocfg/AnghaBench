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
struct sta_info {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct iapp_hdr {int dummy; } ;
struct iapp_data {int /*<<< orphan*/  hapd; } ;
struct iapp_add_notify {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  seq_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_LEVEL_INFO ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IAPP ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct sta_info* ap_get_sta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_sta_disconnect (int /*<<< orphan*/ ,struct sta_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_logger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,unsigned long) ; 

__attribute__((used)) static void iapp_process_add_notify(struct iapp_data *iapp,
				    struct sockaddr_in *from,
				    struct iapp_hdr *hdr, int len)
{
	struct iapp_add_notify *add = (struct iapp_add_notify *) (hdr + 1);
	struct sta_info *sta;

	if (len != sizeof(*add)) {
		wpa_printf(MSG_INFO, "Invalid IAPP-ADD packet length %d (expected %lu)",
			   len, (unsigned long) sizeof(*add));
		return;
	}

	sta = ap_get_sta(iapp->hapd, add->mac_addr);

	/* IAPP-ADD.indication(MAC Address, Sequence Number) */
	hostapd_logger(iapp->hapd, add->mac_addr, HOSTAPD_MODULE_IAPP,
		       HOSTAPD_LEVEL_INFO,
		       "Received IAPP ADD-notify (seq# %d) from %s:%d%s",
		       be_to_host16(add->seq_num),
		       inet_ntoa(from->sin_addr), ntohs(from->sin_port),
		       sta ? "" : " (STA not found)");

	if (!sta)
		return;

	/* TODO: could use seq_num to try to determine whether last association
	 * to this AP is newer than the one advertised in IAPP-ADD. Although,
	 * this is not really a reliable verification. */

	hostapd_logger(iapp->hapd, add->mac_addr, HOSTAPD_MODULE_IAPP,
		       HOSTAPD_LEVEL_DEBUG,
		       "Removing STA due to IAPP ADD-notify");
	ap_sta_disconnect(iapp->hapd, sta, NULL, 0);
}