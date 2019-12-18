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
 int EOF ; 
 int /*<<< orphan*/  EOL ; 
 int /*<<< orphan*/  ESCAPE ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  FORCE ; 
 int /*<<< orphan*/  HALFDUPLEX ; 
 int /*<<< orphan*/  RAISE ; 
 int /*<<< orphan*/  RAISECHAR ; 
 int /*<<< orphan*/  SCRIPT ; 
 int STRIP_PAR ; 
 int any (int,int /*<<< orphan*/ ) ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int character (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cumode ; 
 int escape () ; 
 int getchar () ; 
 scalar_t__ islower (int) ; 
 int /*<<< orphan*/  noesc ; 
 int /*<<< orphan*/  parwrite (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setboolean (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setscript () ; 
 int /*<<< orphan*/  sleep (int) ; 
 int toupper (int) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tipin(void)
{
	int bol = 1;
	int gch;
	char ch;

	/*
	 * Kinda klugey here...
	 *   check for scripting being turned on from the .tiprc file,
	 *   but be careful about just using setscript(), as we may
	 *   send a SIGEMT before tipout has a chance to set up catching
	 *   it; so wait a second, then setscript()
	 */
	if (boolean(value(SCRIPT))) {
		sleep(1);
		setscript();
	}

	while (1) {
		gch = getchar();
		if (gch == EOF)
			return;
		gch = gch & STRIP_PAR;
		if ((gch == character(value(ESCAPE))) && bol) {
			if (!noesc) {
				gch = escape();
				if (gch == EOF)
					return;
				if (gch == 0)
					continue;
			}
		} else if (!cumode && gch == character(value(RAISECHAR))) {
			setboolean(value(RAISE), !boolean(value(RAISE)));
			continue;
		} else if (gch == '\r') {
			bol = 1;
			ch = gch;
			parwrite(FD, &ch, 1);
			if (boolean(value(HALFDUPLEX)))
				printf("\r\n");
			continue;
		} else if (!cumode && gch == character(value(FORCE)))
			gch = getchar();
			if (gch == EOF)
				return;
			gch = gch & STRIP_PAR;
		bol = any(gch, value(EOL));
		if (boolean(value(RAISE)) && islower(gch))
			gch = toupper(gch);
		ch = gch;
		parwrite(FD, &ch, 1);
		if (boolean(value(HALFDUPLEX)))
			printf("%c", ch);
	}
}