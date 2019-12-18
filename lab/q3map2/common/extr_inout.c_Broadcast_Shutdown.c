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
 int /*<<< orphan*/  Net_Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sys_Printf (char*) ; 
 int /*<<< orphan*/ * brdcst_socket ; 

void Broadcast_Shutdown(){
	if ( brdcst_socket ) {
		Sys_Printf( "Disconnecting\n" );
		Net_Disconnect( brdcst_socket );
		brdcst_socket = NULL;
	}
}