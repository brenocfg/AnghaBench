#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double vidWidth; double vidHeight; } ;
struct TYPE_3__ {double xscale; double yscale; double bias; scalar_t__ menusp; int /*<<< orphan*/ * activemenu; TYPE_2__ glconfig; } ;

/* Variables and functions */
 int /*<<< orphan*/  Menu_Cache () ; 
 int /*<<< orphan*/  UI_InitGameinfo () ; 
 int /*<<< orphan*/  UI_RegisterCvars () ; 
 int /*<<< orphan*/  trap_GetGlconfig (TYPE_2__*) ; 
 TYPE_1__ uis ; 

void UI_Init( void ) {
	UI_RegisterCvars();

	UI_InitGameinfo();

	// cache redundant calulations
	trap_GetGlconfig( &uis.glconfig );

	// for 640x480 virtualized screen
	uis.xscale = uis.glconfig.vidWidth * (1.0/640.0);
	uis.yscale = uis.glconfig.vidHeight * (1.0/480.0);
	if ( uis.glconfig.vidWidth * 480 > uis.glconfig.vidHeight * 640 ) {
		// wide screen
		uis.bias = 0.5 * ( uis.glconfig.vidWidth - ( uis.glconfig.vidHeight * (640.0/480.0) ) );
		uis.xscale = uis.yscale;
	}
	else {
		// no wide screen
		uis.bias = 0;
	}

	// initialize the menu system
	Menu_Cache();

	uis.activemenu = NULL;
	uis.menusp     = 0;
}