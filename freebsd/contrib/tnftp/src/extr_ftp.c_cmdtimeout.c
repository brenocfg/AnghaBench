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
 int /*<<< orphan*/  alarmtimer (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ fromatty ; 
 int /*<<< orphan*/  ptabort ; 
 scalar_t__ ptflag ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timeoutflag ; 
 int /*<<< orphan*/  ttyout ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

void
cmdtimeout(int notused)
{
	int oerrno = errno;

	alarmtimer(0);
	if (fromatty)
		write(fileno(ttyout), "\n", 1);
	timeoutflag++;
	if (ptflag)
		siglongjmp(ptabort, 1);
	errno = oerrno;
}