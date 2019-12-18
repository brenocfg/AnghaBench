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
struct TYPE_2__ {scalar_t__ warmupTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  QGR_KEY_BOXES ; 
 int /*<<< orphan*/  QGR_KEY_BOXES_BFG_AMMO ; 
 int /*<<< orphan*/  QGR_KEY_BOXES_BULLETS ; 
 int /*<<< orphan*/  QGR_KEY_BOXES_CELLS ; 
 int /*<<< orphan*/  QGR_KEY_BOXES_GRENADES ; 
 int /*<<< orphan*/  QGR_KEY_BOXES_LG_AMMO ; 
 int /*<<< orphan*/  QGR_KEY_BOXES_ROCKETS ; 
 int /*<<< orphan*/  QGR_KEY_BOXES_SHELLS ; 
 int /*<<< orphan*/  QGR_KEY_BOXES_SLUGS ; 
 int /*<<< orphan*/  QGR_KEY_ROUNDS ; 
 int /*<<< orphan*/  QGR_KEY_ROUNDS_BFG_AMMO ; 
 int /*<<< orphan*/  QGR_KEY_ROUNDS_BULLETS ; 
 int /*<<< orphan*/  QGR_KEY_ROUNDS_CELLS ; 
 int /*<<< orphan*/  QGR_KEY_ROUNDS_GRENADES ; 
 int /*<<< orphan*/  QGR_KEY_ROUNDS_LG_AMMO ; 
 int /*<<< orphan*/  QGR_KEY_ROUNDS_ROCKETS ; 
 int /*<<< orphan*/  QGR_KEY_ROUNDS_SHELLS ; 
 int /*<<< orphan*/  QGR_KEY_ROUNDS_SLUGS ; 
#define  WP_BFG 135 
#define  WP_GRENADE_LAUNCHER 134 
#define  WP_LIGHTNING 133 
#define  WP_MACHINEGUN 132 
#define  WP_PLASMAGUN 131 
#define  WP_RAILGUN 130 
#define  WP_ROCKET_LAUNCHER 129 
#define  WP_SHOTGUN 128 
 TYPE_1__ level ; 
 int /*<<< orphan*/  trap_RankReportInt (int,int,int /*<<< orphan*/ ,int,int) ; 

void G_RankPickupAmmo( int self, int weapon, int quantity )
{
	if( level.warmupTime != 0 )
	{
		// no reports during warmup period
		return;
	}
	
	trap_RankReportInt( self, -1, QGR_KEY_BOXES, 1, 1 );
	trap_RankReportInt( self, -1, QGR_KEY_ROUNDS, quantity, 1 );
	
	switch( weapon )
	{
	case WP_MACHINEGUN:
		trap_RankReportInt( self, -1, QGR_KEY_BOXES_BULLETS, 1, 1 );
		trap_RankReportInt( self, -1, QGR_KEY_ROUNDS_BULLETS, quantity, 1 );
		break;
	case WP_SHOTGUN:
		trap_RankReportInt( self, -1, QGR_KEY_BOXES_SHELLS, 1, 1 );
		trap_RankReportInt( self, -1, QGR_KEY_ROUNDS_SHELLS, quantity, 1 );
		break;
	case WP_GRENADE_LAUNCHER:
		trap_RankReportInt( self, -1, QGR_KEY_BOXES_GRENADES, 1, 1 );
		trap_RankReportInt( self, -1, QGR_KEY_ROUNDS_GRENADES, quantity, 1 );
		break;
	case WP_ROCKET_LAUNCHER:
		trap_RankReportInt( self, -1, QGR_KEY_BOXES_ROCKETS, 1, 1 );
		trap_RankReportInt( self, -1, QGR_KEY_ROUNDS_ROCKETS, quantity, 1 );
		break;
	case WP_LIGHTNING:
		trap_RankReportInt( self, -1, QGR_KEY_BOXES_LG_AMMO, 1, 1 );
		trap_RankReportInt( self, -1, QGR_KEY_ROUNDS_LG_AMMO, quantity, 1 );
		break;
	case WP_RAILGUN:
		trap_RankReportInt( self, -1, QGR_KEY_BOXES_SLUGS, 1, 1 );
		trap_RankReportInt( self, -1, QGR_KEY_ROUNDS_SLUGS, quantity, 1 );
		break;
	case WP_PLASMAGUN:
		trap_RankReportInt( self, -1, QGR_KEY_BOXES_CELLS, 1, 1 );
		trap_RankReportInt( self, -1, QGR_KEY_ROUNDS_CELLS, quantity, 1 );
		break;
	case WP_BFG:
		trap_RankReportInt( self, -1, QGR_KEY_BOXES_BFG_AMMO, 1, 1 );
		trap_RankReportInt( self, -1, QGR_KEY_ROUNDS_BFG_AMMO, quantity, 1 );
		break;
	default:
		break;
	}
}