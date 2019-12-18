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
typedef  enum mandoc_esc { ____Placeholder_mandoc_esc } mandoc_esc ;

/* Variables and functions */
 int ESCAPE_ERROR ; 
 int ESCAPE_FONTBI ; 
 int ESCAPE_FONTBOLD ; 
 int ESCAPE_FONTCW ; 
 int ESCAPE_FONTITALIC ; 
 int ESCAPE_FONTPREV ; 
 int ESCAPE_FONTROMAN ; 

enum mandoc_esc
mandoc_font(const char *cp, int sz)
{
	switch (sz) {
	case 0:
		return ESCAPE_FONTPREV;
	case 1:
		switch (cp[0]) {
		case 'B':
		case '3':
			return ESCAPE_FONTBOLD;
		case 'I':
		case '2':
			return ESCAPE_FONTITALIC;
		case 'P':
			return ESCAPE_FONTPREV;
		case 'R':
		case '1':
			return ESCAPE_FONTROMAN;
		case '4':
			return ESCAPE_FONTBI;
		default:
			return ESCAPE_ERROR;
		}
	case 2:
		switch (cp[0]) {
		case 'B':
			switch (cp[1]) {
			case 'I':
				return ESCAPE_FONTBI;
			default:
				return ESCAPE_ERROR;
			}
		case 'C':
			switch (cp[1]) {
			case 'B':
				return ESCAPE_FONTBOLD;
			case 'I':
				return ESCAPE_FONTITALIC;
			case 'R':
			case 'W':
				return ESCAPE_FONTCW;
			default:
				return ESCAPE_ERROR;
			}
		default:
			return ESCAPE_ERROR;
		}
	default:
		return ESCAPE_ERROR;
	}
}