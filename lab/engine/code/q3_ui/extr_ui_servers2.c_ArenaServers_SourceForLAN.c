#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int AS_FAVORITES ; 
 int AS_GLOBAL ; 
 int AS_LOCAL ; 
#define  UIAS_FAVORITES 135 
#define  UIAS_GLOBAL0 134 
#define  UIAS_GLOBAL1 133 
#define  UIAS_GLOBAL2 132 
#define  UIAS_GLOBAL3 131 
#define  UIAS_GLOBAL4 130 
#define  UIAS_GLOBAL5 129 
#define  UIAS_LOCAL 128 
 int g_servertype ; 

int ArenaServers_SourceForLAN(void) {
	switch( g_servertype ) {
	default:
	case UIAS_LOCAL:
		return AS_LOCAL;
	case UIAS_GLOBAL0:
	case UIAS_GLOBAL1:
	case UIAS_GLOBAL2:
	case UIAS_GLOBAL3:
	case UIAS_GLOBAL4:
	case UIAS_GLOBAL5:
		return AS_GLOBAL;
	case UIAS_FAVORITES:
		return AS_FAVORITES;
	}
}