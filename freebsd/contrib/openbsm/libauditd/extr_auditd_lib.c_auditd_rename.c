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
typedef  int /*<<< orphan*/  tname ;
typedef  int /*<<< orphan*/  fname ;

/* Variables and functions */
 int MAXPATHLEN ; 
 scalar_t__ auditd_dist ; 
 int /*<<< orphan*/  inject_dist (char const*,char*,int) ; 
 int rename (char const*,char const*) ; 

int
auditd_rename(const char *fromname, const char *toname)
{
	char fname[MAXPATHLEN], tname[MAXPATHLEN];

	if (auditd_dist) {
		inject_dist(fromname, fname, sizeof(fname));
		inject_dist(toname, tname, sizeof(tname));
		/* Ignore errors. */
		(void) rename(fname, tname);
	}

	return (rename(fromname, toname));
}