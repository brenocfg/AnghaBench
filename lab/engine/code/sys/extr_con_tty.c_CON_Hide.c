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
struct TYPE_2__ {int cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_Back () ; 
 int /*<<< orphan*/  TTY_CONSOLE_PROMPT ; 
 TYPE_1__ TTY_con ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ ttycon_hide ; 
 scalar_t__ ttycon_on ; 

__attribute__((used)) static void CON_Hide( void )
{
	if( ttycon_on )
	{
		int i;
		if (ttycon_hide)
		{
			ttycon_hide++;
			return;
		}
		if (TTY_con.cursor>0)
		{
			for (i=0; i<TTY_con.cursor; i++)
			{
				CON_Back();
			}
		}
		// Delete prompt
		for (i = strlen(TTY_CONSOLE_PROMPT); i > 0; i--) {
			CON_Back();
		}
		ttycon_hide++;
	}
}