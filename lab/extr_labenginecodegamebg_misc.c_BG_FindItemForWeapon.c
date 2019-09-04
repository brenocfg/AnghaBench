#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ weapon_t ;
struct TYPE_4__ {scalar_t__ giType; scalar_t__ giTag; scalar_t__ classname; } ;
typedef  TYPE_1__ gitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 scalar_t__ IT_WEAPON ; 
 TYPE_1__* bg_itemlist ; 

gitem_t	*BG_FindItemForWeapon( weapon_t weapon ) {
	gitem_t	*it;
	
	for ( it = bg_itemlist + 1 ; it->classname ; it++) {
		if ( it->giType == IT_WEAPON && it->giTag == weapon ) {
			return it;
		}
	}

	Com_Error( ERR_DROP, "Couldn't find item for weapon %i", weapon);
	return NULL;
}