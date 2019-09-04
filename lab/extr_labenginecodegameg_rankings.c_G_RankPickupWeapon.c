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
 int /*<<< orphan*/  QGR_KEY_PICKUP_BFG ; 
 int /*<<< orphan*/  QGR_KEY_PICKUP_GAUNTLET ; 
 int /*<<< orphan*/  QGR_KEY_PICKUP_GRAPPLE ; 
 int /*<<< orphan*/  QGR_KEY_PICKUP_GRENADE ; 
 int /*<<< orphan*/  QGR_KEY_PICKUP_LIGHTNING ; 
 int /*<<< orphan*/  QGR_KEY_PICKUP_MACHINEGUN ; 
 int /*<<< orphan*/  QGR_KEY_PICKUP_PLASMA ; 
 int /*<<< orphan*/  QGR_KEY_PICKUP_RAILGUN ; 
 int /*<<< orphan*/  QGR_KEY_PICKUP_ROCKET ; 
 int /*<<< orphan*/  QGR_KEY_PICKUP_SHOTGUN ; 
 int /*<<< orphan*/  QGR_KEY_PICKUP_WEAPON ; 
#define  WP_BFG 137 
#define  WP_GAUNTLET 136 
#define  WP_GRAPPLING_HOOK 135 
#define  WP_GRENADE_LAUNCHER 134 
#define  WP_LIGHTNING 133 
#define  WP_MACHINEGUN 132 
#define  WP_PLASMAGUN 131 
#define  WP_RAILGUN 130 
#define  WP_ROCKET_LAUNCHER 129 
#define  WP_SHOTGUN 128 
 TYPE_1__ level ; 
 int /*<<< orphan*/  trap_RankReportInt (int,int,int /*<<< orphan*/ ,int,int) ; 

void G_RankPickupWeapon( int self, int weapon )
{
	if( level.warmupTime != 0 )
	{
		// no reports during warmup period
		return;
	}
	
	trap_RankReportInt( self, -1, QGR_KEY_PICKUP_WEAPON, 1, 1 );
	switch( weapon )
	{
	case WP_GAUNTLET:
		trap_RankReportInt( self, -1, QGR_KEY_PICKUP_GAUNTLET, 1, 1 );
		break;
	case WP_MACHINEGUN:
		trap_RankReportInt( self, -1, QGR_KEY_PICKUP_MACHINEGUN, 1, 1 );
		break;
	case WP_SHOTGUN:
		trap_RankReportInt( self, -1, QGR_KEY_PICKUP_SHOTGUN, 1, 1 );
		break;
	case WP_GRENADE_LAUNCHER:
		trap_RankReportInt( self, -1, QGR_KEY_PICKUP_GRENADE, 1, 1 );
		break;
	case WP_ROCKET_LAUNCHER:
		trap_RankReportInt( self, -1, QGR_KEY_PICKUP_ROCKET, 1, 1 );
		break;
	case WP_LIGHTNING:
		trap_RankReportInt( self, -1, QGR_KEY_PICKUP_LIGHTNING, 1, 1 );
		break;
	case WP_RAILGUN:
		trap_RankReportInt( self, -1, QGR_KEY_PICKUP_RAILGUN, 1, 1 );
		break;
	case WP_PLASMAGUN:
		trap_RankReportInt( self, -1, QGR_KEY_PICKUP_PLASMA, 1, 1 );
		break;
	case WP_BFG:
		trap_RankReportInt( self, -1, QGR_KEY_PICKUP_BFG, 1, 1 );
		break;
	case WP_GRAPPLING_HOOK:
		trap_RankReportInt( self, -1, QGR_KEY_PICKUP_GRAPPLE, 1, 1 );
		break;
	default:
		break;
	}
}