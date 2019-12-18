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
typedef  int /*<<< orphan*/  wd ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  appendf (char**,char*,...) ; 
 scalar_t__ dochroot ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 scalar_t__ guest ; 
 int logging ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
logcmd(char *cmd, char *file1, char *file2, off_t cnt)
{
	char *msg = NULL;
	char wd[MAXPATHLEN + 1];

	if (logging <= 1)
		return;

	if (getcwd(wd, sizeof(wd) - 1) == NULL)
		strcpy(wd, strerror(errno));

	appendf(&msg, "%s", cmd);
	if (file1)
		appendf(&msg, " %s", file1);
	if (file2)
		appendf(&msg, " %s", file2);
	if (cnt >= 0)
		appendf(&msg, " = %jd bytes", (intmax_t)cnt);
	appendf(&msg, " (wd: %s", wd);
	if (guest || dochroot)
		appendf(&msg, "; chrooted");
	appendf(&msg, ")");
	syslog(LOG_INFO, "%s", msg);
	free(msg);
}