#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_Hide () ; 
 int /*<<< orphan*/  CON_Show () ; 
 int /*<<< orphan*/  Sys_AnsiColorPrint (char const*) ; 
 TYPE_1__* com_ansiColor ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  ttycon_on ; 
 scalar_t__ ttycon_show_overdue ; 

void CON_Print( const char *msg )
{
	if (!msg[0])
		return;

	CON_Hide( );

	if( com_ansiColor && com_ansiColor->integer )
		Sys_AnsiColorPrint( msg );
	else
		fputs( msg, stderr );

	if (!ttycon_on) {
		// CON_Hide didn't do anything.
		return;
	}

	// Only print prompt when msg ends with a newline, otherwise the console
	//   might get garbled when output does not fit on one line.
	if (msg[strlen(msg) - 1] == '\n') {
		CON_Show();

		// Run CON_Show the number of times it was deferred.
		while (ttycon_show_overdue > 0) {
			CON_Show();
			ttycon_show_overdue--;
		}
	}
	else
	{
		// Defer calling CON_Show
		ttycon_show_overdue++;
	}
}