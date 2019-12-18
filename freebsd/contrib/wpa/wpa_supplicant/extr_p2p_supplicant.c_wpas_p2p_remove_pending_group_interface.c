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
struct wpa_supplicant {char* pending_interface_name; TYPE_1__* global; int /*<<< orphan*/  pending_interface_addr; int /*<<< orphan*/  pending_interface_type; } ;
struct TYPE_2__ {scalar_t__ pending_group_iface_for_p2ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_drv_if_remove (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void wpas_p2p_remove_pending_group_interface(
	struct wpa_supplicant *wpa_s)
{
	if (!wpa_s->pending_interface_name[0] ||
	    is_zero_ether_addr(wpa_s->pending_interface_addr))
		return; /* No pending virtual interface */

	wpa_printf(MSG_DEBUG, "P2P: Removing pending group interface %s",
		   wpa_s->pending_interface_name);
	wpa_drv_if_remove(wpa_s, wpa_s->pending_interface_type,
			  wpa_s->pending_interface_name);
	os_memset(wpa_s->pending_interface_addr, 0, ETH_ALEN);
	wpa_s->pending_interface_name[0] = '\0';
	wpa_s->global->pending_group_iface_for_p2ps = 0;
}