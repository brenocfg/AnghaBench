#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_5__ {int vislines; scalar_t__ xadjust; int /*<<< orphan*/  color; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* SetColor ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CA_DISCONNECTED ; 
 int /*<<< orphan*/  Field_Draw (int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KEYCATCH_CONSOLE ; 
 int Key_GetCatcher () ; 
 scalar_t__ SCREEN_WIDTH ; 
 int /*<<< orphan*/  SCR_DrawSmallChar (scalar_t__,int,char) ; 
 int SMALLCHAR_HEIGHT ; 
 int SMALLCHAR_WIDTH ; 
 TYPE_3__ clc ; 
 TYPE_2__ con ; 
 int /*<<< orphan*/  g_consoleField ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void Con_DrawInput (void) {
	int		y;

	if ( clc.state != CA_DISCONNECTED && !(Key_GetCatcher( ) & KEYCATCH_CONSOLE ) ) {
		return;
	}

	y = con.vislines - ( SMALLCHAR_HEIGHT * 2 );

	re.SetColor( con.color );

	SCR_DrawSmallChar( con.xadjust + 1 * SMALLCHAR_WIDTH, y, ']' );

	Field_Draw( &g_consoleField, con.xadjust + 2 * SMALLCHAR_WIDTH, y,
		SCREEN_WIDTH - 3 * SMALLCHAR_WIDTH, qtrue, qtrue );
}