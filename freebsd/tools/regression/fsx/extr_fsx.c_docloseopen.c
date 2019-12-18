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
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ close (scalar_t__) ; 
 scalar_t__ debug ; 
 scalar_t__ fd ; 
 int /*<<< orphan*/  fname ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prt (char*,scalar_t__) ; 
 int /*<<< orphan*/  prterr (char*) ; 
 int /*<<< orphan*/  report_failure (int) ; 
 scalar_t__ simulatedopcount ; 
 scalar_t__ testcalls ; 

void
docloseopen(void)
{ 
	if (testcalls <= simulatedopcount)
		return;

	if (debug)
		prt("%lu close/open\n", testcalls);
	if (close(fd)) {
		prterr("docloseopen: close");
		report_failure(180);
	}
	fd = open(fname, O_RDWR, 0);
	if (fd < 0) {
		prterr("docloseopen: open");
		report_failure(181);
	}
}