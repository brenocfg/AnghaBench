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
struct TYPE_6__ {int weaponSelect; TYPE_1__* snap; int /*<<< orphan*/  time; int /*<<< orphan*/  weaponSelectTime; } ;
struct TYPE_5__ {int pm_flags; int* stats; } ;
struct TYPE_4__ {TYPE_2__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Argv (int) ; 
 int MAX_WEAPONS ; 
 int PMF_FOLLOW ; 
 size_t STAT_WEAPONS ; 
 int atoi (int /*<<< orphan*/ ) ; 
 TYPE_3__ cg ; 

void CG_Weapon_f( void ) {
	int		num;

	if ( !cg.snap ) {
		return;
	}
	if ( cg.snap->ps.pm_flags & PMF_FOLLOW ) {
		return;
	}

	num = atoi( CG_Argv( 1 ) );

	if ( num < 1 || num > MAX_WEAPONS-1 ) {
		return;
	}

	cg.weaponSelectTime = cg.time;

	if ( ! ( cg.snap->ps.stats[STAT_WEAPONS] & ( 1 << num ) ) ) {
		return;		// don't have the weapon
	}

	cg.weaponSelect = num;
}