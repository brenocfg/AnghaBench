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
 double ARRAY_LEN (char const**) ; 
 double PROP_HEIGHT ; 
 double PROP_SMALL_SIZE_SCALE ; 
 double SCREEN_HEIGHT ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawString (int,int,char*,int,int /*<<< orphan*/ ) ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  color_black ; 
 int /*<<< orphan*/  color_blue ; 

__attribute__((used)) static void UI_CreditMenu_Draw_ioq3( void ) {
	int		y;
	int		i;

	// These are all people that have made commits to Subversion, and thus
	//  probably incomplete.
	// (These are in alphabetical order, for the defense of everyone's egos.)
	static const char *names[] = {
		"Tim Angus",
		"James Canete",
		"Vincent Cojot",
		"Ryan C. Gordon",
		"Aaron Gyes",
		"Zack Middleton",
		"Ludwig Nussel",
		"Julian Priestley",
		"Scirocco Six",
		"Thilo Schulz",
		"Zachary J. Slater",
		"Tony J. White",
		"...and many, many others!",  // keep this one last.
		NULL
	};

	// Center text vertically on the screen
	y = (SCREEN_HEIGHT - ARRAY_LEN(names) * (1.42 * PROP_HEIGHT * PROP_SMALL_SIZE_SCALE)) / 2;

	UI_DrawProportionalString( 320, y, "ioquake3 contributors:", UI_CENTER|UI_SMALLFONT, color_black );
	y += 1.42 * PROP_HEIGHT * PROP_SMALL_SIZE_SCALE;

	for (i = 0; names[i]; i++) {
		UI_DrawProportionalString( 320, y, names[i], UI_CENTER|UI_SMALLFONT, color_black );
		y += 1.42 * PROP_HEIGHT * PROP_SMALL_SIZE_SCALE;
	}

	UI_DrawString( 320, 459, "http://www.ioquake3.org/", UI_CENTER|UI_SMALLFONT, color_blue );
}