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
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ giType; int giTag; } ;
typedef  TYPE_1__ gitem_t ;
struct TYPE_19__ {size_t modelindex; int /*<<< orphan*/  eFlags; } ;
struct TYPE_14__ {scalar_t__ miscTime; TYPE_9__ currentState; } ;
typedef  TYPE_2__ centity_t ;
struct TYPE_18__ {scalar_t__* persistant; int* stats; int* ammo; } ;
struct TYPE_17__ {scalar_t__ time; TYPE_8__ predictedPlayerState; } ;
struct TYPE_16__ {int /*<<< orphan*/  integer; } ;
struct TYPE_15__ {scalar_t__ gametype; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_AddPredictableEventToPlayerstate (int /*<<< orphan*/ ,size_t,TYPE_8__*) ; 
 int /*<<< orphan*/  BG_CanItemBeGrabbed (scalar_t__,TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/  BG_PlayerTouchesItem (TYPE_8__*,TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  EF_NODRAW ; 
 int /*<<< orphan*/  EV_ITEM_PICKUP ; 
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ IT_TEAM ; 
 scalar_t__ IT_WEAPON ; 
 size_t PERS_TEAM ; 
 int PW_BLUEFLAG ; 
 int PW_NEUTRALFLAG ; 
 int PW_REDFLAG ; 
 size_t STAT_WEAPONS ; 
 scalar_t__ TEAM_BLUE ; 
 scalar_t__ TEAM_RED ; 
 TYPE_1__* bg_itemlist ; 
 TYPE_5__ cg ; 
 TYPE_4__ cg_predictItems ; 
 TYPE_3__ cgs ; 

__attribute__((used)) static void CG_TouchItem( centity_t *cent ) {
	gitem_t		*item;

	if ( !cg_predictItems.integer ) {
		return;
	}
	if ( !BG_PlayerTouchesItem( &cg.predictedPlayerState, &cent->currentState, cg.time ) ) {
		return;
	}

	// never pick an item up twice in a prediction
	if ( cent->miscTime == cg.time ) {
		return;
	}

	if ( !BG_CanItemBeGrabbed( cgs.gametype, &cent->currentState, &cg.predictedPlayerState ) ) {
		return;		// can't hold it
	}

	item = &bg_itemlist[ cent->currentState.modelindex ];

	// Special case for flags.  
	// We don't predict touching our own flag
#ifdef MISSIONPACK
	if( cgs.gametype == GT_1FCTF ) {
		if( item->giType == IT_TEAM && item->giTag != PW_NEUTRALFLAG ) {
			return;
		}
	}
#endif
	if( cgs.gametype == GT_CTF ) {
		if (cg.predictedPlayerState.persistant[PERS_TEAM] == TEAM_RED &&
			item->giType == IT_TEAM && item->giTag == PW_REDFLAG)
			return;
		if (cg.predictedPlayerState.persistant[PERS_TEAM] == TEAM_BLUE &&
			item->giType == IT_TEAM && item->giTag == PW_BLUEFLAG)
			return;
	}

	// grab it
	BG_AddPredictableEventToPlayerstate( EV_ITEM_PICKUP, cent->currentState.modelindex , &cg.predictedPlayerState);

	// remove it from the frame so it won't be drawn
	cent->currentState.eFlags |= EF_NODRAW;

	// don't touch it again this prediction
	cent->miscTime = cg.time;

	// if it's a weapon, give them some predicted ammo so the autoswitch will work
	if ( item->giType == IT_WEAPON ) {
		cg.predictedPlayerState.stats[ STAT_WEAPONS ] |= 1 << item->giTag;
		if ( !cg.predictedPlayerState.ammo[ item->giTag ] ) {
			cg.predictedPlayerState.ammo[ item->giTag ] = 1;
		}
	}
}