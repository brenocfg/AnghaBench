#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct statfs {int f_mntfromname; } ;
struct TYPE_3__ {int rm_eo; int rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  dev ;

/* Variables and functions */
 int NMATCHES ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int regcomp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int regexec (int /*<<< orphan*/ *,char*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int statfs (char*,struct statfs*) ; 
 int /*<<< orphan*/  strlcpy (char*,int,int) ; 
 scalar_t__ strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *
get_rootdisk(void)
{
	struct statfs rootfs;
	regex_t re;
#define NMATCHES 2
	regmatch_t rm[NMATCHES];
	char dev[PATH_MAX], *s;
	int rv;

	if (statfs("/", &rootfs) == -1)
		err(1, "statfs(\"/\")");

	if ((rv = regcomp(&re, "^(/dev/[a-z/]+[0-9]*)([sp][0-9]+)?[a-h]?(\\.journal)?$",
		    REG_EXTENDED)) != 0)
		errx(1, "regcomp() failed (%d)", rv);
	strlcpy(dev, rootfs.f_mntfromname, sizeof (dev));
	if ((s = strstr(dev, ".eli")) != NULL)
	    memmove(s, s+4, strlen(s + 4) + 1);

	if ((rv = regexec(&re, dev, NMATCHES, rm, 0)) != 0)
		errx(1,
"mounted root fs resource doesn't match expectations (regexec returned %d)",
		    rv);
	if ((s = malloc(rm[1].rm_eo - rm[1].rm_so + 1)) == NULL)
		errx(1, "out of memory");
	memcpy(s, rootfs.f_mntfromname + rm[1].rm_so,
	    rm[1].rm_eo - rm[1].rm_so);
	s[rm[1].rm_eo - rm[1].rm_so] = 0;

	return s;
}