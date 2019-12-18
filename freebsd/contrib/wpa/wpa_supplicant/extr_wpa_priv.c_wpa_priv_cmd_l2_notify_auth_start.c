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
struct wpa_priv_interface {scalar_t__* l2; } ;
struct sockaddr_un {int dummy; } ;

/* Variables and functions */
 int WPA_PRIV_MAX_L2 ; 
 int /*<<< orphan*/  l2_packet_notify_auth_start (scalar_t__) ; 

__attribute__((used)) static void wpa_priv_cmd_l2_notify_auth_start(struct wpa_priv_interface *iface,
					      struct sockaddr_un *from)
{
	int idx;

	for (idx = 0; idx < WPA_PRIV_MAX_L2; idx++) {
		if (iface->l2[idx])
			l2_packet_notify_auth_start(iface->l2[idx]);
	}
}