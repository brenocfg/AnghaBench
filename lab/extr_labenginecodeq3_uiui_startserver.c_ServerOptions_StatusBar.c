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
struct TYPE_2__ {int id; } ;
typedef  TYPE_1__ menucommon_s ;

/* Variables and functions */
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawString (int,int,char*,int,int /*<<< orphan*/ ) ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  colorWhite ; 

__attribute__((used)) static void ServerOptions_StatusBar( void* ptr ) {
	switch( ((menucommon_s*)ptr)->id ) {
	default:
		UI_DrawString( 320, 440, "0 = NO LIMIT", UI_CENTER|UI_SMALLFONT, colorWhite );
		break;
	}
}