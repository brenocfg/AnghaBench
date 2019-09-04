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
struct TYPE_4__ {int id; scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_5__ {int numitems; char const** itemnames; TYPE_1__ generic; } ;
struct TYPE_6__ {int numBots; TYPE_2__ list; scalar_t__ bots; } ;

/* Variables and functions */
#define  ID_LIST_BOTS 130 
#define  ID_LIST_CTF_ORDERS 129 
#define  ID_LIST_TEAM_ORDERS 128 
 int NUM_CTF_ORDERS ; 
 int NUM_TEAM_ORDERS ; 
 int PROP_HEIGHT ; 
 char const** ctfOrders ; 
 char const** teamOrders ; 
 TYPE_3__ teamOrdersMenuInfo ; 

__attribute__((used)) static void UI_TeamOrdersMenu_SetList( int id ) {
	switch( id ) {
	default:
	case ID_LIST_BOTS:
		teamOrdersMenuInfo.list.generic.id = id;
		teamOrdersMenuInfo.list.numitems = teamOrdersMenuInfo.numBots;
		teamOrdersMenuInfo.list.itemnames = (const char **)teamOrdersMenuInfo.bots;
		 break;

	case ID_LIST_CTF_ORDERS:
		teamOrdersMenuInfo.list.generic.id = id;
		teamOrdersMenuInfo.list.numitems = NUM_CTF_ORDERS;
		teamOrdersMenuInfo.list.itemnames = ctfOrders;
		break;

	case ID_LIST_TEAM_ORDERS:
		teamOrdersMenuInfo.list.generic.id = id;
		teamOrdersMenuInfo.list.numitems = NUM_TEAM_ORDERS;
		teamOrdersMenuInfo.list.itemnames = teamOrders;
		break;
	}

	teamOrdersMenuInfo.list.generic.bottom = teamOrdersMenuInfo.list.generic.top + teamOrdersMenuInfo.list.numitems * PROP_HEIGHT;
}