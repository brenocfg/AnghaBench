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
struct printer {char* printer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRDBG (char*,...) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int firstprinter (struct printer*,int*) ; 
 int /*<<< orphan*/  handle_printer (struct printer*) ; 
 int /*<<< orphan*/  init_printer (struct printer*) ; 
 int /*<<< orphan*/  lastprinter () ; 
 int nextprinter (struct printer*,int*) ; 
 int /*<<< orphan*/  printer_tick ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  this_tick ; 

__attribute__((used)) static void
hrPrinter_get_OS_entries(void)
{
	int  status, more;
	struct printer myprinter, *pp = &myprinter;

	init_printer(pp);
	HRDBG("---->Getting printers .....");
	more = firstprinter(pp, &status);
	if (status)
		goto errloop;

	while (more) {
		do {
			HRDBG("---->Got printer %s", pp->printer);

			handle_printer(pp);
			more = nextprinter(pp, &status);
errloop:
			if (status)
				syslog(LOG_WARNING,
				    "hrPrinterTable: printcap entry for %s "
				    "has errors, skipping",
				    pp->printer ? pp->printer : "<noname?>");
		} while (more && status);
	}

	lastprinter();
	printer_tick = this_tick;
}