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
 char* MAP_FAILED ; 
 int MAP_FILE ; 
 int MAP_SHARED ; 
 int MS_INVALIDATE ; 
 int MS_SYNC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fd ; 
 scalar_t__ file_size ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ msync (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ munmap (char*,scalar_t__) ; 
 int /*<<< orphan*/  prt (char*,scalar_t__) ; 
 int /*<<< orphan*/  prterr (char*) ; 
 int /*<<< orphan*/  report_failure (int) ; 
 scalar_t__ simulatedopcount ; 
 scalar_t__ testcalls ; 

void
doinvl(void)
{
	char *p;

	if (file_size == 0)
		return;
	if (testcalls <= simulatedopcount)
		return;
	if (debug)
		prt("%lu msync(MS_INVALIDATE)\n", testcalls);

	if ((p = (char *)mmap(0, file_size, PROT_READ | PROT_WRITE,
			      MAP_FILE | MAP_SHARED, fd, 0)) == MAP_FAILED) {
		prterr("doinvl: mmap");
		report_failure(205);
	}

	if (msync(p, 0, MS_SYNC | MS_INVALIDATE) != 0) {
		prterr("doinvl: msync");
		report_failure(206);
	}

	if (munmap(p, file_size) != 0) {
		prterr("doinvl: munmap");
		report_failure(207);
	}
}