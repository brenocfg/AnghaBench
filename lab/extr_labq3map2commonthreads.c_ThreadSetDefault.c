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
 int /*<<< orphan*/  Sys_Printf (char*,int) ; 
 int numthreads ; 

void ThreadSetDefault( void ){
	if ( numthreads == -1 ) { // not set manually
		/* default to one thread, only multi-thread when specifically told to */
		numthreads = 1;
	}
	if ( numthreads > 1 ) {
		Sys_Printf( "threads: %d\n", numthreads );
	}
}