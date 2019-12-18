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
struct wps_registrar {int /*<<< orphan*/  multi_ap_backhaul_network_key_len; int /*<<< orphan*/  multi_ap_backhaul_network_key; int /*<<< orphan*/  extra_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wps_registrar*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct wps_registrar*) ; 
 int /*<<< orphan*/  wpabuf_clear_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_registrar_flush (struct wps_registrar*) ; 
 int /*<<< orphan*/  wps_registrar_pbc_timeout ; 
 int /*<<< orphan*/  wps_registrar_set_selected_timeout ; 

void wps_registrar_deinit(struct wps_registrar *reg)
{
	if (reg == NULL)
		return;
	eloop_cancel_timeout(wps_registrar_pbc_timeout, reg, NULL);
	eloop_cancel_timeout(wps_registrar_set_selected_timeout, reg, NULL);
	wps_registrar_flush(reg);
	wpabuf_clear_free(reg->extra_cred);
	bin_clear_free(reg->multi_ap_backhaul_network_key,
		       reg->multi_ap_backhaul_network_key_len);
	os_free(reg);
}