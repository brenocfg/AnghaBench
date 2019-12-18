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
typedef  int WORD ;

/* Variables and functions */
 char COLOR_WHITE ; 
 size_t ColorIndex (char) ; 
 int FOREGROUND_BLUE ; 
 int FOREGROUND_GREEN ; 
 int FOREGROUND_INTENSITY ; 
 int FOREGROUND_RED ; 
 float** g_color_table ; 
 int qconsole_attrib ; 
 int qconsole_backgroundAttrib ; 

__attribute__((used)) static WORD CON_ColorCharToAttrib( char color ) {
	WORD attrib;

	if ( color == COLOR_WHITE )
	{
		// use console's foreground and background colors
		attrib = qconsole_attrib;
	}
	else
	{
		float *rgba = g_color_table[ ColorIndex( color ) ];

		// set foreground color
		attrib = ( rgba[0] >= 0.5 ? FOREGROUND_RED		: 0 ) |
				( rgba[1] >= 0.5 ? FOREGROUND_GREEN		: 0 ) |
				( rgba[2] >= 0.5 ? FOREGROUND_BLUE		: 0 ) |
				( rgba[3] >= 0.5 ? FOREGROUND_INTENSITY	: 0 );

		// use console's background color
		attrib |= qconsole_backgroundAttrib;
	}

	return attrib;
}