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
 int BACKGROUND_ALL ; 
 int BACKGROUND_BLUE ; 
 int BACKGROUND_GREEN ; 
 int BACKGROUND_INTENSITY ; 
 int BACKGROUND_RED ; 
 int FOREGROUND_ALL ; 
 int FOREGROUND_BLUE ; 
 int FOREGROUND_GREEN ; 
 int FOREGROUND_INTENSITY ; 
 int FOREGROUND_RED ; 
 int attr ; 
 int /*<<< orphan*/  erase_in_line () ; 
 int negative ; 
 int plain_attr ; 
 int /*<<< orphan*/  set_console_attr () ; 

__attribute__((used)) static void set_attr(char func, const int *params, int paramlen)
{
	int i;
	switch (func) {
	case 'm':
		for (i = 0; i < paramlen; i++) {
			switch (params[i]) {
			case 0: /* reset */
				attr = plain_attr;
				negative = 0;
				break;
			case 1: /* bold */
				attr |= FOREGROUND_INTENSITY;
				break;
			case 2:  /* faint */
			case 22: /* normal */
				attr &= ~FOREGROUND_INTENSITY;
				break;
			case 3:  /* italic */
				/* Unsupported */
				break;
			case 4:  /* underline */
			case 21: /* double underline */
				/* Wikipedia says this flag does nothing */
				/* Furthermore, mingw doesn't define this flag
				attr |= COMMON_LVB_UNDERSCORE; */
				break;
			case 24: /* no underline */
				/* attr &= ~COMMON_LVB_UNDERSCORE; */
				break;
			case 5:  /* slow blink */
			case 6:  /* fast blink */
				/* We don't have blink, but we do have
				   background intensity */
				attr |= BACKGROUND_INTENSITY;
				break;
			case 25: /* no blink */
				attr &= ~BACKGROUND_INTENSITY;
				break;
			case 7:  /* negative */
				negative = 1;
				break;
			case 27: /* positive */
				negative = 0;
				break;
			case 8:  /* conceal */
			case 28: /* reveal */
				/* Unsupported */
				break;
			case 30: /* Black */
				attr &= ~FOREGROUND_ALL;
				break;
			case 31: /* Red */
				attr &= ~FOREGROUND_ALL;
				attr |= FOREGROUND_RED;
				break;
			case 32: /* Green */
				attr &= ~FOREGROUND_ALL;
				attr |= FOREGROUND_GREEN;
				break;
			case 33: /* Yellow */
				attr &= ~FOREGROUND_ALL;
				attr |= FOREGROUND_RED | FOREGROUND_GREEN;
				break;
			case 34: /* Blue */
				attr &= ~FOREGROUND_ALL;
				attr |= FOREGROUND_BLUE;
				break;
			case 35: /* Magenta */
				attr &= ~FOREGROUND_ALL;
				attr |= FOREGROUND_RED | FOREGROUND_BLUE;
				break;
			case 36: /* Cyan */
				attr &= ~FOREGROUND_ALL;
				attr |= FOREGROUND_GREEN | FOREGROUND_BLUE;
				break;
			case 37: /* White */
				attr |= FOREGROUND_RED |
					FOREGROUND_GREEN |
					FOREGROUND_BLUE;
				break;
			case 38: /* Unknown */
				break;
			case 39: /* reset */
				attr &= ~FOREGROUND_ALL;
				attr |= (plain_attr & FOREGROUND_ALL);
				break;
			case 40: /* Black */
				attr &= ~BACKGROUND_ALL;
				break;
			case 41: /* Red */
				attr &= ~BACKGROUND_ALL;
				attr |= BACKGROUND_RED;
				break;
			case 42: /* Green */
				attr &= ~BACKGROUND_ALL;
				attr |= BACKGROUND_GREEN;
				break;
			case 43: /* Yellow */
				attr &= ~BACKGROUND_ALL;
				attr |= BACKGROUND_RED | BACKGROUND_GREEN;
				break;
			case 44: /* Blue */
				attr &= ~BACKGROUND_ALL;
				attr |= BACKGROUND_BLUE;
				break;
			case 45: /* Magenta */
				attr &= ~BACKGROUND_ALL;
				attr |= BACKGROUND_RED | BACKGROUND_BLUE;
				break;
			case 46: /* Cyan */
				attr &= ~BACKGROUND_ALL;
				attr |= BACKGROUND_GREEN | BACKGROUND_BLUE;
				break;
			case 47: /* White */
				attr |= BACKGROUND_RED |
					BACKGROUND_GREEN |
					BACKGROUND_BLUE;
				break;
			case 48: /* Unknown */
				break;
			case 49: /* reset */
				attr &= ~BACKGROUND_ALL;
				attr |= (plain_attr & BACKGROUND_ALL);
				break;
			default:
				/* Unsupported code */
				break;
			}
		}
		set_console_attr();
		break;
	case 'K':
		erase_in_line();
		break;
	default:
		/* Unsupported code */
		break;
	}
}