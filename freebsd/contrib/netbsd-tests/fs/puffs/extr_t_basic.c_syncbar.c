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
struct statvfs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_WAIT ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int rump_sys_statvfs1 (char const*,struct statvfs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
syncbar(const char *fs)
{
	struct statvfs svb;

	if (rump_sys_statvfs1(fs, &svb, ST_WAIT) == -1)
		atf_tc_fail_errno("statvfs");
}