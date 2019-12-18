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

/* Variables and functions */
 int /*<<< orphan*/  GPIROUTNMI ; 
 int /*<<< orphan*/  PAD_CFG_DW0_GPP_D_0 ; 
 int /*<<< orphan*/  nmi_debug (char*,char*) ; 
 int /*<<< orphan*/  uv_init_hubless_pch_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_pch_intr_enable ; 
 scalar_t__ uv_pch_intr_now_enabled ; 

__attribute__((used)) static void uv_nmi_setup_hubless_intr(void)
{
	uv_pch_intr_now_enabled = uv_pch_intr_enable;

	uv_init_hubless_pch_io(
		PAD_CFG_DW0_GPP_D_0, GPIROUTNMI,
		uv_pch_intr_now_enabled ? GPIROUTNMI : 0);

	nmi_debug("UV:NMI: GPP_D_0 interrupt %s\n",
		uv_pch_intr_now_enabled ? "enabled" : "disabled");
}