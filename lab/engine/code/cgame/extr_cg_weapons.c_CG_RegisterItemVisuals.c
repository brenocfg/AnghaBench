#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void** models; int /*<<< orphan*/  icon; scalar_t__ registered; } ;
typedef  TYPE_1__ itemInfo_t ;
struct TYPE_7__ {scalar_t__ giType; scalar_t__* world_model; int /*<<< orphan*/  giTag; int /*<<< orphan*/  icon; } ;
typedef  TYPE_2__ gitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Error (char*,int,int) ; 
 int /*<<< orphan*/  CG_RegisterWeapon (int /*<<< orphan*/ ) ; 
 scalar_t__ IT_ARMOR ; 
 scalar_t__ IT_HEALTH ; 
 scalar_t__ IT_HOLDABLE ; 
 scalar_t__ IT_POWERUP ; 
 scalar_t__ IT_WEAPON ; 
 TYPE_2__* bg_itemlist ; 
 int bg_numItems ; 
 TYPE_1__* cg_items ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qtrue ; 
 void* trap_R_RegisterModel (scalar_t__) ; 
 int /*<<< orphan*/  trap_R_RegisterShader (int /*<<< orphan*/ ) ; 

void CG_RegisterItemVisuals( int itemNum ) {
	itemInfo_t		*itemInfo;
	gitem_t			*item;

	if ( itemNum < 0 || itemNum >= bg_numItems ) {
		CG_Error( "CG_RegisterItemVisuals: itemNum %d out of range [0-%d]", itemNum, bg_numItems-1 );
	}

	itemInfo = &cg_items[ itemNum ];
	if ( itemInfo->registered ) {
		return;
	}

	item = &bg_itemlist[ itemNum ];

	memset( itemInfo, 0, sizeof( *itemInfo ) );
	itemInfo->registered = qtrue;

	itemInfo->models[0] = trap_R_RegisterModel( item->world_model[0] );

	itemInfo->icon = trap_R_RegisterShader( item->icon );

	if ( item->giType == IT_WEAPON ) {
		CG_RegisterWeapon( item->giTag );
	}

	//
	// powerups have an accompanying ring or sphere
	//
	if ( item->giType == IT_POWERUP || item->giType == IT_HEALTH || 
		item->giType == IT_ARMOR || item->giType == IT_HOLDABLE ) {
		if ( item->world_model[1] ) {
			itemInfo->models[1] = trap_R_RegisterModel( item->world_model[1] );
		}
	}
}