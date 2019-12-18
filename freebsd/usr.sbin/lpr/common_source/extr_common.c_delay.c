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
struct timeval {int tv_sec; int tv_usec; } ;
struct printer {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (struct printer*,char*,int) ; 
 int /*<<< orphan*/  select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

void
delay(int millisec)
{
	struct timeval tdelay;

	if (millisec <= 0 || millisec > 10000)
		fatal((struct printer *)0, /* fatal() knows how to deal */
		    "unreasonable delay period (%d)", millisec);
	tdelay.tv_sec = millisec / 1000;
	tdelay.tv_usec = millisec * 1000 % 1000000;
	(void) select(0, (fd_set *)0, (fd_set *)0, (fd_set *)0, &tdelay);
}