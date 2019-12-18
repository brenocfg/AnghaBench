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
struct TYPE_2__ {int /*<<< orphan*/  (* exit ) (struct bwn_mac*) ;int /*<<< orphan*/  (* rf_onoff ) (struct bwn_mac*,int /*<<< orphan*/ ) ;} ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct bwn_mac*) ; 

__attribute__((used)) static void
bwn_phy_exit(struct bwn_mac *mac)
{

	mac->mac_phy.rf_onoff(mac, 0);
	if (mac->mac_phy.exit != NULL)
		mac->mac_phy.exit(mac);
}