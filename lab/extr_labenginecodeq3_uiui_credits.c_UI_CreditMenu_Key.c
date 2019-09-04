#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sfxHandle_t ;
struct TYPE_3__ {int /*<<< orphan*/  draw; } ;
struct TYPE_4__ {int frame; TYPE_1__ menu; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_APPEND ; 
 int K_CHAR_FLAG ; 
 int /*<<< orphan*/  UI_CreditMenu_Draw_deepmind ; 
 int /*<<< orphan*/  UI_CreditMenu_Draw_ioq3 ; 
 TYPE_2__ s_credits ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static sfxHandle_t UI_CreditMenu_Key( int key ) {
	if( key & K_CHAR_FLAG ) {
		return 0;
	}

	s_credits.frame++;
	if (s_credits.frame == 1) {
		s_credits.menu.draw = UI_CreditMenu_Draw_ioq3;
	}
  else if (s_credits.frame == 2) {
		s_credits.menu.draw = UI_CreditMenu_Draw_deepmind;
	}
  else {
		trap_Cmd_ExecuteText( EXEC_APPEND, "quit\n" );
	}
	return 0;
}