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
 int ENTITYNUM_WORLD ; 
#define  MOD_BFG 149 
#define  MOD_BFG_SPLASH 148 
#define  MOD_CRUSH 147 
#define  MOD_FALLING 146 
#define  MOD_GAUNTLET 145 
#define  MOD_GRAPPLE 144 
#define  MOD_GRENADE 143 
#define  MOD_GRENADE_SPLASH 142 
#define  MOD_LAVA 141 
#define  MOD_LIGHTNING 140 
#define  MOD_MACHINEGUN 139 
#define  MOD_PLASMA 138 
#define  MOD_PLASMA_SPLASH 137 
#define  MOD_RAILGUN 136 
#define  MOD_ROCKET 135 
#define  MOD_ROCKET_SPLASH 134 
#define  MOD_SHOTGUN 133 
#define  MOD_SLIME 132 
#define  MOD_SUICIDE 131 
#define  MOD_TELEFRAG 130 
#define  MOD_TRIGGER_HURT 129 
#define  MOD_WATER 128 
 int /*<<< orphan*/  QGR_KEY_CRUSH ; 
 int /*<<< orphan*/  QGR_KEY_FALLING ; 
 int /*<<< orphan*/  QGR_KEY_FRAG ; 
 int /*<<< orphan*/  QGR_KEY_FRAG_BFG ; 
 int /*<<< orphan*/  QGR_KEY_FRAG_GAUNTLET ; 
 int /*<<< orphan*/  QGR_KEY_FRAG_GRAPPLE ; 
 int /*<<< orphan*/  QGR_KEY_FRAG_GRENADE ; 
 int /*<<< orphan*/  QGR_KEY_FRAG_LIGHTNING ; 
 int /*<<< orphan*/  QGR_KEY_FRAG_MACHINEGUN ; 
 int /*<<< orphan*/  QGR_KEY_FRAG_PLASMA ; 
 int /*<<< orphan*/  QGR_KEY_FRAG_RAILGUN ; 
 int /*<<< orphan*/  QGR_KEY_FRAG_ROCKET ; 
 int /*<<< orphan*/  QGR_KEY_FRAG_SHOTGUN ; 
 int /*<<< orphan*/  QGR_KEY_FRAG_UNKNOWN ; 
 int /*<<< orphan*/  QGR_KEY_HAZARD_DEATH ; 
 int /*<<< orphan*/  QGR_KEY_HAZARD_MISC ; 
 int /*<<< orphan*/  QGR_KEY_LAVA ; 
 int /*<<< orphan*/  QGR_KEY_SLIME ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_BFG ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_CMD ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_GAUNTLET ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_GRAPPLE ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_GRENADE ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_LIGHTNING ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_MACHINEGUN ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_PLASMA ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_RAILGUN ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_ROCKET ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_SHOTGUN ; 
 int /*<<< orphan*/  QGR_KEY_SUICIDE_UNKNOWN ; 
 int /*<<< orphan*/  QGR_KEY_TELEFRAG ; 
 int /*<<< orphan*/  QGR_KEY_TRIGGER_HURT ; 
 int /*<<< orphan*/  QGR_KEY_WATER ; 
 TYPE_1__ level ; 
 int /*<<< orphan*/  trap_RankReportInt (int,int,int /*<<< orphan*/ ,int,int) ; 

