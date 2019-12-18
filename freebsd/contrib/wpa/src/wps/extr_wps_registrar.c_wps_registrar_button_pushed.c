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
typedef  int /*<<< orphan*/  u8 ;
struct wps_registrar {int selected_registrar; int pbc; int /*<<< orphan*/  wps; int /*<<< orphan*/  p2p_dev_addr; scalar_t__ force_pbc_overlap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_PBC_WALK_TIME ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wps_registrar*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wps_registrar*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_pbc_active_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_pbc_overlap_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_registrar_add_authorized_mac (struct wps_registrar*,int /*<<< orphan*/ *) ; 
 scalar_t__ wps_registrar_pbc_overlap (struct wps_registrar*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wps_registrar_pbc_timeout ; 
 int /*<<< orphan*/  wps_registrar_selected_registrar_changed (struct wps_registrar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_registrar_set_selected_timeout ; 

int wps_registrar_button_pushed(struct wps_registrar *reg,
				const u8 *p2p_dev_addr)
{
	if (p2p_dev_addr == NULL &&
	    wps_registrar_pbc_overlap(reg, NULL, NULL)) {
		wpa_printf(MSG_DEBUG, "WPS: PBC overlap - do not start PBC "
			   "mode");
		wps_pbc_overlap_event(reg->wps);
		return -2;
	}
	wpa_printf(MSG_DEBUG, "WPS: Button pushed - PBC mode started");
	reg->force_pbc_overlap = 0;
	reg->selected_registrar = 1;
	reg->pbc = 1;
	if (p2p_dev_addr)
		os_memcpy(reg->p2p_dev_addr, p2p_dev_addr, ETH_ALEN);
	else
		os_memset(reg->p2p_dev_addr, 0, ETH_ALEN);
	wps_registrar_add_authorized_mac(reg,
					 (u8 *) "\xff\xff\xff\xff\xff\xff");
	wps_registrar_selected_registrar_changed(reg, 0);

	wps_pbc_active_event(reg->wps);
	eloop_cancel_timeout(wps_registrar_set_selected_timeout, reg, NULL);
	eloop_cancel_timeout(wps_registrar_pbc_timeout, reg, NULL);
	eloop_register_timeout(WPS_PBC_WALK_TIME, 0, wps_registrar_pbc_timeout,
			       reg, NULL);
	return 0;
}