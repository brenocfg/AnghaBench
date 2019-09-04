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
typedef  scalar_t__ time_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  SwapBSPFile () ; 
 TYPE_1__* game ; 
 int /*<<< orphan*/  remove (char const*) ; 
 int /*<<< orphan*/  rename (char*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,int) ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 

void WriteBSPFile( const char *filename ){
	char tempname[ 1024 ];
	time_t tm;


	/* dummy check */
	if ( game == NULL || game->write == NULL ) {
		Error( "WriteBSPFile: unsupported BSP file format" );
	}

	/* make fake temp name so existing bsp file isn't damaged in case write process fails */
	time( &tm );
	sprintf( tempname, "%s.%08X", filename, (int) tm );

	/* byteswap, write the bsp, then swap back so it can be manipulated further */
	SwapBSPFile();
	game->write( tempname );
	SwapBSPFile();

	/* replace existing bsp file */
	remove( filename );
	rename( tempname, filename );
}