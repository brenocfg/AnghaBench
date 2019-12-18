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
typedef  scalar_t__ intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char const*,scalar_t__) ; 

void
getfssize(intmax_t *fsz, const char *s, intmax_t disksize, intmax_t reserved)
{
	intmax_t available;

	available = disksize - reserved;
	if (available <= 0)
		errx(1, "%s: reserved not less than device size %jd",
		    s, disksize);
	if (*fsz == 0)
		*fsz = available;
	else if (*fsz > available)
		errx(1, "%s: maximum file system size is %jd",
		    s, available);
}