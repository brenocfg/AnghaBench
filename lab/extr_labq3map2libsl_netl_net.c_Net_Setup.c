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
 int /*<<< orphan*/  WINS_Init () ; 
 int /*<<< orphan*/  WINS_MyAddress () ; 
 int /*<<< orphan*/  WinPrint (char*,int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int qtrue ; 

int Net_Setup( void ){
	if ( !WINS_Init() ) {
		return qfalse;
	}

	//
	WinPrint( "my address is %s\n", WINS_MyAddress() );
	//
	return qtrue;
}