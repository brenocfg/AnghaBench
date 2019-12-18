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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USES_SYMLINKS ; 
 int /*<<< orphan*/  rump_sys_chdir (char const*) ; 
 int /*<<< orphan*/  rump_sys_symlink (char*,char*) ; 

__attribute__((used)) static void
symlink_root(const atf_tc_t *tc, const char *mp)
{

	USES_SYMLINKS;

	RL(rump_sys_chdir(mp));
	RL(rump_sys_symlink("/", "foo"));
	RL(rump_sys_chdir("foo"));
}