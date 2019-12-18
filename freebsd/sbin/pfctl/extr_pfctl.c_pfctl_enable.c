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
 int /*<<< orphan*/  DIOCSTART ; 
 int /*<<< orphan*/  DIOCSTARTALTQ ; 
 scalar_t__ EEXIST ; 
 scalar_t__ ESRCH ; 
 int PF_OPT_QUIET ; 
 scalar_t__ altqsupport ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
pfctl_enable(int dev, int opts)
{
	if (ioctl(dev, DIOCSTART)) {
		if (errno == EEXIST)
			errx(1, "pf already enabled");
		else if (errno == ESRCH)
			errx(1, "pfil registeration failed");
		else
			err(1, "DIOCSTART");
	}
	if ((opts & PF_OPT_QUIET) == 0)
		fprintf(stderr, "pf enabled\n");

	if (altqsupport && ioctl(dev, DIOCSTARTALTQ))
		if (errno != EEXIST)
			err(1, "DIOCSTARTALTQ");

	return (0);
}