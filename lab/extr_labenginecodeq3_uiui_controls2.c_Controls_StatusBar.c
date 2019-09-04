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
 double SCREEN_HEIGHT ; 
 double SCREEN_WIDTH ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawString (double,double,char*,int,int /*<<< orphan*/ ) ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  colorBlack ; 

__attribute__((used)) static void Controls_StatusBar( void *self )
{
	UI_DrawString(SCREEN_WIDTH * 0.50, SCREEN_HEIGHT * 0.80, "Use Arrow Keys or CLICK to change", UI_SMALLFONT|UI_CENTER, colorBlack );
}