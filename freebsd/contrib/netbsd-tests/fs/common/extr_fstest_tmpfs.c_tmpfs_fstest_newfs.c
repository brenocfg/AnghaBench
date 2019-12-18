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
struct TYPE_2__ {int ta_root_mode; int /*<<< orphan*/  ta_size_max; int /*<<< orphan*/  ta_version; } ;
struct tmpfstestargs {TYPE_1__ ta_uargs; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  TMPFS_ARGS_VERSION ; 
 struct tmpfstestargs* calloc (int,int) ; 
 int rump_init () ; 

int
tmpfs_fstest_newfs(const atf_tc_t *tc, void **buf, const char *image,
    off_t size, void *fspriv)
{
	int res;
	struct tmpfstestargs *args;

	res = rump_init();
	if (res != 0)
		return res;

	args = calloc(1, sizeof(*args));
	if (args == NULL)
		return -1;

	args->ta_uargs.ta_version = TMPFS_ARGS_VERSION;
	args->ta_uargs.ta_root_mode = 0777;
	args->ta_uargs.ta_size_max = size;

	*buf = args;

	return 0;
}