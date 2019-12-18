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
struct bwn_rfatt {int dummy; } ;
struct bwn_phy_g {int /*<<< orphan*/  pg_bbatt; int /*<<< orphan*/  pg_rfatt; } ;
struct TYPE_2__ {struct bwn_phy_g phy_g; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;
struct bwn_lo_calib {int /*<<< orphan*/  ctl; } ;
typedef  int /*<<< orphan*/  rf ;

/* Variables and functions */
 int /*<<< orphan*/  bwn_lo_fixup_rfatt (struct bwn_rfatt*) ; 
 struct bwn_lo_calib* bwn_lo_get_calib (struct bwn_mac*,int /*<<< orphan*/ *,struct bwn_rfatt*) ; 
 int /*<<< orphan*/  bwn_lo_write (struct bwn_mac*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct bwn_rfatt*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
bwn_lo_g_adjust(struct bwn_mac *mac)
{
	struct bwn_phy_g *pg = &mac->mac_phy.phy_g;
	struct bwn_lo_calib *cal;
	struct bwn_rfatt rf;

	memcpy(&rf, &pg->pg_rfatt, sizeof(rf));
	bwn_lo_fixup_rfatt(&rf);

	cal = bwn_lo_get_calib(mac, &pg->pg_bbatt, &rf);
	if (!cal)
		return;
	bwn_lo_write(mac, &cal->ctl);
}