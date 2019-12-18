#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct pmcstat_pmcrecord {int dummy; } ;
typedef  int /*<<< orphan*/  pmcstat_interned_string ;
typedef  int /*<<< orphan*/  fullpath ;
struct TYPE_2__ {char* pa_samplesdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int PATH_MAX ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRWXU ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 TYPE_1__ args ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ mkdir (char*,int) ; 
 char* pmcstat_string_unintern (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

void
pmcpl_gmon_newpmc(pmcstat_interned_string ps, struct pmcstat_pmcrecord *pr)
{
	struct stat st;
	char fullpath[PATH_MAX];

	(void) pr;

	/*
	 * Create the appropriate directory to hold gmon.out files.
	 */

	(void) snprintf(fullpath, sizeof(fullpath), "%s/%s", args.pa_samplesdir,
	    pmcstat_string_unintern(ps));

	/* If the path name exists, it should be a directory */
	if (stat(fullpath, &st) == 0 && S_ISDIR(st.st_mode))
		return;

	if (mkdir(fullpath, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH) < 0)
		err(EX_OSERR, "ERROR: Cannot create directory \"%s\"",
		    fullpath);
}