void G_RankPlayerDie( int self, int attacker, int means_of_death )
{
	int	p1;
	int	p2;

	if( level.warmupTime != 0 )
	{
		// no reports during warmup period
		return;
	}
	
	if( attacker == ENTITYNUM_WORLD )
	{
		p1 = self;
		p2 = -1;
		
		trap_RankReportInt( p1, p2, QGR_KEY_HAZARD_DEATH, 1, 1 );

		switch( means_of_death )
		{
		case MOD_WATER:
			trap_RankReportInt( p1, p2, QGR_KEY_WATER, 1, 1 );
			break;
		case MOD_SLIME:
			trap_RankReportInt( p1, p2, QGR_KEY_SLIME, 1, 1 );
			break;
		case MOD_LAVA:
			trap_RankReportInt( p1, p2, QGR_KEY_LAVA, 1, 1 );
			break;
		case MOD_CRUSH:
			trap_RankReportInt( p1, p2, QGR_KEY_CRUSH, 1, 1 );
			break;
		case MOD_TELEFRAG:
			trap_RankReportInt( p1, p2, QGR_KEY_TELEFRAG, 1, 1 );
			break;
		case MOD_FALLING:
			trap_RankReportInt( p1, p2, QGR_KEY_FALLING, 1, 1 );
			break;
		case MOD_SUICIDE:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_CMD, 1, 1 );
			break;
		case MOD_TRIGGER_HURT:
			trap_RankReportInt( p1, p2, QGR_KEY_TRIGGER_HURT, 1, 1 );
			break;
		default:
			trap_RankReportInt( p1, p2, QGR_KEY_HAZARD_MISC, 1, 1 );
			break;
		}
	}
	else if( attacker == self )
	{
		p1 = self;
		p2 = -1;
		
		trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE, 1, 1 );
		
		switch( means_of_death )
		{
		case MOD_GAUNTLET:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_GAUNTLET, 1, 1 );
			break;
		case MOD_MACHINEGUN:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_MACHINEGUN, 1, 1 );
			break;
		case MOD_SHOTGUN:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_SHOTGUN, 1, 1 );
			break;
		case MOD_GRENADE:
		case MOD_GRENADE_SPLASH:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_GRENADE, 1, 1 );
			break;
		case MOD_ROCKET:
		case MOD_ROCKET_SPLASH:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_ROCKET, 1, 1 );
			break;
		case MOD_PLASMA:
		case MOD_PLASMA_SPLASH:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_PLASMA, 1, 1 );
			break;
		case MOD_RAILGUN:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_RAILGUN, 1, 1 );
			break;
		case MOD_LIGHTNING:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_LIGHTNING, 1, 1 );
			break;
		case MOD_BFG:
		case MOD_BFG_SPLASH:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_BFG, 1, 1 );
			break;
		case MOD_GRAPPLE:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_GRAPPLE, 1, 1 );
			break;
		default:
			trap_RankReportInt( p1, p2, QGR_KEY_SUICIDE_UNKNOWN, 1, 1 );
			break;
		}
	}
	else
	{
		p1 = attacker;
		p2 = self;

		trap_RankReportInt( p1, p2, QGR_KEY_FRAG, 1, 1 );
		
		switch( means_of_death )
		{
		case MOD_GAUNTLET:
			trap_RankReportInt( p1, p2, QGR_KEY_FRAG_GAUNTLET, 1, 1 );
			break;
		case MOD_MACHINEGUN:
			trap_RankReportInt( p1, p2, QGR_KEY_FRAG_MACHINEGUN, 1, 1 );
			break;
		case MOD_SHOTGUN:
			trap_RankReportInt( p1, p2, QGR_KEY_FRAG_SHOTGUN, 1, 1 );
			break;
		case MOD_GRENADE:
		case MOD_GRENADE_SPLASH:
			trap_RankReportInt( p1, p2, QGR_KEY_FRAG_GRENADE, 1, 1 );
			break;
		case MOD_ROCKET:
		case MOD_ROCKET_SPLASH:
			trap_RankReportInt( p1, p2, QGR_KEY_FRAG_ROCKET, 1, 1 );
			break;
		case MOD_PLASMA:
		case MOD_PLASMA_SPLASH:
			trap_RankReportInt( p1, p2, QGR_KEY_FRAG_PLASMA, 1, 1 );
			break;
		case MOD_RAILGUN:
			trap_RankReportInt( p1, p2, QGR_KEY_FRAG_RAILGUN, 1, 1 );
			break;
		case MOD_LIGHTNING:
			trap_RankReportInt( p1, p2, QGR_KEY_FRAG_LIGHTNING, 1, 1 );
			break;
		case MOD_BFG:
		case MOD_BFG_SPLASH:
			trap_RankReportInt( p1, p2, QGR_KEY_FRAG_BFG, 1, 1 );
			break;
		case MOD_GRAPPLE:
			trap_RankReportInt( p1, p2, QGR_KEY_FRAG_GRAPPLE, 1, 1 );
			break;
		default:
			trap_RankReportInt( p1, p2, QGR_KEY_FRAG_UNKNOWN, 1, 1 );
			break;
		}
	}
}