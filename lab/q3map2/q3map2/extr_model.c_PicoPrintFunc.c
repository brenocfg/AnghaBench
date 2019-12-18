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
 int /*<<< orphan*/  Error (char*,char const*) ; 
#define  PICO_ERROR 132 
#define  PICO_FATAL 131 
#define  PICO_NORMAL 130 
#define  PICO_VERBOSE 129 
#define  PICO_WARNING 128 
 int /*<<< orphan*/  SYS_ERR ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,char const*) ; 

void PicoPrintFunc( int level, const char *str ){
	if ( str == NULL ) {
		return;
	}
	switch ( level )
	{
	case PICO_NORMAL:
		Sys_Printf( "%s\n", str );
		break;

	case PICO_VERBOSE:
		Sys_FPrintf( SYS_VRB, "%s\n", str );
		break;

	case PICO_WARNING:
		Sys_FPrintf( SYS_WRN, "WARNING: %s\n", str );
		break;

	case PICO_ERROR:
		Sys_FPrintf( SYS_ERR, "ERROR: %s\n", str );
		break;

	case PICO_FATAL:
		Error( "ERROR: %s\n", str );
		break;
	}
}