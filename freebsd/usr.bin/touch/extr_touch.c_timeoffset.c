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
 int ATOI2 (char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int strlen (char const*) ; 

int
timeoffset(const char *arg)
{
	int offset;
	int isneg;

	offset = 0;
	isneg = *arg == '-';
	if (isneg)
		arg++;
	switch (strlen(arg)) {
	default:				/* invalid */
		errx(1, "Invalid offset spec, must be [-][[HH]MM]SS");

	case 6:					/* HHMMSS */
		offset = ATOI2(arg);
		/* FALLTHROUGH */
	case 4:					/* MMSS */
		offset = offset * 60 + ATOI2(arg);
		/* FALLTHROUGH */
	case 2:					/* SS */
		offset = offset * 60 + ATOI2(arg);
	}
	if (isneg)
		return (-offset);
	else
		return (offset);
}