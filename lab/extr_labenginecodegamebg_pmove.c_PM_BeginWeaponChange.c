#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ps; } ;
struct TYPE_3__ {int* stats; scalar_t__ weaponstate; int weaponTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_CHANGE_WEAPON ; 
 int /*<<< orphan*/  PM_AddEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_StartTorsoAnim (int /*<<< orphan*/ ) ; 
 size_t STAT_WEAPONS ; 
 int /*<<< orphan*/  TORSO_DROP ; 
 scalar_t__ WEAPON_DROPPING ; 
 int WP_NONE ; 
 int WP_NUM_WEAPONS ; 
 TYPE_2__* pm ; 

__attribute__((used)) static void PM_BeginWeaponChange( int weapon ) {
	if ( weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS ) {
		return;
	}

	if ( !( pm->ps->stats[STAT_WEAPONS] & ( 1 << weapon ) ) ) {
		return;
	}
	
	if ( pm->ps->weaponstate == WEAPON_DROPPING ) {
		return;
	}

	PM_AddEvent( EV_CHANGE_WEAPON );
	pm->ps->weaponstate = WEAPON_DROPPING;
	pm->ps->weaponTime += 200;
	PM_StartTorsoAnim( TORSO_DROP );
}