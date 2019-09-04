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
struct TYPE_2__ {char* demoName; int /*<<< orphan*/  demofile; scalar_t__ spDemoRecording; int /*<<< orphan*/  demorecording; } ;

/* Variables and functions */
 int FS_FTell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCR_DrawStringExt (int,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ clc ; 
 int /*<<< orphan*/ * g_color_table ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int strlen (char*) ; 

void SCR_DrawDemoRecording( void ) {
	char	string[1024];
	int		pos;

	if ( !clc.demorecording ) {
		return;
	}
	if ( clc.spDemoRecording ) {
		return;
	}

	pos = FS_FTell( clc.demofile );
	sprintf( string, "RECORDING %s: %ik", clc.demoName, pos / 1024 );

	SCR_DrawStringExt( 320 - strlen( string ) * 4, 20, 8, string, g_color_table[7], qtrue, qfalse );
}