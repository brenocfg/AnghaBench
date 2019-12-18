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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  sb ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  atf_tc_fail (char*,int) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*,int,char*) ; 
 int /*<<< orphan*/  md (char*,int,char const*,char*) ; 
 scalar_t__ memcmp (struct stat*,struct stat*,int) ; 
 int rump_sys_stat (char*,struct stat*) ; 

__attribute__((used)) static void
checkfile(const char *path, struct stat *refp)
{
	char buf[MAXPATHLEN];
	struct stat sb;
	static int n = 1;

	md(buf, sizeof(buf), path, "file");
	if (rump_sys_stat(buf, &sb) == -1)
		atf_tc_fail_errno("cannot stat file %d (%s)", n, buf);
	if (memcmp(&sb, refp, sizeof(sb)) != 0)
		atf_tc_fail("stat mismatch %d", n);
	n++;
}