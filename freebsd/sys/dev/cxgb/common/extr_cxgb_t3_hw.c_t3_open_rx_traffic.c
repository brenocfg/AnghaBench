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
typedef  int /*<<< orphan*/  u32 ;
struct cmac {scalar_t__ offset; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 scalar_t__ A_XGM_RX_CFG ; 
 scalar_t__ A_XGM_RX_HASH_HIGH ; 
 scalar_t__ A_XGM_RX_HASH_LOW ; 
 int F_COPYALLFRAMES ; 
 int F_DISBCAST ; 
 int F_ENHASHMCAST ; 
 int /*<<< orphan*/  t3_mac_enable_exact_filters (struct cmac*) ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void t3_open_rx_traffic(struct cmac *mac, u32 rx_cfg,
			       u32 rx_hash_high, u32 rx_hash_low)
{
	t3_mac_enable_exact_filters(mac);
	t3_set_reg_field(mac->adapter, A_XGM_RX_CFG + mac->offset,
			 F_ENHASHMCAST | F_DISBCAST | F_COPYALLFRAMES,
			 rx_cfg);
	t3_write_reg(mac->adapter, A_XGM_RX_HASH_HIGH + mac->offset,
	    rx_hash_high);
	t3_write_reg(mac->adapter, A_XGM_RX_HASH_LOW + mac->offset,
	    rx_hash_low);
}