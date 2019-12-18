#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ giTag; } ;
struct TYPE_6__ {int buttons; int weapon; } ;
struct TYPE_9__ {TYPE_2__* ps; int /*<<< orphan*/  gauntletHit; TYPE_1__ cmd; } ;
struct TYPE_8__ {scalar_t__ msec; } ;
struct TYPE_7__ {int pm_flags; scalar_t__* persistant; size_t* stats; int weapon; scalar_t__ weaponTime; scalar_t__ weaponstate; int* ammo; scalar_t__* powerups; } ;

/* Variables and functions */
 int BUTTON_ATTACK ; 
 int BUTTON_USE_HOLDABLE ; 
 scalar_t__ EV_FIRE_WEAPON ; 
 scalar_t__ EV_NOAMMO ; 
 scalar_t__ EV_USE_ITEM0 ; 
 scalar_t__ HI_MEDKIT ; 
 size_t PERS_TEAM ; 
 int PMF_RESPAWNED ; 
 int PMF_USE_ITEM_HELD ; 
 int /*<<< orphan*/  PM_AddEvent (scalar_t__) ; 
 int /*<<< orphan*/  PM_BeginWeaponChange (int) ; 
 int /*<<< orphan*/  PM_FinishWeaponChange () ; 
 int /*<<< orphan*/  PM_StartTorsoAnim (int /*<<< orphan*/ ) ; 
 scalar_t__ PW_AMMOREGEN ; 
 size_t PW_HASTE ; 
 scalar_t__ PW_SCOUT ; 
 size_t STAT_HEALTH ; 
 size_t STAT_HOLDABLE_ITEM ; 
 size_t STAT_MAX_HEALTH ; 
 size_t STAT_PERSISTANT_POWERUP ; 
 scalar_t__ TEAM_SPECTATOR ; 
 int /*<<< orphan*/  TORSO_ATTACK ; 
 int /*<<< orphan*/  TORSO_ATTACK2 ; 
 int /*<<< orphan*/  TORSO_STAND ; 
 int /*<<< orphan*/  TORSO_STAND2 ; 
 scalar_t__ WEAPON_DROPPING ; 
 scalar_t__ WEAPON_FIRING ; 
 scalar_t__ WEAPON_RAISING ; 
 void* WEAPON_READY ; 
#define  WP_BFG 140 
#define  WP_CHAINGUN 139 
#define  WP_GAUNTLET 138 
#define  WP_GRAPPLING_HOOK 137 
#define  WP_GRENADE_LAUNCHER 136 
#define  WP_LIGHTNING 135 
#define  WP_MACHINEGUN 134 
#define  WP_NAILGUN 133 
 int WP_NONE ; 
#define  WP_PLASMAGUN 132 
#define  WP_PROX_LAUNCHER 131 
#define  WP_RAILGUN 130 
#define  WP_ROCKET_LAUNCHER 129 
#define  WP_SHOTGUN 128 
 TYPE_5__* bg_itemlist ; 
 TYPE_4__* pm ; 
 TYPE_3__ pml ; 

