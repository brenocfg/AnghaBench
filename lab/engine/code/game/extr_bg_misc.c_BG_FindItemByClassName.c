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
struct TYPE_4__ {scalar_t__ classname; } ;
typedef  TYPE_1__ gitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  BG_UpdateItems () ; 
 int /*<<< orphan*/  Q_stricmp (scalar_t__,char const*) ; 
 int bg_defaultNumItems ; 
 TYPE_1__* bg_itemlist ; 
 scalar_t__ dmlab_finditem (char const*,int*) ; 

gitem_t *BG_FindItemByClassName( const char *classname ) {
	gitem_t	*it;
	int idx;

	for ( it = bg_itemlist + 1 ; it->classname ; it++ ) {
		if ( !Q_stricmp( it->classname, classname ) )
			return it;
	}

	if ( dmlab_finditem( classname, &idx ) ) {
		BG_UpdateItems( );
		return &bg_itemlist[bg_defaultNumItems + idx];
	}

	return NULL;
}