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
struct TYPE_6__ {scalar_t__ giType; scalar_t__ giTag; } ;
struct TYPE_5__ {int itemPickup; scalar_t__ weaponSelect; int /*<<< orphan*/  time; int /*<<< orphan*/  weaponSelectTime; int /*<<< orphan*/  itemPickupBlendTime; int /*<<< orphan*/  itemPickupTime; } ;
struct TYPE_4__ {scalar_t__ integer; } ;

/* Variables and functions */
 scalar_t__ IT_WEAPON ; 
 scalar_t__ WP_MACHINEGUN ; 
 TYPE_3__* bg_itemlist ; 
 TYPE_2__ cg ; 
 TYPE_1__ cg_autoswitch ; 

__attribute__((used)) static void CG_ItemPickup( int itemNum ) {
	cg.itemPickup = itemNum;
	cg.itemPickupTime = cg.time;
	cg.itemPickupBlendTime = cg.time;
	// see if it should be the grabbed weapon
	if ( bg_itemlist[itemNum].giType == IT_WEAPON ) {
		// select it immediately
		if ( cg_autoswitch.integer && bg_itemlist[itemNum].giTag != WP_MACHINEGUN ) {
			cg.weaponSelectTime = cg.time;
			cg.weaponSelect = bg_itemlist[itemNum].giTag;
		}
	}

}