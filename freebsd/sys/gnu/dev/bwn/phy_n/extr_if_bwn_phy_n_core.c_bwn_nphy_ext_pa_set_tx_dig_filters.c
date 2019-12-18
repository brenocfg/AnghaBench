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
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwn_nphy_pa_set_tx_dig_filter (struct bwn_mac*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tbl_tx_filter_coef_rev4 ; 

__attribute__((used)) static void bwn_nphy_ext_pa_set_tx_dig_filters(struct bwn_mac *mac)
{
	bwn_nphy_pa_set_tx_dig_filter(mac, 0x2C5,
				      tbl_tx_filter_coef_rev4[2]);
}