__attribute__((used)) static void PM_Weapon( void ) {
	int		addTime;

	// don't allow attack until all buttons are up
	if ( pm->ps->pm_flags & PMF_RESPAWNED ) {
		return;
	}

	// ignore if spectator
	if ( pm->ps->persistant[PERS_TEAM] == TEAM_SPECTATOR ) {
		return;
	}

	// check for dead player
	if ( pm->ps->stats[STAT_HEALTH] <= 0 ) {
		pm->ps->weapon = WP_NONE;
		return;
	}

	// check for item using
	if ( pm->cmd.buttons & BUTTON_USE_HOLDABLE ) {
		if ( ! ( pm->ps->pm_flags & PMF_USE_ITEM_HELD ) ) {
			if ( bg_itemlist[pm->ps->stats[STAT_HOLDABLE_ITEM]].giTag == HI_MEDKIT
				&& pm->ps->stats[STAT_HEALTH] >= (pm->ps->stats[STAT_MAX_HEALTH] + 25) ) {
				// don't use medkit if at max health
			} else {
				pm->ps->pm_flags |= PMF_USE_ITEM_HELD;
				PM_AddEvent( EV_USE_ITEM0 + bg_itemlist[pm->ps->stats[STAT_HOLDABLE_ITEM]].giTag );
				pm->ps->stats[STAT_HOLDABLE_ITEM] = 0;
			}
			return;
		}
	} else {
		pm->ps->pm_flags &= ~PMF_USE_ITEM_HELD;
	}


	// make weapon function
	if ( pm->ps->weaponTime > 0 ) {
		pm->ps->weaponTime -= pml.msec;
	}

	// check for weapon change
	// can't change if weapon is firing, but can change
	// again if lowering or raising
	if ( pm->ps->weaponTime <= 0 || pm->ps->weaponstate != WEAPON_FIRING ) {
		if ( pm->ps->weapon != pm->cmd.weapon ) {
			PM_BeginWeaponChange( pm->cmd.weapon );
		}
	}

	if ( pm->ps->weaponTime > 0 ) {
		return;
	}

	// change weapon if time
	if ( pm->ps->weaponstate == WEAPON_DROPPING ) {
		PM_FinishWeaponChange();
		return;
	}

	if ( pm->ps->weaponstate == WEAPON_RAISING ) {
		pm->ps->weaponstate = WEAPON_READY;
		if ( pm->ps->weapon == WP_GAUNTLET ) {
			PM_StartTorsoAnim( TORSO_STAND2 );
		} else {
			PM_StartTorsoAnim( TORSO_STAND );
		}
		return;
	}

	// check for fire
	if ( ! (pm->cmd.buttons & BUTTON_ATTACK) ) {
		pm->ps->weaponTime = 0;
		pm->ps->weaponstate = WEAPON_READY;
		return;
	}

	// start the animation even if out of ammo
	if ( pm->ps->weapon == WP_GAUNTLET ) {
		// the guantlet only "fires" when it actually hits something
		if ( !pm->gauntletHit ) {
			pm->ps->weaponTime = 0;
			pm->ps->weaponstate = WEAPON_READY;
			return;
		}
		PM_StartTorsoAnim( TORSO_ATTACK2 );
	} else {
		PM_StartTorsoAnim( TORSO_ATTACK );
	}

	pm->ps->weaponstate = WEAPON_FIRING;

	// check for out of ammo
	if ( ! pm->ps->ammo[ pm->ps->weapon ] ) {
		PM_AddEvent( EV_NOAMMO );
		pm->ps->weaponTime += 500;
		return;
	}

	// take an ammo away if not infinite
	if ( pm->ps->ammo[ pm->ps->weapon ] != -1 ) {
		pm->ps->ammo[ pm->ps->weapon ]--;
	}

	// fire weapon
	PM_AddEvent( EV_FIRE_WEAPON );

	switch( pm->ps->weapon ) {
	default:
	case WP_GAUNTLET:
		addTime = 400;
		break;
	case WP_LIGHTNING:
		addTime = 50;
		break;
	case WP_SHOTGUN:
		addTime = 1000;
		break;
	case WP_MACHINEGUN:
		addTime = 100;
		break;
	case WP_GRENADE_LAUNCHER:
		addTime = 800;
		break;
	case WP_ROCKET_LAUNCHER:
		addTime = 800;
		break;
	case WP_PLASMAGUN:
		addTime = 100;
		break;
	case WP_RAILGUN:
		addTime = 1500;
		break;
	case WP_BFG:
		addTime = 200;
		break;
	case WP_GRAPPLING_HOOK:
		addTime = 400;
		break;
#ifdef MISSIONPACK
	case WP_NAILGUN:
		addTime = 1000;
		break;
	case WP_PROX_LAUNCHER:
		addTime = 800;
		break;
	case WP_CHAINGUN:
		addTime = 30;
		break;
#endif
	}

#ifdef MISSIONPACK
	if( bg_itemlist[pm->ps->stats[STAT_PERSISTANT_POWERUP]].giTag == PW_SCOUT ) {
		addTime /= 1.5;
	}
	else
	if( bg_itemlist[pm->ps->stats[STAT_PERSISTANT_POWERUP]].giTag == PW_AMMOREGEN ) {
		addTime /= 1.3;
	}
	else
#endif
	if ( pm->ps->powerups[PW_HASTE] ) {
		addTime /= 1.3;
	}

	pm->ps->weaponTime += addTime;
}