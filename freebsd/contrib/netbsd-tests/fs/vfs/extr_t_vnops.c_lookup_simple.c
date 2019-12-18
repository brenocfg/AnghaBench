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
typedef  int /*<<< orphan*/  sb1 ;
typedef  int /*<<< orphan*/  pb ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 char* basename (char*) ; 
 scalar_t__ memcmp (struct stat*,struct stat*,int) ; 
 int rump_sys_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static void
lookup_simple(const atf_tc_t *tc, const char *mountpath)
{
	char pb[MAXPATHLEN], final[MAXPATHLEN];
	struct stat sb1, sb2;

	strcpy(final, mountpath);
	snprintf(pb, sizeof(pb), "%s/../%s", mountpath, basename(final));
	if (rump_sys_stat(pb, &sb1) == -1)
		atf_tc_fail_errno("stat 1");

	snprintf(pb, sizeof(pb), "%s/./../%s", mountpath, basename(final));
	if (rump_sys_stat(pb, &sb2) == -1)
		atf_tc_fail_errno("stat 2");

	ATF_REQUIRE(memcmp(&sb1, &sb2, sizeof(sb1)) == 0);
}