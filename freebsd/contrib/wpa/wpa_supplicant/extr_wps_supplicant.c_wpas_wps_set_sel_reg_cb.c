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
typedef  int /*<<< orphan*/  u16 ;
struct wpa_supplicant {int /*<<< orphan*/ * wps_er; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_er_set_sel_reg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_wps_set_sel_reg_cb(void *ctx, int sel_reg, u16 dev_passwd_id,
				    u16 sel_reg_config_methods)
{
#ifdef CONFIG_WPS_ER
	struct wpa_supplicant *wpa_s = ctx;

	if (wpa_s->wps_er == NULL)
		return;
	wpa_printf(MSG_DEBUG, "WPS ER: SetSelectedRegistrar - sel_reg=%d "
		   "dev_password_id=%u sel_reg_config_methods=0x%x",
		   sel_reg, dev_passwd_id, sel_reg_config_methods);
	wps_er_set_sel_reg(wpa_s->wps_er, sel_reg, dev_passwd_id,
			   sel_reg_config_methods);
#endif /* CONFIG_WPS_ER */
}