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
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  SYSCTL_DDB_CAPTURE_DATA ; 
 int /*<<< orphan*/  bzero (char*,size_t) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int sysctlbyname (int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ddb_capture_print_sysctl(void)
{
	size_t buflen, len;
	char *buffer;
	int ret;

repeat:
	if (sysctlbyname(SYSCTL_DDB_CAPTURE_DATA, NULL, &buflen, NULL, 0) < 0)
		err(EX_OSERR, "sysctl: %s", SYSCTL_DDB_CAPTURE_DATA);
	if (buflen == 0)
		return;
	buffer = malloc(buflen);
	if (buffer == NULL)
		err(EX_OSERR, "malloc");
	bzero(buffer, buflen);
	len = buflen;
	ret = sysctlbyname(SYSCTL_DDB_CAPTURE_DATA, buffer, &len, NULL, 0);
	if (ret < 0 && errno != ENOMEM)
		err(EX_OSERR, "sysctl: %s", SYSCTL_DDB_CAPTURE_DATA);
	if (ret < 0) {
		free(buffer);
		goto repeat;
	}

	printf("%s\n", buffer);
	free(buffer);
}