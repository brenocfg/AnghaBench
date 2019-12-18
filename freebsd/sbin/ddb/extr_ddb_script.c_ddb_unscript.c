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
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
 char* SYSCTL_UNSCRIPT ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ strlen (char*) ; 
 int sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  usage () ; 

void
ddb_unscript(int argc, char *argv[])
{
	int ret;

	if (argc != 2)
		usage();
	argv++;
	argc--;
	ret = sysctlbyname(SYSCTL_UNSCRIPT, NULL, NULL, argv[0],
	    strlen(argv[0]) + 1);
	if (ret < 0 && errno == EINVAL) {
		errno = ENOENT;
		err(EX_DATAERR, "sysctl: %s", argv[0]);
	} else if (ret < 0)
		err(EX_OSERR, "sysctl: %s", SYSCTL_UNSCRIPT);
}