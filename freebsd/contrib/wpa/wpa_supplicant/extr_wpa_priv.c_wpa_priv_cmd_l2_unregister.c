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
struct wpa_priv_interface {int /*<<< orphan*/ ** l2; int /*<<< orphan*/ * l2_addr; int /*<<< orphan*/ * l2_addr_len; } ;
struct sockaddr_un {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_PRIV_MAX_L2 ; 
 int /*<<< orphan*/  l2_packet_deinit (int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ *,struct sockaddr_un*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wpa_priv_cmd_l2_unregister(struct wpa_priv_interface *iface,
				       struct sockaddr_un *from,
				       socklen_t fromlen)
{
	int idx;

	for (idx = 0; idx < WPA_PRIV_MAX_L2; idx++) {
		if (iface->l2_addr_len[idx] == fromlen &&
		    os_memcmp(&iface->l2_addr[idx], from, fromlen) == 0)
			break;
	}
	if (idx == WPA_PRIV_MAX_L2) {
		wpa_printf(MSG_DEBUG,
			   "No registered l2_packet socket found for unregister request");
		return;
	}

	if (iface->l2[idx]) {
		l2_packet_deinit(iface->l2[idx]);
		iface->l2[idx] = NULL;
	}
}