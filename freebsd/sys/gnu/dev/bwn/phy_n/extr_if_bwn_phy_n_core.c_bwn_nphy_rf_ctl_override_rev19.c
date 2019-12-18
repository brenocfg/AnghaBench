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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void bwn_nphy_rf_ctl_override_rev19(struct bwn_mac *mac, uint16_t field,
					   uint16_t value, uint8_t core, bool off,
					   uint8_t override_id)
{
	/* TODO */
}