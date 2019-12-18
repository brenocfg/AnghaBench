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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ checkfor ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/ * xfopenat (int,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
getbounds(int savedirfd)
{
	FILE *fp;
	char buf[6];
	int ret;

	/*
	 * If we are just checking, then we haven't done a chdir to the dump
	 * directory and we should not try to read a bounds file.
	 */
	if (checkfor)
		return (0);

	ret = 0;

	if ((fp = xfopenat(savedirfd, "bounds", O_RDONLY, "r")) == NULL) {
		if (verbose)
			printf("unable to open bounds file, using 0\n");
		return (ret);
	}
	if (fgets(buf, sizeof(buf), fp) == NULL) {
		if (feof(fp))
			logmsg(LOG_WARNING, "bounds file is empty, using 0");
		else
			logmsg(LOG_WARNING, "bounds file: %s", strerror(errno));
		fclose(fp);
		return (ret);
	}

	errno = 0;
	ret = (int)strtol(buf, NULL, 10);
	if (ret == 0 && (errno == EINVAL || errno == ERANGE))
		logmsg(LOG_WARNING, "invalid value found in bounds, using 0");
	fclose(fp);
	return (ret);
}