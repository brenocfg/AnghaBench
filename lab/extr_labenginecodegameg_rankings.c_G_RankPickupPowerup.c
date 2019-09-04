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
#define  PW_BATTLESUIT 133 
 int PW_BLUEFLAG ; 
#define  PW_FLIGHT 132 
#define  PW_HASTE 131 
#define  PW_INVIS 130 
#define  PW_QUAD 129 
 int PW_REDFLAG ; 
#define  PW_REGEN 128 
 int /*<<< orphan*/  QGR_KEY_FLAG_PICKUP ; 
 int /*<<< orphan*/  QGR_KEY_FLIGHT ; 
 int /*<<< orphan*/  QGR_KEY_HASTE ; 
 int /*<<< orphan*/  QGR_KEY_INVIS ; 
 int /*<<< orphan*/  QGR_KEY_POWERUP ; 
 int /*<<< orphan*/  QGR_KEY_QUAD ; 
 int /*<<< orphan*/  QGR_KEY_REGEN ; 
 int /*<<< orphan*/  QGR_KEY_SUIT ; 
 TYPE_1__ level ; 
 int /*<<< orphan*/  trap_RankReportInt (int,int,int /*<<< orphan*/ ,int,int) ; 

void G_RankPickupPowerup( int self, int powerup )
{
	if( level.warmupTime != 0 )
	{
		// no reports during warmup period
		return;
	}
	
	// ctf flags are treated as powerups
	if( (powerup == PW_REDFLAG) || (powerup == PW_BLUEFLAG) )
	{
		trap_RankReportInt( self, -1, QGR_KEY_FLAG_PICKUP, 1, 1 );
		return;
	}

	trap_RankReportInt( self, -1, QGR_KEY_POWERUP, 1, 1 );
	
	switch( powerup )
	{
	case PW_QUAD:
		trap_RankReportInt( self, -1, QGR_KEY_QUAD, 1, 1 );
		break;
	case PW_BATTLESUIT:
		trap_RankReportInt( self, -1, QGR_KEY_SUIT, 1, 1 );
		break;
	case PW_HASTE:
		trap_RankReportInt( self, -1, QGR_KEY_HASTE, 1, 1 );
		break;
	case PW_INVIS:
		trap_RankReportInt( self, -1, QGR_KEY_INVIS, 1, 1 );
		break;
	case PW_REGEN:
		trap_RankReportInt( self, -1, QGR_KEY_REGEN, 1, 1 );
		break;
	case PW_FLIGHT:
		trap_RankReportInt( self, -1, QGR_KEY_FLIGHT, 1, 1 );
		break;
	default:
		break;
	}
}