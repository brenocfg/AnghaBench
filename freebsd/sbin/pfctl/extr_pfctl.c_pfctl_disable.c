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
 int /*<<< orphan*/  DIOCSTOP ; 
 int /*<<< orphan*/  DIOCSTOPALTQ ; 
 scalar_t__ ENOENT ; 
 int PF_OPT_QUIET ; 
 scalar_t__ altqsupport ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
pfctl_disable(int dev, int opts)
{
	if (ioctl(dev, DIOCSTOP)) {
		if (errno == ENOENT)
			errx(1, "pf not enabled");
		else
			err(1, "DIOCSTOP");
	}
	if ((opts & PF_OPT_QUIET) == 0)
		fprintf(stderr, "pf disabled\n");

	if (altqsupport && ioctl(dev, DIOCSTOPALTQ))
			if (errno != ENOENT)
				err(1, "DIOCSTOPALTQ");

	return (0);
}