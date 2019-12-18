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
struct cmac {scalar_t__ offset; int /*<<< orphan*/ * adapter; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 scalar_t__ A_XGM_PORT_CFG ; 
 int F_MAC_RESET_ ; 
 int F_PCS_RESET_ ; 
 int F_RGMII_RESET_ ; 
 int F_XG2G_RESET_ ; 
 int F_XGMAC_STOP_EN ; 
 int G_PORTSPEED (int) ; 
 scalar_t__ is_10G (int /*<<< orphan*/ *) ; 
 int t3_read_reg (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ uses_xaui (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int xgm_reset_ctrl(const struct cmac *mac)
{
	adapter_t *adap = mac->adapter;
	int val = F_MAC_RESET_ | F_XGMAC_STOP_EN;

	if (is_10G(adap)) {
		int cfg = t3_read_reg(adap, A_XGM_PORT_CFG + mac->offset);

		val |= F_PCS_RESET_;
		if (G_PORTSPEED(cfg) != 3)	/* not running at 10G */
			val |= F_XG2G_RESET_;
	} else if (uses_xaui(adap))
		val |= F_PCS_RESET_ | F_XG2G_RESET_;
	else
		val |= F_RGMII_RESET_ | F_XG2G_RESET_;

	return (val);
}