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
struct bwn_phy_g {int pg_flags; int /*<<< orphan*/ * pg_tssi2dbm; } ;
struct TYPE_2__ {struct bwn_phy_g phy_g; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int BWN_PHY_G_FLAG_TSSITABLE_ALLOC ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
bwn_phy_g_detach(struct bwn_mac *mac)
{
	struct bwn_phy_g *pg = &mac->mac_phy.phy_g;

	if (pg->pg_flags & BWN_PHY_G_FLAG_TSSITABLE_ALLOC) {
		free(pg->pg_tssi2dbm, M_DEVBUF);
		pg->pg_tssi2dbm = NULL;
	}
	pg->pg_flags = 0;
}