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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * cal_fopen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calendarFile ; 
 int /*<<< orphan*/ * calendarHomes ; 
 int /*<<< orphan*/  calendarNoMail ; 
 scalar_t__ chdir (int /*<<< orphan*/ ) ; 
 scalar_t__ doall ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

FILE *
opencalin(void)
{
	struct stat sbuf;
	FILE *fpin;

	/* open up calendar file */
	if ((fpin = fopen(calendarFile, "r")) == NULL) {
		if (doall) {
			if (chdir(calendarHomes[0]) != 0)
				return (NULL);
			if (stat(calendarNoMail, &sbuf) == 0)
				return (NULL);
			if ((fpin = fopen(calendarFile, "r")) == NULL)
				return (NULL);
		} else {
			fpin = cal_fopen(calendarFile);
		}
	}
	return (fpin);
}