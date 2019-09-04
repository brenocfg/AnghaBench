#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int buttons; } ;
typedef  TYPE_1__ usercmd_t ;
struct TYPE_5__ {scalar_t__ wasPressed; scalar_t__ active; } ;

/* Variables and functions */
 int BUTTON_ANY ; 
 int BUTTON_TALK ; 
 scalar_t__ Key_GetCatcher () ; 
 scalar_t__ anykeydown ; 
 TYPE_2__* in_buttons ; 
 scalar_t__ qfalse ; 

void CL_CmdButtons( usercmd_t *cmd ) {
	int		i;

	//
	// figure button bits
	// send a button bit even if the key was pressed and released in
	// less than a frame
	//	
	for (i = 0 ; i < 15 ; i++) {
		if ( in_buttons[i].active || in_buttons[i].wasPressed ) {
			cmd->buttons |= 1 << i;
		}
		in_buttons[i].wasPressed = qfalse;
	}

	if ( Key_GetCatcher( ) ) {
		cmd->buttons |= BUTTON_TALK;
	}

	// allow the game to know if any key at all is
	// currently pressed, even if it isn't bound to anything
	if ( anykeydown && Key_GetCatcher( ) == 0 ) {
		cmd->buttons |= BUTTON_ANY;
	}
}