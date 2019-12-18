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
struct null_args {int /*<<< orphan*/  nulla_target; } ;
typedef  int /*<<< orphan*/  nargs ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOUNT_NULL ; 
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __UNCONST (char const*) ; 
 int /*<<< orphan*/  memset (struct null_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remount_ro (int /*<<< orphan*/  const*,char const*,int) ; 
 int /*<<< orphan*/  rump_sys_mkdir (char const*,int) ; 
 int /*<<< orphan*/  rump_sys_mount (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct null_args*,int) ; 
 int /*<<< orphan*/  rump_sys_unmount (char const*,int /*<<< orphan*/ ) ; 
 void stub1 (char const*) ; 
 void stub2 (char const*) ; 

__attribute__((used)) static void
basic_test(const atf_tc_t *tc, const char *mp, int expected_errno,
    bool use_layer, void (*pre)(const char *), void (*post)(const char *))
{
	const char *null_mount = "/nullm";
	struct null_args nargs;

	if (use_layer) {
		RL(rump_sys_mkdir(null_mount, 0777));
		memset(&nargs, 0, sizeof(nargs));
		nargs.nulla_target = __UNCONST(mp);;
		RL(rump_sys_mount(MOUNT_NULL, null_mount, 0,
		    &nargs, sizeof(nargs)));
	}
	if (pre)
		(*pre)(use_layer ? null_mount : mp);
	remount_ro(tc, mp, expected_errno);
	if (post)
		(*post)(use_layer ? null_mount : mp);
	if (use_layer)
		RL(rump_sys_unmount(null_mount, 0));
}