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
struct bwn_phy {int rev; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */

__attribute__((used)) static void bwn_nphy_gain_ctl_workarounds_rev7(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;

	switch (phy->rev) {
	/* TODO */
	}
}