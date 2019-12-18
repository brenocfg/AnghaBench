#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int weapon_change_time; } ;
typedef  TYPE_1__ gclient_t ;
struct TYPE_6__ {TYPE_1__* client; } ;
struct TYPE_5__ {scalar_t__ warmupTime; int time; } ;

/* Variables and functions */
 int /*<<< orphan*/  QGR_KEY_TIME ; 
 int /*<<< orphan*/  QGR_KEY_TIME_BFG ; 
 int /*<<< orphan*/  QGR_KEY_TIME_GAUNTLET ; 
 int /*<<< orphan*/  QGR_KEY_TIME_GRAPPLE ; 
 int /*<<< orphan*/  QGR_KEY_TIME_GRENADE ; 
 int /*<<< orphan*/  QGR_KEY_TIME_LIGHTNING ; 
 int /*<<< orphan*/  QGR_KEY_TIME_MACHINEGUN ; 
 int /*<<< orphan*/  QGR_KEY_TIME_PLASMA ; 
 int /*<<< orphan*/  QGR_KEY_TIME_RAILGUN ; 
 int /*<<< orphan*/  QGR_KEY_TIME_ROCKET ; 
 int /*<<< orphan*/  QGR_KEY_TIME_SHOTGUN ; 
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
 TYPE_3__* g_entities ; 
 TYPE_2__ level ; 
 int /*<<< orphan*/  trap_RankReportInt (int,int,int /*<<< orphan*/ ,int,int) ; 

void G_RankWeaponTime( int self, int weapon )
{
	gclient_t*	client;
	int			time;

	if( level.warmupTime != 0 )
	{
		// no reports during warmup period
		return;
	}
	
	client = g_entities[self].client;
	time = (level.time - client->weapon_change_time) / 1000;
	client->weapon_change_time = level.time;

	if( time <= 0 )
	{
		return;
	}
	
	trap_RankReportInt( self, -1, QGR_KEY_TIME, time, 1 );

	switch( weapon )
	{
	case WP_GAUNTLET:
		trap_RankReportInt( self, -1, QGR_KEY_TIME_GAUNTLET, time, 1 );
		break;
	case WP_MACHINEGUN:
		trap_RankReportInt( self, -1, QGR_KEY_TIME_MACHINEGUN, time, 1 );
		break;
	case WP_SHOTGUN:
		trap_RankReportInt( self, -1, QGR_KEY_TIME_SHOTGUN, time, 1 );
		break;
	case WP_GRENADE_LAUNCHER:
		trap_RankReportInt( self, -1, QGR_KEY_TIME_GRENADE, time, 1 );
		break;
	case WP_ROCKET_LAUNCHER:
		trap_RankReportInt( self, -1, QGR_KEY_TIME_ROCKET, time, 1 );
		break;
	case WP_LIGHTNING:
		trap_RankReportInt( self, -1, QGR_KEY_TIME_LIGHTNING, time, 1 );
		break;
	case WP_RAILGUN:
		trap_RankReportInt( self, -1, QGR_KEY_TIME_RAILGUN, time, 1 );
		break;
	case WP_PLASMAGUN:
		trap_RankReportInt( self, -1, QGR_KEY_TIME_PLASMA, time, 1 );
		break;
	case WP_BFG:
		trap_RankReportInt( self, -1, QGR_KEY_TIME_BFG, time, 1 );
		break;
	case WP_GRAPPLING_HOOK:
		trap_RankReportInt( self, -1, QGR_KEY_TIME_GRAPPLE, time, 1 );
		break;
	default:
		break;
	}
}