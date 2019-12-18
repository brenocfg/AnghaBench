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
typedef  int u16 ;
struct wps_registrar {scalar_t__ pbc; scalar_t__ selected_registrar; int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* set_sel_reg_cb ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ;TYPE_1__* wps; } ;
struct TYPE_2__ {int config_methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PW_DEFAULT ; 
 int /*<<< orphan*/  DEV_PW_PUSHBUTTON ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPS_CONFIG_PHY_PUSHBUTTON ; 
 int WPS_CONFIG_PUSHBUTTON ; 
 int WPS_CONFIG_VIRT_PUSHBUTTON ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  wps_set_pushbutton (int*,int) ; 

__attribute__((used)) static void wps_cb_set_sel_reg(struct wps_registrar *reg)
{
	u16 methods = 0;
	if (reg->set_sel_reg_cb == NULL)
		return;

	if (reg->selected_registrar) {
		methods = reg->wps->config_methods & ~WPS_CONFIG_PUSHBUTTON;
		methods &= ~(WPS_CONFIG_VIRT_PUSHBUTTON |
			     WPS_CONFIG_PHY_PUSHBUTTON);
		if (reg->pbc)
			wps_set_pushbutton(&methods, reg->wps->config_methods);
	}

	wpa_printf(MSG_DEBUG, "WPS: wps_cb_set_sel_reg: sel_reg=%d "
		   "config_methods=0x%x pbc=%d methods=0x%x",
		   reg->selected_registrar, reg->wps->config_methods,
		   reg->pbc, methods);

	reg->set_sel_reg_cb(reg->cb_ctx, reg->selected_registrar,
			    reg->pbc ? DEV_PW_PUSHBUTTON : DEV_PW_DEFAULT,
			    methods);
}