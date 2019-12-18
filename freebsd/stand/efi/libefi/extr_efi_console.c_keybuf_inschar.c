#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ScanCode; char UnicodeChar; } ;
typedef  TYPE_1__ EFI_INPUT_KEY ;

/* Variables and functions */
 char CHAR_BACKSPACE ; 
#define  SCAN_DELETE 133 
#define  SCAN_DOWN 132 
#define  SCAN_ESC 131 
#define  SCAN_LEFT 130 
#define  SCAN_RIGHT 129 
#define  SCAN_UP 128 
 char* keybuf ; 

__attribute__((used)) static void
keybuf_inschar(EFI_INPUT_KEY *key)
{

	switch (key->ScanCode) {
	case SCAN_UP: /* UP */
		keybuf[0] = 0x1b;	/* esc */
		keybuf[1] = '[';
		keybuf[2] = 'A';
		break;
	case SCAN_DOWN: /* DOWN */
		keybuf[0] = 0x1b;	/* esc */
		keybuf[1] = '[';
		keybuf[2] = 'B';
		break;
	case SCAN_RIGHT: /* RIGHT */
		keybuf[0] = 0x1b;	/* esc */
		keybuf[1] = '[';
		keybuf[2] = 'C';
		break;
	case SCAN_LEFT: /* LEFT */
		keybuf[0] = 0x1b;	/* esc */
		keybuf[1] = '[';
		keybuf[2] = 'D';
		break;
	case SCAN_DELETE:
		keybuf[0] = CHAR_BACKSPACE;
		break;
	case SCAN_ESC:
		keybuf[0] = 0x1b;	/* esc */
		break;
	default:
		keybuf[0] = key->UnicodeChar;
		break;
	}
}