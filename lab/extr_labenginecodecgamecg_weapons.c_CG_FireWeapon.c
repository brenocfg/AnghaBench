#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  (* ejectBrassFunc ) (TYPE_5__*) ;scalar_t__* flashSound; } ;
typedef  TYPE_3__ weaponInfo_t ;
struct TYPE_16__ {size_t weapon; int powerups; int /*<<< orphan*/  number; } ;
typedef  TYPE_4__ entityState_t ;
struct TYPE_13__ {int /*<<< orphan*/  railFireTime; scalar_t__ lightningFiring; } ;
struct TYPE_17__ {TYPE_4__ currentState; TYPE_1__ pe; int /*<<< orphan*/  muzzleFlashTime; } ;
typedef  TYPE_5__ centity_t ;
struct TYPE_19__ {scalar_t__ integer; } ;
struct TYPE_14__ {scalar_t__ quadSound; } ;
struct TYPE_18__ {TYPE_2__ media; } ;
struct TYPE_12__ {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Error (char*) ; 
 int /*<<< orphan*/  CHAN_ITEM ; 
 int /*<<< orphan*/  CHAN_WEAPON ; 
 int PW_QUAD ; 
 size_t WP_LIGHTNING ; 
 size_t WP_NONE ; 
 size_t WP_NUM_WEAPONS ; 
 size_t WP_RAILGUN ; 
 TYPE_10__ cg ; 
 TYPE_9__ cg_brassTime ; 
 TYPE_3__* cg_weapons ; 
 TYPE_7__ cgs ; 
 int rand () ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  trap_S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void CG_FireWeapon( centity_t *cent ) {
	entityState_t *ent;
	int				c;
	weaponInfo_t	*weap;

	ent = &cent->currentState;
	if ( ent->weapon == WP_NONE ) {
		return;
	}
	if ( ent->weapon >= WP_NUM_WEAPONS ) {
		CG_Error( "CG_FireWeapon: ent->weapon >= WP_NUM_WEAPONS" );
		return;
	}
	weap = &cg_weapons[ ent->weapon ];

	// mark the entity as muzzle flashing, so when it is added it will
	// append the flash to the weapon model
	cent->muzzleFlashTime = cg.time;

	// lightning gun only does this this on initial press
	if ( ent->weapon == WP_LIGHTNING ) {
		if ( cent->pe.lightningFiring ) {
			return;
		}
	}

	if( ent->weapon == WP_RAILGUN ) {
		cent->pe.railFireTime = cg.time;
	}

	// play quad sound if needed
	if ( cent->currentState.powerups & ( 1 << PW_QUAD ) ) {
		trap_S_StartSound (NULL, cent->currentState.number, CHAN_ITEM, cgs.media.quadSound );
	}

	// play a sound
	for ( c = 0 ; c < 4 ; c++ ) {
		if ( !weap->flashSound[c] ) {
			break;
		}
	}
	if ( c > 0 ) {
		c = rand() % c;
		if ( weap->flashSound[c] )
		{
			trap_S_StartSound( NULL, ent->number, CHAN_WEAPON, weap->flashSound[c] );
		}
	}

	// do brass ejection
	if ( weap->ejectBrassFunc && cg_brassTime.integer > 0 ) {
		weap->ejectBrassFunc( cent );
	}
}