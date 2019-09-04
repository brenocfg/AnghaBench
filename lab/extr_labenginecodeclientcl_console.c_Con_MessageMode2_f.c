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
struct TYPE_3__ {int widthInChars; } ;

/* Variables and functions */
 int /*<<< orphan*/  Field_Clear (TYPE_1__*) ; 
 int KEYCATCH_MESSAGE ; 
 int Key_GetCatcher () ; 
 int /*<<< orphan*/  Key_SetCatcher (int) ; 
 TYPE_1__ chatField ; 
 int chat_playerNum ; 
 int /*<<< orphan*/  chat_team ; 
 int /*<<< orphan*/  qtrue ; 

void Con_MessageMode2_f (void) {
	chat_playerNum = -1;
	chat_team = qtrue;
	Field_Clear( &chatField );
	chatField.widthInChars = 25;
	Key_SetCatcher( Key_GetCatcher( ) ^ KEYCATCH_MESSAGE );
}