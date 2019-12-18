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
typedef  int /*<<< orphan*/  fname ;

/* Variables and functions */
 int MAXPATHLEN ; 
 scalar_t__ auditd_dist ; 
 int /*<<< orphan*/  inject_dist (char const*,char*,int) ; 
 int /*<<< orphan*/  link (char const*,char*) ; 

__attribute__((used)) static int
auditdist_link(const char *filename)
{
	char fname[MAXPATHLEN];

	if (auditd_dist) {
		inject_dist(filename, fname, sizeof(fname));
		/* Ignore errors. */
		(void) link(filename, fname);
	}

	return (0);
}