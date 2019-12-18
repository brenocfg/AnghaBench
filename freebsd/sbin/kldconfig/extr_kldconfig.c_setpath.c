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
struct pathhead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getmib () ; 
 int /*<<< orphan*/  mib ; 
 scalar_t__ miblen ; 
 char* modpath ; 
 int /*<<< orphan*/  pathctl ; 
 char* qstring (struct pathhead*) ; 
 scalar_t__ strlen (char*) ; 
 int sysctl (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static void
setpath(struct pathhead *pathq)
{
	char *newpath;

	if (miblen == 0)
		getmib();
	if ((newpath = qstring(pathq)) == NULL) {
		errno = ENOMEM;
		err(1, "building path string");
	}
	if (sysctl(mib, miblen, NULL, NULL, newpath, strlen(newpath)+1) == -1)
		err(1, "setting path: sysctl(%s)", pathctl);

	if (modpath != NULL)
		free(modpath);
	modpath = newpath;
}