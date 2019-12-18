#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ giType; int /*<<< orphan*/ * world_model; scalar_t__ classname; } ;
typedef  TYPE_1__ gitem_t ;

/* Variables and functions */
 scalar_t__ IT_WEAPON ; 
 TYPE_1__* bg_itemlist ; 
 int /*<<< orphan*/  trap_R_RegisterModel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Controls_InitWeapons( void ) {
	gitem_t *	item;

	for ( item = bg_itemlist + 1 ; item->classname ; item++ ) {
		if ( item->giType != IT_WEAPON ) {
			continue;
		}
		trap_R_RegisterModel( item->world_model[0] );
	}
}