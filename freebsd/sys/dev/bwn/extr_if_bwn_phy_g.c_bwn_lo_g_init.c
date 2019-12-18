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
 int /*<<< orphan*/  bwn_has_hwpctl (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_lo_get_powervector (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_g_dc_lookup_init (struct bwn_mac*,int) ; 

__attribute__((used)) static void
bwn_lo_g_init(struct bwn_mac *mac)
{

	if (!bwn_has_hwpctl(mac))
		return;

	bwn_lo_get_powervector(mac);
	bwn_phy_g_dc_lookup_init(mac, 1);
}