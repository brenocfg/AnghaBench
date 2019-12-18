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
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  O_FLASH ; 
 scalar_t__ O_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SC_EX ; 
 int SC_SCR_EX ; 
 int SC_SCR_EXWROTE ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  beep () ; 
 int /*<<< orphan*/  flash () ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

int
cl_bell(SCR *sp)
{
	if (F_ISSET(sp, SC_EX | SC_SCR_EXWROTE | SC_SCR_EX))
		(void)write(STDOUT_FILENO, "\07", 1);		/* \a */
	else {
		/*
		 * Vi has an edit option which determines if the terminal
		 * should be beeped or the screen flashed.
		 */
		if (O_ISSET(sp, O_FLASH))
			(void)flash();
		else
			(void)beep();
	}
	return (0);
}