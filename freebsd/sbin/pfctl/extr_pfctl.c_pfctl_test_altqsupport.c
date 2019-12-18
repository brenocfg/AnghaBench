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
struct pfioc_altq {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETALTQS ; 
 scalar_t__ ENODEV ; 
 int /*<<< orphan*/  PFIOC_ALTQ_VERSION ; 
 int PF_OPT_VERBOSE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_altq*) ; 
 int /*<<< orphan*/  stderr ; 

int
pfctl_test_altqsupport(int dev, int opts)
{
	struct pfioc_altq pa;

	pa.version = PFIOC_ALTQ_VERSION;
	if (ioctl(dev, DIOCGETALTQS, &pa)) {
		if (errno == ENODEV) {
			if (opts & PF_OPT_VERBOSE)
				fprintf(stderr, "No ALTQ support in kernel\n"
				    "ALTQ related functions disabled\n");
			return (0);
		} else
			err(1, "DIOCGETALTQS");
	}
	return (1);
}