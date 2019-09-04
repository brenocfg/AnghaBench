#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* load ) (char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  SwapBSPFile () ; 
 TYPE_1__* game ; 
 int /*<<< orphan*/  stub1 (char const*) ; 

void LoadBSPFile( const char *filename ){
	/* dummy check */
	if ( game == NULL || game->load == NULL ) {
		Error( "LoadBSPFile: unsupported BSP file format" );
	}

	/* load it, then byte swap the in-memory version */
	game->load( filename );
	SwapBSPFile();
}